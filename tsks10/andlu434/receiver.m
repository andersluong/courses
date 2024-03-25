function [zI,zQ,A,tau] = receiver(x)

fs = 400e3; % samplingsfrekvens
M = 400e3/20e3; % uppsamplingsfaktor
fc = 140000; % bärfrekvens
Ts = 1 / fs; % samplingsperiod

% BP-filter
grad = 100; % filtrets gradtal
undre = 130e3/(fs/2); % normerad undre frekvens
ovre = 150e3/(fs/2); % normerad övre frekvens
[b,a]=fir1(grad,[undre,ovre]);  % designa filter

% eliminerar brus som kan ha uppkommit via kanalen
signal_filtrerad = filter(b,a,[x;zeros(grad/2,1)]);
signal_filtrerad = signal_filtrerad(grad/2+1:end);

% ta reda på tisfördröjning
t_chirp = (0:fs-1)/fs;
chirp_x = 0.018 * chirp(t_chirp,fc-1000,1,fc+1000); % det här är den sända chirp-signal från sender

% chirp finns mellan 1 och 400.000
chirp_y = signal_filtrerad(1:400000); % mottagen chirp

[corr, lag] = xcorr(chirp_y,chirp_x); % korskorrelation
[~, index] = max(abs(corr)); % maxpunkten av korrelationen

figure();
plot(lag, corr);
axis([-400 400 -60 60]);
set(gca, "FontSize", 25);
xlabel("Sampel", 'FontSize', 33);
ylabel("Korskorrelation", 'FontSize', 33);

tau_sampel = lag(index); % tidsfördröjning i sampel
tau = tau_sampel * Ts * 1e6; % tidsfördröjning i us 
A = corr(index)/max(xcorr(chirp_x)); % amplitud
A = round(A, 1); % avrunda till en decimal

% x finns mellan 400.001 och 2.400.000
x_filtrerad = signal_filtrerad(400001+tau_sampel:2400000+tau_sampel) / A;

fs_down = 20e3;
L = length(x_filtrerad);
t = Ts*(0:L-1);
f = fs*(0:L-1)/L;

xI_demodulerad = x_filtrerad .* 2 .* cos(2*pi*fc*t).';
xQ_demodulerad = x_filtrerad .* -2 .* sin(2*pi*fc*t).';

% lågpassfilter
F0 = (fs_down/2)/(fs/2); % normerad gränsfrekvens
[b,a] = fir1(grad,F0);  % designa filter

xI_filtrerad = filter(b,a,[xI_demodulerad;zeros(grad/2,1)]);  % filtrera signalen
xQ_filtrerad = filter(b,a,[xQ_demodulerad;zeros(grad/2,1)]);  % filtrera signalen
xI_filtrerad = xI_filtrerad(grad/2+1:end);
xQ_filtrerad = xQ_filtrerad(grad/2+1:end);

zI = downsample(xI_filtrerad, M);
zQ = downsample(xQ_filtrerad, M);

Ts_down = 1/fs_down;
L_down = length(zI);
t_down = Ts_down*(0:L_down-1)/L_down;

figure();
plot(t_down, zI, t_down, zQ);
set(gca, "FontSize", 25);
xlabel("Tid [s]", 'FontSize', 33);
ylabel("Amplitud", 'FontSize', 33);

end

