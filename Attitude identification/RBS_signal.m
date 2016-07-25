omegab_g = 3;               % guess system bandwidth

Ts = 0.01;
fs = 1/Ts;
fnyquist = fs/2;            % Nyquist frequency
wlow=0.01*fnyquist;
whigh = 0.1*fnyquist;
band = [wlow, whigh]        % The frequency contents of the input signal
type = 'rbs';
levels = [47, 53]
N = 30;
u_ident = idinput(N,type,band,levels);