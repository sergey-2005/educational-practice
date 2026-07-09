%% проверка кода с++ на слух ФМ
clear
clc
fid = fopen('fm_audio.bin','rb');
audio = fread(fid,'float');
fclose(fid);
Fs = 50000; % после децимации
sound(audio,Fs);
fprintf('Нажмите Enter, чтобы остановить\n');
pause();
clear sound;
%% проверка кода с++ на слух АМ
clear
clc
fid = fopen('am_audio.bin','rb');
audio = fread(fid,'float');
fclose(fid);
Fs = 32000;
sound(audio,Fs);
fprintf('Нажмите Enter, чтобы остановить\n');
pause();
clear sound;


