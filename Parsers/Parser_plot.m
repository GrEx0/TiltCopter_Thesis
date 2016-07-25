%% Parser plot                                  %
% Author: Mattia Giurato,Alessandro De Angelis  %
% Last review: 2015/06/06                       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc
clear all
close all

%% Files Parameters


LOG_PARSER = 'logParser.jar';
LOGS_FOLDER = 'parsed_logs';

LOG_NAME = 'RBS_IDENT_4_deltaTH2';
LOG_TYPE = '.txt';
LOG_FOLDER = strcat(LOGS_FOLDER,'/',LOG_NAME);
LOG_FILE = strcat(LOG_NAME,LOG_TYPE);

LOG_CMD = ['java -jar','  ',LOG_PARSER,'  ',LOG_FILE];

SAVE_FILE_TYPE = '.mat';
SAVE_FILE_NAME = LOG_NAME;
SAVE_FILE = strcat(SAVE_FILE_NAME,SAVE_FILE_TYPE);

clear SAVE_FILE_NAME;
clear SAVE_FILE_TYPE;

IMU_RAW_SUFFIX = '-IMU_RAW';
ONBOARD_ATTITUDE_SUFFIX = '-ON_ATTITUDE';
ONBOARD_ATTITUDE_Q_SUFFIX = '-ON_ATTITUDE_QUATER';
ONBOARD_ALTITUDE_SUFFIX = '-ON_ALTITUDE';
ONBOARD_POSITION_SUFFIX = '-ON_POSITION';
BAROMETER_SUFFIX = '-BARO';
GPS_SUFFIX = '-GPS';
RADIO_SUFFIX = '-RADIO';
MIXER_CTR_SUFFIX = '-MIXER_CTR';
ATTITUDE_CTR_SUFFIX = '-ATTITUDE_CTR';
ALTITUDE_CTR_SUFFIX = '-ALTITUDE_CTR';
POSITION_CTR_SUFFIX = '-POSITION_CTR';
GROUND_ATTITUDE_SUFFIX = '-GND_ATTITUDE';
GROUND_POSITION_SUFFIX = '-GND_POSITION';
WAYPOINT_DELTA_SUFFIX = '-WAYPOINT';
HEARTBEAT_SUFFIX = '-HEARTBEAT';

%% Imu Raw scale factor

%Gyroscope
%imu_raw_gyro_scale = diag([0.00032947 0.00033315 0.00031014]);
%Accelerometer
%imu_raw_acc_scale = diag([0.0093684 0.009644 0.0099314]);
%imu_raw_acc_bias = diag([0.05588 -0.024584 0.3292]);
%Magnetometer
%imu_raw_mag_scale = diag([0.00284 0.0027798 0.0030678]);
%imu_raw_mag_bias = diag([0.23112 0.14511 -0.32205]);

%% Parsing

system(LOG_CMD);
clear LOG_CMD;
clear LOG_FILE;
clear LOG_PARSER;
%% Import data logged

cd(LOG_FOLDER)
clear LOG_FOLDER;

disp(' ');
disp(' ');
disp('Stored Data:');

try
    imu_raw_file = strcat(LOG_NAME,IMU_RAW_SUFFIX,LOG_TYPE);
    imu_raw_data = dlmread(imu_raw_file);
    
    %imu_raw_acc = imu_raw_data(:,1:3) * imu_raw_acc_scale - ones(length(imu_raw_data),3)*imu_raw_acc_bias;
    %imu_raw_gyro = imu_raw_data(:,4:6) * imu_raw_gyro_scale;
    %imu_raw_mag = imu_raw_data(:,7:9) * imu_raw_mag_scale - ones(length(imu_raw_data),3)*imu_raw_mag_bias;
    
    imu_raw_acc_x = imu_raw_data(:,1);
    imu_raw_acc_y = imu_raw_data(:,2);
    imu_raw_acc_z = imu_raw_data(:,3);
    
    imu_raw_gyro_x = imu_raw_data(:,4);
    imu_raw_gyro_y = imu_raw_data(:,5); 
    imu_raw_gyro_z = imu_raw_data(:,6);
    
    imu_raw_mag_x = imu_raw_data(:,7);
    imu_raw_mag_y = imu_raw_data(:,8);
    imu_raw_mag_z = imu_raw_data(:,9);
   
    imu_raw_state = imu_raw_data(:,10);
    
    %disp(strcat(IMU_RAW_SUFFIX,'(imu_raw_acc, imu_raw_gyro, imu_raw_mag, imu_raw_state)'));
    disp(strcat(IMU_RAW_SUFFIX,'(imu_raw_acc_x,imu_raw_acc_y, imu_raw_acc_z, imu_raw_gyro_x, imu_raw_gyro_y, imu_raw_gyro_z, imu_raw_mag_x, imu_raw_mag_y, imu_raw_mag_z, imu_raw_state)'));

catch
end

clear IMU_RAW_SUFFIX;
clear imu_raw_data;
clear imu_raw_file;
clear imu_raw_acc_scale;
clear imu_raw_acc_bias;
clear imu_raw_gyro_scale;
clear imu_raw_gyro_bias;
clear imu_raw_mag_scale;
clear imu_raw_mag_bias;

try
    onboard_attitude_file = strcat(LOG_NAME,ONBOARD_ATTITUDE_SUFFIX,LOG_TYPE);
    onboard_attitude_data = dlmread(onboard_attitude_file);
    
    onboard_attitude_roll = onboard_attitude_data(:,1);
    onboard_attitude_pitch = onboard_attitude_data(:,2);
    onboard_attitude_yaw = onboard_attitude_data(:,3);
    onboard_attitude_p = onboard_attitude_data(:,4);
    onboard_attitude_q = onboard_attitude_data(:,5);
    onboard_attitude_r = onboard_attitude_data(:,6);
    onboard_attitude_state = onboard_attitude_data(:,7);

    disp(strcat(ONBOARD_ATTITUDE_SUFFIX,'(onboard_attitude_roll, onboard_attitude_pitch, onboard_attitude_yaw, onboard_attitude_p, onboard_attitude_q, onboard_attitude_r,onboard_attitude_state)'));
catch
end

clear ONBOARD_ATTITUDE_SUFFIX;
clear onboard_attitude_file;
clear onboard_attitude_data;

try
    onboard_attitude_q_file = strcat(LOG_NAME,ONBOARD_ATTITUDE_Q_SUFFIX,LOG_TYPE);
    onboard_attitude_q_data = dlmread(onboard_attitude_q_file);
    
    onboard_attitude_q_vector = onboard_attitude_q_data(:,1:4);
    onboard_attitude_q_bias = onboard_attitude_q_data(:,5:7);
    onboard_attitude_q_state = onboard_attitude_q_data(:,8);
    
    disp(strcat(ONBOARD_ATTITUDE_Q_SUFFIX,'(onboard_attitude_q_vector, onboard_attitude_q_bias,onboard_attitude_q_state)'));
catch  
end

clear onboard_attitude_q_file;
clear onboard_attitude_q_data;
clear ONBOARD_ATTITUDE_Q_SUFFIX;

try
    onboard_position_file = strcat(LOG_NAME,ONBOARD_POSITION_SUFFIX,LOG_TYPE);
    onboard_position_data = dlmread(onboard_position_file);
    
    onboard_position_dist_north = onboard_position_data(:,1);
    onboard_position_u = onboard_position_data(:,2);
    onboard_position_acc_north = onboard_position_data(:,3);
    onboard_position_dist_east = onboard_position_data(:,4);
    onboard_position_v = onboard_position_data(:,5);
    onboard_position_acc_east = onboard_position_data(:,6);
    onboard_position_state = onboard_position_data(:,7);

    disp(strcat(ONBOARD_POSITION_SUFFIX,'(onboard_position_dist_north, onboard_position_u,gps_lon, onboard_position_acc_north, onboard_position_dist_east, onboard_position_v, onboard_position_acc_east, onboard_position_state)'));
catch    
end

clear onboard_position_file;
clear onboard_position_data;
clear ONBOARD_POSITION_SUFFIX;

try
    onboard_altitude_file = strcat(LOG_NAME,ONBOARD_ALTITUDE_SUFFIX,LOG_TYPE);
    onboard_altitude_data = dlmread(onboard_altitude_file);
    
    onboard_altitude_dist_z = onboard_altitude_data(:,1);
    onboard_altitude_w = onboard_altitude_data(:,2);
    onboard_altitude_acc_z = onboard_altitude_data(:,3);
    onboard_altitude_state = onboard_altitude_data(:,4);
    
    disp(strcat(ONBOARD_ALTITUDE_SUFFIX,'(onboard_altitude_dist_z, onboard_altitude_w,onboard_altitude_acc_z, onboard_altitude_state)'));
catch
end

clear onboard_altitude_file
clear onboard_altitude_data
clear ONBOARD_ALTITUDE_SUFFIX;

try
    barometer_file = strcat(LOG_NAME,BAROMETER_SUFFIX,LOG_TYPE);
    barometer_data = dlmread(barometer_file);
    
    barometer_pressure = barometer_data(:,1);
    barometer_state = barometer_data(:,2);
    
    disp(strcat(BAROMETER_SUFFIX,'(barometer_pressure, barometer_state)'));
catch
end

clear BAROMETER_SUFFIX;
clear barometer_file;
clear barometer_data;

try
    gps_file = strcat(LOG_NAME,GPS_SUFFIX,LOG_TYPE);
    gps_data = dlmread(gps_file);

    gps_fix = gps_data(:,1);
    gps_lat = gps_data(:,2);
    gps_lon = gps_data(:,3);
    gps_alt = gps_data(:,4);
    gps_state = gps_data(:,5);
    
    disp(strcat(GPS_SUFFIX,'(gps_fix, gps_lat,gps_lon, gps_alt, gps_state)'));
catch
end

clear gps_file;
clear gps_data;
clear GPS_SUFFIX;


try
    attitude_ctr_file = strcat(LOG_NAME,ATTITUDE_CTR_SUFFIX,LOG_TYPE);
    attitude_ctr_data = dlmread(attitude_ctr_file);
    
    attitude_ctr_var_l = attitude_ctr_data(:,1);
    attitude_ctr_var_m = attitude_ctr_data(:,2);
    attitude_ctr_var_n = attitude_ctr_data(:,3);
    attitude_ctr_state = attitude_ctr_data(:,4);
    
    disp(strcat(ATTITUDE_CTR_SUFFIX,'(attitude_ctr_var_l,attitude_ctr_var_m, attitude_ctr_var_n, attitude_ctr_state)'));
catch
end

clear attitude_ctr_file;
clear attitude_ctr_data;
clear ATTITUDE_CTR_SUFFIX;

try
    altitude_ctr_file = strcat(LOG_NAME,ALTITUDE_CTR_SUFFIX,LOG_TYPE);
    altitude_ctr_data = dlmread(altitude_ctr_file);
    
    altitude_ctr_var_t = altitude_ctr_data(:,1);
    altitude_ctr_ref_z = altitude_ctr_data(:,2);
    altitude_ctr_state = altitude_ctr_data(:,3);
    
    
    disp(strcat(ALTITUDE_CTR_SUFFIX,'(altitude_ctr_var_t,altitude_ctr_ref_z,altitude_ctr_state)'));        
catch   
end

clear altitude_ctr_file;
clear altitude_ctr_data;
clear ALTITUDE_CTR_SUFFIX;

try
    position_ctr_file = strcat(LOG_NAME,POSITION_CTR_SUFFIX,LOG_TYPE);
    position_ctr_data = dlmread(position_ctr_file);
    
    position_ctr_var_r = position_ctr_data(:,1);
    position_ctr_var_p = position_ctr_data(:,2);
    position_ctr_ref_north = position_ctr_data(:,3);
    position_ctr_ref_east = position_ctr_data(:,4);
    position_ctr_ref_yaw = position_ctr_data(:,5);
    position_ctr_state = position_ctr_data(:,6);
    
        
    disp(strcat(POSITION_CTR_SUFFIX,'(position_ctr_var_r,position_ctr_var_p,position_ctr_ref_north,position_ctr_ref_east,position_ctr_ref_yaw,position_ctr_state)'));        
catch   
end

clear position_ctr_file;
clear position_ctr_data;
clear POSITION_CTR_SUFFIX;

try
    mixer_ctr_file = strcat(LOG_NAME,MIXER_CTR_SUFFIX,LOG_TYPE);
    mixer_ctr_data = dlmread(mixer_ctr_file);
    
    mixer_ctr_motor_1 = mixer_ctr_data(:,1);
    mixer_ctr_motor_2 = mixer_ctr_data(:,2);
    mixer_ctr_motor_3 = mixer_ctr_data(:,3);
    mixer_ctr_motor_4 = mixer_ctr_data(:,4);
    mixer_ctr_servo_1 = mixer_ctr_data(:,5);
    mixer_ctr_servo_2 = mixer_ctr_data(:,6);
    mixer_ctr_servo_3 = mixer_ctr_data(:,7);
    mixer_ctr_servo_4 = mixer_ctr_data(:,8);
    mixer_ctr_state = mixer_ctr_data(:,9);
    
    
    disp(strcat(MIXER_CTR_SUFFIX,'(mixer_ctr_motor_1, mixer_ctr_motor_2, mixer_ctr_motor_3, mixer_ctr_motor_4, mixer_ctr_servo_1, mixer_ctr_servo_2, mixer_ctr_servo_3, mixer_ctr_servo_4, mixer_ctr_state)'));
catch    
end

clear mixer_ctr_file;
clear mixer_ctr_data;
clear MIXER_CTR_SUFFIX;

try
    radio_file = strcat(LOG_NAME,RADIO_SUFFIX,LOG_TYPE);
    radio_data = dlmread(radio_file);
    
    radio_thrust = radio_data(:,1);
    radio_roll = radio_data(:,2);
    radio_pitch = radio_data(:,3);
    radio_yaw = radio_data(:,4);
    radio_gen_arm = radio_data(:,5);
    radio_sec_arm = radio_data(:,6);
    radio_mode = radio_data(:,7);
    radio_dN = radio_data(:,8);
    radio_dE = radio_data(:,9);
    radio_dZ = radio_data(:,10);
    radio_state = radio_data(:,11);

    disp(strcat(RADIO_SUFFIX,'(radio_thrust, radio_roll, radio_pitch, radio_yaw, radio_gen_arm, radio_sec_arm, radio_mode, radio_dN, radio_dE, radio_dZ, radio_state)'));
catch
end

clear RADIO_SUFFIX;
clear radio_file;
clear radio_data;

try
    heartbeat_file = strcat(LOG_NAME,HEARTBEAT_SUFFIX,LOG_TYPE);
    heartbeat_data = dlmread(heartbeat_file);
    
    heartbeat_mode = heartbeat_data(:,1);
    heartbeat_radio_state = heartbeat_data(:,2);
    heartbeat_gen_arm = heartbeat_data(:,3);
    heartbeat_sec_arm = heartbeat_data(:,4);
    heartbeat_state = heartbeat_data(:,5);
    
    disp(strcat(HEARTBEAT_SUFFIX,'(heartbeat_mode, heartbeat_radio_state, heartbeat_gen_arm, heartbeat_sec_arm,heartbeat_state)'));
catch    
end

clear heartbeat_file;
clear heartbeat_data;
clear HEARTBEAT_SUFFIX;

try
    ground_attitude_file = strcat(LOG_NAME,GROUND_ATTITUDE_SUFFIX,LOG_TYPE);
    ground_attitude_data = dlmread(ground_attitude_file);
    
    ground_attitude_roll = ground_attitude_data(:,1);
    ground_attitude_pitch = ground_attitude_data(:,2);
    ground_attitude_yaw = ground_attitude_data(:,3);
    ground_attitude_state = ground_attitude_data(:,4);
    
    disp(strcat(GROUND_ATTITUDE_SUFFIX,'(ground_attitude_roll, ground_attitude_pitch, ground_attitude_yaw, ground_attitude_state)'));
catch    
end

clear ground_attitude_file;
clear ground_attitude_data;
clear GROUND_ATTITUDE_SUFFIX;

try
    ground_position_file = strcat(LOG_NAME,GROUND_POSITION_SUFFIX,LOG_TYPE);
    ground_position_data = dlmread(ground_position_file);
    
    ground_position_dist_north = ground_position_data(:,1);
    ground_position_dist_east = ground_position_data(:,2);
    ground_position_state = ground_position_data(:,3);
    
    disp(strcat(GROUND_POSITION_SUFFIX,'(ground_position_dist_north, ground_position_dist_east, ground_position_state)'));
catch
end

clear ground_position_file;
clear ground_position_data;
clear GROUND_POSITION_SUFFIX;

try
    waypoint_delta_file = strcat(LOG_NAME,WAYPOINT_DELTA_SUFFIX,LOG_TYPE);
    waypoint_delta_data = dlmread(waypoint_delta_file);
    
    waypoint_delta_dN = waypoint_delta_data(:,1);
    waypoint_delta_dE = waypoint_delta_data(:,2); 
    waypoint_delta_dZ = waypoint_delta_data(:,3);
    waypoint_delta_thrust = waypoint_delta_data(:,4);
    waypoint_delta_state = waypoint_delta_data(:,5);
    
    disp(strcat(WAYPOINT_DELTA_SUFFIX,'(waypoint_delta_dN, waypoint_delta_dE, waypoint_delta_dZ,waypoint_delta_thrust, waypoint_delta_state)'));

catch    
end
clear waypoint_delta_file;
clear waypoint_delta_data;
clear WAYPOINT_DELTA_SUFFIX;

clear LOG_NAME;
clear LOG_TYPE;

%% save data

save(SAVE_FILE)
clear SAVE_FILE;

%% clear temp files

cd('../..')

%% END of Code