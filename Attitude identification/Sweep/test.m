Ts = .01
fs=100; %sampling frequency
t=0:1/fs:20; %time base - upto 1 second

f0=1;% starting frequency of the chirp
f1=10; %frequency of the chirp at t1=1 second
x = sweep(t,f0,1,f1); 
subplot(2,2,1)
plot(t,x,'k');
title(['Chirp Signal']);
xlabel('Time(s)');
ylabel('Amplitude');