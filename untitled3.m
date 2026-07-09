clear; clc; close all;
Fs_FM = 500000;          % Частота дискретизации FM 500 кГц
Fs_AM = 32000;           % Частота дискретизации AM 32 кГц
% Размер окна для фильтра скользящего среднего сглаживание, убирание высоких
% частот. При следующих значениях, которые я подобрал на слух звук получается
% не сильно приглушённым.
WINDOW_SIZE_AM = 5;      % Для AM 
WINDOW_SIZE_FM = 10;     % Для FM 

file_bin = 'file1EuropaPlus.bin'; % 72 482 816 байт => FM
file_dat = 'am_sound.dat';% 3 276 800 байт => AM
%% 1. ОБРАБОТКА AM (файл .dat), int - 4 байта определил перебором
fprintf(' 1. ОБРАБОТКА AM (Файл .dat) \n');
if ~exist(file_dat, 'file')
    error('Файл %s не найден!', file_dat);
end
fid = fopen(file_dat, 'rb');
am_raw = fread(fid, 'int');
fclose(fid);
% I и Q образуют один отсчёт
fprintf('AM: Прочитано %d отсчетов\n', length(am_raw) / 2);
I_am = am_raw(1:2:end); % нечётные
Q_am = am_raw(2:2:end); % чётные
% Преобразую в double и нормализуем
I_am = double(I_am) / 2147483648;   
Q_am = double(Q_am) / 2147483648;
% Формирую комплексные значения
complex_am = I_am + 1j * Q_am;
% нахожу модуль(длину отрезка) - демодуляция
am_signal = abs(complex_am);
% создание ядра фильтра скользящего среднего. Буду использовать простой
% нерекурсивный
kernel_am = ones(WINDOW_SIZE_AM, 1) / WINDOW_SIZE_AM;
% применяю ядро к элементрам амплитуд
am_filtered = filter(kernel_am, 1, am_signal);
% Убираю первые отсчёты, среднее у которых считается при неполной
% заполнености окна
am_filtered = am_filtered(WINDOW_SIZE_AM:end);
% Нормализация, чтобы избежать клиппинга. Звуковая карта предпочитает диапазон (-1, 1)
% Т.к значения были маленькие, то при нормализации они возрастут до 1 по
% модулю
am_filtered = am_filtered / max(abs(am_filtered));
% Рекурсивная реализация фильтра скользящего среднего AM
am_filtered_rec = zeros(size(am_signal));
% Первое значение вычисляется обычным способом
am_filtered_rec(WINDOW_SIZE_AM) = mean(am_signal(1:WINDOW_SIZE_AM));
% Далее используется рекурсивная формула
for i = WINDOW_SIZE_AM + 1:length(am_signal)
    am_filtered_rec(i) = am_filtered_rec(i-1) + ...
        (am_signal(i) - am_signal(i-WINDOW_SIZE_AM)) / WINDOW_SIZE_AM;
end
% очевидно, что оба фильтра дадут идентичные результаты
% Отбрасываю первые отсчёты
am_filtered_rec = am_filtered_rec(WINDOW_SIZE_AM:end);
% Нормализация
am_filtered_rec = am_filtered_rec / max(abs(am_filtered_rec));
fprintf('AM: Длительность = %.2f секунд\n\n', length(am_filtered)/Fs_AM);
%% 2. Обработка FM (Файл .bin), тоже int - 4байта, определил также перебором
fprintf('2. ОБРАБОТКА FM (Файл .bin)\n');
if ~exist(file_bin, 'file')
    error('Файл %s не найден!', file_bin);
end
fid = fopen(file_bin, 'rb');
fm_raw = fread(fid, 'int'); 
fclose(fid);
fprintf('FM: Прочитано %d отсчётов (I и Q вместе)\n', length(fm_raw)/2);
% Разделяю на I и Q
I = fm_raw(1:2:end);
Q = fm_raw(2:2:end);
% Преобразую в double и нормализую
I = double(I) / 2147483648;
Q = double(Q) / 2147483648;
% Формирую комплексный сигнал
complex_signal = I + 1j * Q;
% демодуляция FM - скорость вращения комплексного вектора
% Вычисляю фазу
phase = atan2(Q, I);
% убираю перескоки фазы с +pi к -pi и наоборот, при помоoи встроенной
% функции. теперь значения в массифе фаз только расстут
phase_unwrapped = unwrap(phase);
% Производная фазы (разность между соседними отсчетами) -> изменение частоты -> звук
fm_audio_raw = diff(phase_unwrapped);
% Убираю постоянную составляющую
fm_signal = fm_audio_raw - mean(fm_audio_raw);
% Фильтр скользящего среднего по аналогии с AM
kernel_fm = ones(WINDOW_SIZE_FM, 1) / WINDOW_SIZE_FM;
fm_audio_filtered = filter(kernel_fm, 1, fm_signal);
% Не учитываю начальные значение, когда окно не целиком заполнено 
fm_audio_filtered = fm_audio_filtered(WINDOW_SIZE_FM:end);
% Нормализация
fm_audio_filtered = fm_audio_filtered / max(abs(fm_audio_filtered));
% Децимация (понижение частоты с 500 кГц до 50 кГц)
DECIMATION_FACTOR = 10;
% захватываю каждый 10 отсчёт
fm_audio_decimated = fm_audio_filtered(1:DECIMATION_FACTOR:end);
Fs_FM_new = Fs_FM / DECIMATION_FACTOR;  % 50 кГц
% Рекурсивная реализация фильтра скользящего среднего FM
fm_filtered_rec = zeros(size(fm_signal));
% Первое значение
fm_filtered_rec(WINDOW_SIZE_FM) = mean(fm_signal(1:WINDOW_SIZE_FM));
% Рекурсивное обновление вычитаю крайнее левое, добавляю новое
for i = WINDOW_SIZE_FM + 1:length(fm_signal)
    fm_filtered_rec(i) = fm_filtered_rec(i-1) + ...
        (fm_signal(i) - fm_signal(i-WINDOW_SIZE_FM)) / WINDOW_SIZE_FM;
end
% Убираю первые значения
fm_filtered_rec = fm_filtered_rec(WINDOW_SIZE_FM:end);
% Нормализация
fm_filtered_rec = fm_filtered_rec / max(abs(fm_filtered_rec));
% Децимация
fm_audio_rec_decimated = fm_filtered_rec(1:DECIMATION_FACTOR:end);
fprintf('FM: Длительность = %.2f секунд\n', length(fm_audio_decimated)/Fs_FM_new);
%% 3. Визуализация сигнальных созвездий(вспомогательное для себя и удобства
% восприятия)
fprintf('\n 3. ВИЗУАЛИЗАЦИЯ СОЗВЕЗДИЙ \n');
% Беру первые 2000 комплексных чисел, чтобы график был читаемым
N_points = 2000;
%  Созвездие AM
figure('Name', 'Сигнальные созвездия', 'Position', [100, 100, 1200, 500]);
subplot(1,2,1);
% Рисую только точки на комплексной плоскости
plot(real(complex_am(1:N_points)), imag(complex_am(1:N_points)), '.', ...
     'MarkerSize', 6, 'Color', [0, 0, 0]);
title('Созвездие AM (точки)');
xlabel('I (Real)');
ylabel('Q (Imag)');
grid on;
% принудительно устанавливаетс Расстояние между 0 и 1 по горизонтали, так,
% чтобы оно было равно расстоянию между 0 и 1 по вертикали
axis equal;
xlim([-1.2, 1.2]);
ylim([-1.2, 1.2]);
hold on;
% Рисую оси координат
plot([-1.5, 1.5], [0, 0], 'k--', 'LineWidth', 0.5);
plot([0, 0], [-1.5, 1.5], 'k--', 'LineWidth', 0.5);
hold off;
%  Созвездие FM
subplot(1,2,2);
% Рисую радиус-вектор к точки (I, Q)
hold on;
for k = 1:N_points
    plot([0, real(complex_signal(k))], [0, imag(complex_signal(k))], ...
         '-', 'LineWidth', 1, 'Color', [0, 0, 0]);
end
% Рисую точки на концах векторов
plot(real(complex_signal(1:N_points)), imag(complex_signal(1:N_points)), ...
     '.', 'MarkerSize', 6, 'Color', [1, 0, 0]);
title('Созвездие FM (радиус-векторы)');
xlabel('I (Real)');
ylabel('Q (Imag)');
grid on;
axis equal;
xlim([-1.2, 1.2]);
ylim([-1.2, 1.2]);
plot([-1.5, 1.5], [0, 0], 'k--', 'LineWidth', 0.5);
plot([0, 0], [-1.5, 1.5], 'k--', 'LineWidth', 0.5);
hold off;
fprintf('Графики созвездий построены (AM - точки, FM - радиус-векторы).\n');
%% 4. ПРОИГРЫВАНИЕ И СРАВНЕНИЕ
fprintf('\n 4. ПРОИГРЫВАНИЕ И СРАВНЕНИЕ \n');
% Воспроизведение AM нерекурсивный
fprintf('Воспроизведение AM нерекурсивный\n');
sound(am_filtered, Fs_AM);
fprintf('Нажмите Enter, чтобы остановить\n');
pause();
clear sound;
% Воспроизведение AM рекурсивный 
fprintf('Воспроизведение AM рекурсивный\n');
sound(am_filtered_rec, Fs_AM);
fprintf('Нажмите Enter, чтобы остановить\n');
pause();
clear sound;
% Воспроизведение FM нерекурсивный
fprintf('Воспроизведение FM нерекурсивный\n');
sound(fm_audio_decimated, Fs_FM_new);
fprintf('Нажмите Enter, чтобы остановить\n');
pause();
clear sound;
% Воспроизведение FM рекурсивный
fprintf('Воспроизведение FM рекурсивный\n');
sound(fm_audio_rec_decimated, Fs_FM_new);
fprintf('Нажмите Enter, чтобы остановить\n');
pause();
clear sound;
%% левое созвездие надо приблизить тогда можно будет увидеть кольцо из точек
