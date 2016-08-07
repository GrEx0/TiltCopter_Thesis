omegab_g = 3;               % guess system bandwidth

Ts = 0.01;
fs = 1/Ts;
fnyquist = fs/2;            % Nyquist frequency
wlow=.1;
whigh =1;
band = [wlow, whigh]        % The frequency contents of the input signal
type = 'rbs';
deltaTH = 3;
levels = [-deltaTH/2, deltaTH/2];
N = 30;
u_ident= idinput(N,type,band,levels);