%% RBS
wait_time = 1;              % time to wait between each signal
omegab_q =30;               % guess system bandwidth
N = 300;                     % length of RBS vector

B = ceil(omegab_q);         %you need a integer frequency[rad/s]

fecc = B/(2*pi);            %[Hz]
tk = 1/(2*fecc);            %[s]
type = 'rbs';

wlow = .1;                  %
whigh = 1;
band = [wlow, whigh];

deltaTH = 2;
levels = [-deltaTH/2, deltaTH/2];

u_ident = idinput(N,type,band,levels);
motor_speed = 50;
for j=1:N
    fprintf('test actuators 0 %d 0 %d 0 0 0 0 \n',motor_speed+u_ident(j),motor_speed-u_ident(j))
    tic;
      while toc < tk
      end
end
