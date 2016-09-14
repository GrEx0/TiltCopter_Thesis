% This script performs the test_bed roll attidude control experimental tests.
% specify in test_bed the commands (roll/rollMax) and the seconds to wait
% between each command (seconds)
% Uses bluetooth connection

% Setup the correct CHARSET encoding for serial
    slCharacterEncoding('UTF-8');


%% Input command definition
% Uses the same approach of the Servo identification

%logName = 'atti_testbed_0509_1';
% seconds = 2;               % test #1 0309
% test_bed = [0 0.25 0 0.25 0 0.5 0 0.5 0 -0.25 0 -0.25 0 ];   %  test #1 0309
% seconds = 3 ;               % test #2 0309
% test_bed = [0 0.1 0 -0.1 0 0.25 0 -0.25 0 -0.3 0 0.3 0 ];   %  test #2 0309
% seconds = 3 ;               % test #3 0309
% test_bed = [0 0.25 0 0.25 0 0.5 0 0.5 0 -0.25 0 -0.25 0 ];   %  test #3 0309, ripeto il test 1 dato che aveva batteria scarica
% seconds = 3 ;               % test #4 0309
% test_bed = [0 0.25 -0.25 0.25 -0.25 0.5 -0.5 0.5 -0.5 0];   %  test #4 0309
% seconds = 4 ;               % test #5 0309
% test_bed = [0 0.25 -0.25 0.25 -0.25 0.5 -0.5 0.5 -0.5 0];   %  test #5 0309
% seconds = 4 ;               % test #6 0309
% test_bed = [0 0.30 -0.30 0.30 -0.30 0.5 -0.5 0.5 -0.5 0];   %  test #6 0309
% seconds = 4 ;               % test #7 0309
% test_bed = [0 0.30 0 0.30 0 0.67 0 0.67 0];   %  test #7 0309  è registrato in test #6 penso, non ho cmabiato nome
% seconds = 4 ;               % test #8 0309
% test_bed = [0 0.67 -0.67 0.67 -0.67 0.67 0 ];   %  test #8 0309
% seconds = 4 ;               % test #13 0309
% test_bed = [0 0.67 -0.67 0.67 -0.67 0.67 0 ];   %  test 13 atti_testbed_0309_13 salvato in 0309
%------------------------------------------------------------------------------------------------------
% TESTS 0509
seconds = 3;               % test #1 0509
test_bed = [0 0.25 0 0.25 0 0.5 0 0.5 0 -0.25 0 -0.25 0 ];

seconds = 5;               % test #2 0509
test_bed = [0 0.25 0 0.25 0 0.5 0 0.5 0 -0.25 0 -0.25 0 ];  

seconds = 3 ;              % test #3 0509
test_bed = [0 0.1 0 -0.1 0 0.25 -0.25 0 -0.3 0 0.3 0 ]; 

seconds = 4 ;              % test #4 0509
test_bed = [0 0.1 0 -0.1 0 0.25 0 -0.25 0 -0.3 0 0.3 0 ];

seconds = 5 ;              % test #5 0509
test_bed = [0 0.1 -0.1 0 0.25 -0.25 0 0.5 -0.5 0 0.7 0 -0.7 0 ];

seconds = 5 ;              % test #6 0509
test_bed = [0 0.1 -0.1 0 0.25 -0.25 0 0.5 -0.5 0 0.67 -0.67 0 ];

seconds = 5 ;              % test #7 0509
test_bed = [0 0.1 0 -0.1 0 0.3 0 -0.3 0.5 0 -0.5 0.67 0 -0.67 0 ];
% ----------------------------- DISTURBANCE TEST ON MOTORS
% 8. DISTURBO SU MOTORE 2
% seconds = 5;                % test #8 0509
% test_bed = [0 5 0 -5 0 7 0 -7 0];

% TEST 9 e 10 sono con il disturbo di carico
% test #9  -> 95g
% test #10 -> 145g

%--------------------------- DISTURBANCE REJECTION TESTS
% test #9 0309 , la prima volta non ho cambiato nome, sarà loggato sul log
% 8. DISTURBO SU MOTORE 2
% seconds = 5;
% test_bed = [0 5 0 -5 0 7 0 -7 0];
% % test #10 disturbo motore 4
% seconds = 5;
% test_bed = [0 5 0 -5 0 7 0 -7 0];
% % test #11 disturbo motore 4
% seconds = 5;
% test_bed = [0 3 0 -3 0 6 0 -6 0];
% % test #12 disturbo motore 2
% seconds = 5;
% test_bed = [0 3 0 -3 0 6 0 -6 0];
%% Bluetooth comunication
     s = Bluetooth('HB01',1);
    disp('Opening Bluetooth connection..');
    fopen(s);
    disp('Bluetooth connected!');

logName = 'atti_testbed_0509_8';
% Setup log
cmd = ['log ',logName,' ', 'mixer_ctr o_attitude attitude_ctr attitude_ctr_test']
        fprintf(s,'%s \r\n',cmd);
        fread(s);
        
  disp('Starting simulation');
  cmd = sprintf('test attitude_ctr_test 0.1 0 0 0');
  fprintf(s,'%s \r\n',cmd);
  tic
   while toc < 2
   end
  cmd = sprintf('test attitude_ctr_test 0.3 0 0 0');
  fprintf(s,'%s \r\n',cmd);
  tic
   while toc < 2
   end
 cmd = sprintf('test attitude_ctr_test 0.35 0 0 0');
  fprintf(s,'%s \r\n',cmd);
  tic
   while toc < 2
   end
    
        for i = 1:length(test_bed)
            %cmd = sprintf('test attitude_ctr_test 0.4 %d 0 0',test_bed(i)) %
            %test normale
            
            % disrurbance test
            cmd = sprintf('test attitude_ctr_test 0.4 0 0 0 0 %d 0 0',test_bed(i))
            fprintf(s,'%s \r\n',cmd);
            tic;
            while toc < seconds
            end
        end
        
        cmd = 'test attitude_ctr_test stop '
       fprintf(s,'%s \r\n',cmd);
        cmd = 'log stop '
       fprintf(s,'%s \r\n',cmd);
        disp('Test end');