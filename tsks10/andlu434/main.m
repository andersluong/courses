clear              % Rensa Workspace
close all          % Stäng alla figurfönster
clc                % Rensa Command Window

[xI,fs] = audioread('xI.wav');
[xQ,fs] = audioread('xQ.wav');

x = sender(xI,xQ);
y = TSKS10channel(x);

[zI,zQ,A,tau] = receiver(y);

% check with SNR for xI, xQ to zI, zQ
SNRzI = 20*log10(norm(xI)/norm(zI-xI));
SNRzQ = 20*log10(norm(xQ)/norm(zQ-xQ));