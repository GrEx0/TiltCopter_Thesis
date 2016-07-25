B=[-6400 1600];
F=[1 5 408 416 1600];
M0=idpoly(1,B,1,1,F,'Ts',0);
close all;
step(M0);
u = prbs(10,7);
N=length(u);
Ts=0.01;
datau = iddata([],u,Ts,'InterSample','zoh');
snr=10;
y = simc(M0,datau,snr);
data = iddata(y,u,Ts,'InterSample','zoh');
   idplot(data,1:500);
    xlabel('Time (sec)')