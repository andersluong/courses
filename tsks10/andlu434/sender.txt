function x = sender(xI,xQ)

fs = 20e3; % sampelfrekvens
M = 400e3/fs; % uppsamplingsfaktor
fc = 140000; % bärfrekvens
Ts = 1 / fs; % Samplingsperiod
L = length(xI); % xI och xQ har samma längd
t = Ts*(0:L-1); % tidsvektor


figure();
plot(t, xI, t, xQ);
set(gca, "FontSize", 25);
xlabel("Tid [s]", 'FontSize', 33);
ylabel("Amplitud", 'FontSize', 33);

xI_up = upsample(xI,M); % uppsampling av xI till 400 kHZ
xQ_up = upsample(xQ,M); % uppsampling av xQ till 400 kHZ

L_up = length(xI_up); % längden av den uppsamplade signalen
Ts_up = Ts/M; % uppsamplade periodtiden
fs_up = fs*M; % uppsamplade sampelfrekvens
t_up = Ts_up*(0:L_up-1); % tidsvektor

% lågpassfilter
grad = 100; % filtrets gradtal
F0 = (fs/2)/(fs_up/2); % normerad gränsfrekvens
[b,a] = fir1(grad, F0);  % designa filter

xI_filtrerad = filter(b,a,[xI_up;zeros(grad/2,1)])*M;  % filtrera signalen
xQ_filtrerad = filter(b,a,[xQ_up;zeros(grad/2,1)])*M;  % filtrera signalen
xI_filtrerad = xI_filtrerad(grad/2+1:end);
xQ_filtrerad = xQ_filtrerad(grad/2+1:end);

% skapa chirp för att mäta tidsfördröjning senare
t_chirp = (0:fs_up-1)/fs_up;
puls = 0.018 * chirp(t_chirp,fc-1000,1,fc+1000);

L_puls = length(puls); % längden av chirpsignalen

figure();
x_axis = fs_up * (0:L_puls-1)/L_puls;
plot(x_axis, abs(fft(puls)));
axis([0 200000 0 100]);
set(gca, "FontSize", 25);
xlabel("Frekvens [Hz]", 'FontSize', 33);
ylabel("Amplitud", 'FontSize', 33);

x_modulerad = xI_filtrerad .* cos(2*pi*fc*t_up).' - xQ_filtrerad .* sin(2*pi*fc*t_up).';

% de första 400.000 samplen är chirp och resterande är signalen
x = [puls';x_modulerad];

figure();
f_spec=fs_up*(0:length(x)-1)/length(x); % frekvensvektor
plot(f_spec, abs(fft(x)));
axis([0 400000 0 4000]);
set(gca, "FontSize", 25);
xlabel("Frekvens [Hz]", 'FontSize', 33);
ylabel("Amplitud", 'FontSize', 33);


end