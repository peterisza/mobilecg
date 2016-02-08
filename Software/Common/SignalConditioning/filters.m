pkg load signal

clc

format long;

N = 3000;
cut = 2200;

testSignal =[zeros(1,N), 1, zeros(1,N)];

sf = 500*2000/2048;
sf2 = sf/2;
[b,a] = pei_tseng_notch(50/sf2, 0.5/sf2);
filtered = filtfilt(b, a, testSignal);
b
a

[b,a] = cheby2(2, 40, 0.2/sf2, "high");
filtered = filtfilt(b, a, filtered);
b
a

taps = filtered(N-cut:N+cut+2);
m = abs(fft(taps,48800));
20*log10(m(1))

plot(20*log10(m(1:24000)))
#plot(taps)
