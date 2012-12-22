close all;
clear all;
clc;


%iPhone Sensor Log from Crossbow started at Dec 2, 2012, 1:07:59 PM Eastern Standard Time.
% ElapsedTime(s) xMag(uT) yMag(uT) zMag(uT) xAccel(g) yAccel(g) zAccel(g) latitude(deg) longitude(deg) altitude(m)

file = 'xbowSensorLog(3).txt';
Coordinate = textread(file);

time = Coordinate (:,1);
y = Coordinate (:,6);

plot(time,y);
L=length(y);Fs=20;
NFFT = 2^nextpow2(L); % Next power of 2 from length of y
Y = fft(y,NFFT)/L;
f = Fs/2*linspace(0,1,NFFT/2+1);
figure,plot(f,2*abs(Y(1:NFFT/2+1))) 
signal_mag=2*abs(Y(1:NFFT/2+1));
title('Single-Sided Amplitude Spectrum of V(t)')
xlabel('Frequency (Hz)')
ylabel('|V(f)|')

