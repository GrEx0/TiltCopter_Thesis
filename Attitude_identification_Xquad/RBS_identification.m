% Setup the correct CHARSET encoding for serial
    slCharacterEncoding('UTF-8');
%% Bluetooth comunication
% s = Bluetooth('HB01',1);
% disp('Opening Bluetooth connection..');
% fopen(s);
% disp('Bluetooth connected!');
    

%% RBS
wait_time = 1;              % time to wait between each signal
omegab_q =7;               % guess system bandwidth
N =100;                     % length of RBS vector

B = ceil(omegab_q);         %you need a integer frequency[rad/s]

fecc = B/(2*pi);            %[Hz]
tk = 1/(2*fecc);            %[s]
type = 'rbs';

wlow = .3;                  %
whigh = 1;
band = [wlow, whigh];

deltaTH = 1;
levels = [-deltaTH/2, deltaTH/2];

u_ident = idinput(N,type,band,levels);
   
%%  Test commands

motor_speed =  60       % [%]


disp('Starting simulation');
disp('IMU calibrating..');
% cmd = sprintf('sim_raspy 99 1 0');
% fprintf(s,'%s \r\n',cmd);
cmd = sprintf('test motors 10 10 9.6 9.6');
fprintf(s,'%s \r\n',cmd);
tic;
      while toc < 1
      end
    cmd = sprintf('test motors 20 20 19.6 19.6');
fprintf(s,'%s \r\n',cmd);
tic;
      while toc < 1
      end
cmd = sprintf('test motors 30 30 29.6 29.6');
fprintf(s,'%s \r\n',cmd);
tic;
      while toc < 1
      end   
cmd = sprintf('test motors 40 40 39.6 39.6');
fprintf(s,'%s \r\n',cmd);
tic;
      while toc < 1
    end
disp('Motori a regime');

% Setting up the LOG for the experiment
cmd = ['log RBS_2_deltaTH1_Xquad', ' ', 'mixer_ctr',' ','o_attitude']
fprintf(s,'%s \r\n',cmd);
fread(s);

%  cmd = sprintf('sim_raspy 99 2 2');
%  fprintf(s,'%s \r\n',cmd);

for j = 1:N
   cmd = sprintf('test motors %d %d %d %d ',motor_speed+u_ident(j),motor_speed+u_ident(j),motor_speed-u_ident(j)-0.5,motor_speed-u_ident(j)-0.5)
     fprintf(s,'%s \r\n',cmd);
     tic;
     while toc < tk
     end
end
disp('Test successfully ended');
cmd = 'test motors stop ';
fprintf(s,'%s \r\n',cmd);
cmd = 'log stop ';
fprintf(s,'%s \r\n',cmd);
% cmd = 'sim_raspy stop ';
% fprintf(s,'%s \r\n',cmd);
% fclose(s);
