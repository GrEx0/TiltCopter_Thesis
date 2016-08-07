% Setup the correct CHARSET encoding for serial
    slCharacterEncoding('UTF-8');
%% Bluetooth comunication
 %   s = serial('COM3');
     s = Bluetooth('HB01',1);
disp('Opening Bluetooth connection..');
    fopen(s);
disp('Bluetooth connected!');
    

%% RBS
wait_time = 1;              % time to wait between each signal
omegab_q =12;               % guess system bandwidth
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

motor_speed =  50       % [%]


disp('Starting simulation');
disp('IMU calibrating..');
cmd = sprintf('sim_raspy 99 1 0');
fprintf(s,'%s \r\n',cmd);
tic;
      while toc < 8
    end
disp('IMU calibrated!');

% Setting up the LOG for the experiment
cmd = ['log RBS_6b_deltaTH1_290716', ' ', 'mixer_ctr',' ','imu_raw',' ','o_attitude']
fprintf(s,'%s \r\n',cmd);
fread(s);

 cmd = sprintf('sim_raspy 99 2 2');
 fprintf(s,'%s \r\n',cmd);

for j = 1:N
   cmd = sprintf('test actuators 0 %d 0 %d 0 0 0 0',motor_speed+u_ident(j)-1,motor_speed-u_ident(j))
     fprintf(s,'%s \r\n',cmd);
     tic;
     while toc < tk
     end
end
disp('Test successfully ended');
cmd = 'test actuators stop ';
fprintf(s,'%s \r\n',cmd);
cmd = 'log stop ';
fprintf(s,'%s \r\n',cmd);
cmd = 'sim_raspy stop ';
fprintf(s,'%s \r\n',cmd);
fclose(s);
