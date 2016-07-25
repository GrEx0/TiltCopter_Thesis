k=0

N = 33 % Note: Odd number
Fs = 2*N/(5*pi) % Sampling frequency
dt = 1/Fs % Time sampling interval

T = N*dt % FFT imposed period
t = dt*(0:N-1);

df = 1/T % frequency resolution
f = df*(0:N-1); % Nonnegative unipolar frequency range
Q = ceil((N+1)/2) % No. of unique spectral points when y is real
fQ = (Q-1)*df % Maximum unique spectrum frequency
fb = f-fQ; % Bipolar frequency range
P = floor((N+1)/2)

for f0 = 0:0.5:Fs/2
    y = exp(-t/3).*cos(2*pi*f0*t);
    Y = fft(y);
    A = abs(Y);
    Adb = 20*log10(A);
    Abdb = [Adb(P+1:N) Adb(1:P)];

    k = k+1, figure(k)
    subplot(3,1,1)
    plot(t,y)
    subplot(3,1,2)
    plot(f(1:Q),Adb(1:Q))
    subplot(3,1,3)
    plot(fb,Abdb)
end