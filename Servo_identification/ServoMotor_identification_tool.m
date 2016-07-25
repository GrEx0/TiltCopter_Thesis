% Setup the correct CHARSET encoding for serial
    slCharacterEncoding('UTF-8');

%% SETUP DATA AND TEST COMMANDS

    seconds = 2;                %seconds to wait between an input and the other
    motor_speed = 50;
    number_of_tests = 10;
    servo_angles_1 = [0 8 0 8 0 16 0 16 0 25 0 25 0 30 0 30 0 ];   % actuators_ident_5 con 2s
    servo_angles_2 = [0 8 0 8 0 16 0 16 0 25 0 25 0 30 0 30 0 ];   % actuators_ident_5 con 2s
    servo_angles_3 = [0 -10 0 10 0 -15 0 15 0 -20 0 20 0 -30 0 30 0 ];   % actuators_ident_5 con 2s
    servo_angles_4 = [0 -10 0 10 0 -15 0 15 0 -20 0 20 0 -30 0 30 0 ];   % actuators_ident_5 con 2s

    % servo_angles = [-10 0 -10 0 -15 0 -15 0 -20 0 -20 0];
    %test_matrix = [ servo_angles_1; servo_angles_2; servo_angles_3; servo_angles_4;];
    test_matrix = [ servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1;servo_angles_1]
    %second_vector = [1 2 1 2];
    second_vector = [1 1 1 1 1 1 1 1 1 1]

%% Bluetooth comunication

    s = serial('COM3');
    s = Bluetooth('HB01',1);
    % set(s,'BaudRate',57600);
    disp('Opening Bluetooth connection..');
    fopen(s);
    disp('Bluetooth connected!');

    % DA DISABILITARE SOLO SE NON C'Ê IL RADIOCOMANDO
    %    tic;
    % while toc < 3
    % end
    % cmd = 'sim_raspy 6 2 2 ';
    % fprintf(s,'%s \r\n',cmd);
    
    %% test commands

    for j = 1:number_of_tests
        cmd = ['log 12-07-16_act_id11_', int2str(j), ' ', 'g_attitude mixer_ctr']
        fprintf(s,'%s \r\n',cmd);
        fread(s);

        disp('Starting simulation');
        for i = 1:length(test_matrix(j,:))
            %     cmd = ['test actuators 0 0 0' ' ' num2str(motor_speed,2) ' ' '0 0 0' ' ' num2str(servo_angles(i),2)]
            cmd = sprintf('test actuators 0 0 0 %d 0 0 0 %+d',motor_speed,test_matrix(j,i))
            % A=[motor_speed servo_angles(i)];
            %      fprintf(s,'test actuators 0 0 0 %0.2f 0 0 0 %+0.2f \r\n',A);
            
            fprintf(s,'%s \r\n',cmd);
            tic;
            while toc < second_vector(j)
            end

        end
                 cmd = 'test actuators stop ';
                 fprintf(s,'%s \r\n',cmd);
                 cmd = 'log stop ';
                 fprintf(s,'%s \r\n',cmd);
        tic;
        while toc < 5
        end
    end
    fclose(s);
