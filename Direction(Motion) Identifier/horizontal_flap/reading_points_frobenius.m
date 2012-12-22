clear all;close all;clc;

%Final Mean
% 
load horz_stable.mat MU2 MV2
time=1:200;
%Filtered Horiz
Fs=16;
cutoff=3;
[num,den] = butter(1,0.3/8,'low'); 
filtered_horiz = filtfilt(num,den,MU2(1:200));

figure,plot(time,filtered_horiz);
fnames=dir('*.jpg');

textColor1    = [255, 0, 0];
textColor2    = [0, 0,255];
aviobj=VideoWriter('horz_raw.avi');
open(aviobj);
fig=figure;
for K=1:length(time)
fnames(K).name
    I=imread(fnames(K).name);
    textLocation1 = [500 720];
    textLocation2 = [359 460];
   
    imshow(I);
    if filtered_horiz(K)>=1
    text('Position', textLocation1,'String','LEFT','FontSize',30,'Color','r');
    else if filtered_horiz(K)<-1
    text('Position', textLocation1,'String','RIGHT','FontSize',30,'Color','r');
        else
    text('Position', textLocation1,'String','','FontSize',24,'Color','r');
        end
    end
    if MV2(K)>=6.5 
    text('Position', textLocation2,'String','UP','FontSize',30,'Color','r');
    else if MV2(K)<-6.5
    text('Position', textLocation2,'String','DOWN','FontSize',30,'Color','r');
        else
    text('Position', textLocation2,'String','      ','FontSize',24,'Color','r');

        end
        
    end
    F=getframe(fig,[150, 50,1000,720]);
    writeVideo(aviobj,F);

        
   
end

close(fig);
close(aviobj);