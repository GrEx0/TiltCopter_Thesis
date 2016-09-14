%% Parser plot                                  %
% Author: Mattia Giurato,Alessandro De Angelis  %
% Last review: 2015/06/06                       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% clc
% clear all
% close all

%% Files Parameters


LOG_PARSER = 'logParser.jar';
LOGS_FOLDER = 'parsed_logs';

LOG_NAME = 'test_mahony_4';
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
O_ATTITUDE_SUFFIX = '-ON_ATTITUDE';
O_ATTITUDE_Q_SUFFIX = '-ON_ATTITUDE_QUATER';
O_ALTITUDE_SUFFIX = '-ON_ALTITUDE';
O_POSITION_BODY_SUFFIX = '-ON_POSITION_BODY';
O_POSITION_NED_SUFFIX = '-ON_POSITION_NED';
BAROMETER_SUFFIX = '-BARO';
GPS_SUFFIX = '-GPS';
RADIO_SUFFIX = '-RADIO';
MIXER_CTR_SUFFIX = '-MIXER_CTR';
ATTITUDE_CTR_SUFFIX = '-ATTITUDE_CTR';
ALTITUDE_CTR_SUFFIX = '-ALTITUDE_CTR';
POSITION_CTR_SUFFIX = '-POSITION_CTR';
G_ATTITUDE_SUFFIX = '-GND_ATTITUDE';
G_POSITION_SUFFIX = '-GND_POSITION';
WAYPOINT_SUFFIX = '-WAYPOINT';
HEARTBEAT_SUFFIX = '-HEARTBEAT';
ATTITUDE_CTR_TEST_SUFFIX = '-ATTITUDE_CTR_TEST';


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
    
    disp(strcat(IMU_RAW_SUFFIX,'(imu_raw_acc_x,imu_raw_acc_y, imu_raw_acc_z, imu_raw_gyro_x, imu_raw_gyro_y, imu_raw_gyro_z, imu_raw_mag_x, imu_raw_mag_y, imu_raw_mag_z, imu_raw_state)'));

catch
end

clear IMU_RAW_SUFFIX;
clear imu_raw_data;
clear imu_raw_file;

try
    o_attitude_file = strcat(LOG_NAME,O_ATTITUDE_SUFFIX,LOG_TYPE);
    o_attitude_data = dlmread(o_attitude_file);
    
    o_attitude_roll = o_attitude_data(:,1);
    o_attitude_pitch = o_attitude_data(:,2);
    o_attitude_yaw = o_attitude_data(:,3);
    o_attitude_p = o_attitude_data(:,4);
    o_attitude_q = o_attitude_data(:,5);
    o_attitude_r = o_attitude_data(:,6);
    o_attitude_state = o_attitude_data(:,7);

    disp(strcat(O_ATTITUDE_SUFFIX,'(o_attitude_roll, o_attitude_pitch, o_attitude_yaw, o_attitude_p, o_attitude_q, o_attitude_r,o_attitude_state)'));
catch
end

clear O_ATTITUDE_SUFFIX;
clear o_attitude_file;
clear o_attitude_data;

try
    o_attitude_q_file = strcat(LOG_NAME,O_ATTITUDE_Q_SUFFIX,LOG_TYPE);
    o_attitude_q_data = dlmread(o_attitude_q_file);
    
    o_attitude_q_vector = o_attitude_q_data(:,1:4);
    o_attitude_q_bias = o_attitude_q_data(:,5:7);
    o_attitude_q_state = o_attitude_q_data(:,8);
    
    disp(strcat(O_ATTITUDE_Q_SUFFIX,'(o_attitude_q_vector, o_attitude_q_bias,o_attitude_q_state)'));
catch  
end

clear o_attitude_q_file;
clear o_attitude_q_data;
clear O_ATTITUDE_Q_SUFFIX;

try
    o_position_body_file = strcat(LOG_NAME,O_POSITION_BODY_SUFFIX,LOG_TYPE);
    o_position_body_data = dlmread(o_position_body_file);
    
    o_position_body_x = o_position_body_data(:,1);
    o_position_body_u = o_position_body_data(:,2);
    o_position_body_u_dot = o_position_body_data(:,3);
    o_position_body_y = o_position_body_data(:,4);
    o_position_body_v = o_position_body_data(:,5);
    o_position_body_v_dot = o_position_body_data(:,6);
    o_position_body_state = o_position_body_data(:,7);

    disp(strcat(O_POSITION_BODY_SUFFIX,'(o_position_body_x, o_position_body_u,o_position_body_u_dot, o_position_body_y, o_position_body_v, o_position_body_v_dot, o_position_body_state)'));
catch    
end

clear o_position_body_file;
clear o_position_body_data;
clear O_POSITION_BODY_SUFFIX;


try
    o_position_ned_file = strcat(LOG_NAME,O_POSITION_NED_SUFFIX,LOG_TYPE);
    o_position_ned_data = dlmread(o_position_ned_file);
    
    o_position_ned_n = o_position_ned_data(:,1);
    o_position_ned_e = o_position_ned_data(:,2);
    o_position_ned_d = o_position_ned_data(:,3);
    o_position_ned_state = o_position_ned_data(:,4);

    disp(strcat(O_POSITION_NED_SUFFIX,'(o_position_ned_n, o_position_ned_e,o_position_ned_d,o_position_ned_state)'));
catch    
end

clear o_position_ned_file;
clear o_position_ned_data;
clear O_POSITION_NED_SUFFIX;

try
    o_altitude_file = strcat(LOG_NAME,O_ALTITUDE_SUFFIX,LOG_TYPE);
    o_altitude_data = dlmread(o_altitude_file);
    
    o_altitude_z = o_altitude_data(:,1);
    o_altitude_w = o_altitude_data(:,2);
    o_altitude_w_dot = o_altitude_data(:,3);
    o_altitude_state = o_altitude_data(:,4);
    
    disp(strcat(O_ALTITUDE_SUFFIX,'(o_altitude_z, o_altitude_w,o_altitude_w_dot, o_altitude_state)'));
catch
end

clear o_altitude_file
clear o_altitude_data
clear O_ALTITUDE_SUFFIX;

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
    position_ctr_ref_n = position_ctr_data(:,3);
    position_ctr_ref_e = position_ctr_data(:,4);
    position_ctr_ref_yaw = position_ctr_data(:,5);
    position_ctr_state = position_ctr_data(:,6);
    
        
    disp(strcat(POSITION_CTR_SUFFIX,'(position_ctr_var_r,position_ctr_var_p,position_ctr_ref_n,position_ctr_ref_e,position_ctr_ref_yaw,position_ctr_state)'));        
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
    g_attitude_file = strcat(LOG_NAME,G_ATTITUDE_SUFFIX,LOG_TYPE);
    g_attitude_data = dlmread(g_attitude_file);
    
    g_attitude_roll = g_attitude_data(:,1);
    g_attitude_pitch = g_attitude_data(:,2);
    g_attitude_yaw = g_attitude_data(:,3);
    g_attitude_state = g_attitude_data(:,4);
    
    disp(strcat(G_ATTITUDE_SUFFIX,'(g_attitude_roll, g_attitude_pitch, g_attitude_yaw, g_attitude_state)'));
catch    
end

clear g_attitude_file;
clear g_attitude_data;
clear G_ATTITUDE_SUFFIX;

try
    g_position_file = strcat(LOG_NAME,G_POSITION_SUFFIX,LOG_TYPE);
    g_position_data = dlmread(g_position_file);
    
    g_position_n = g_position_data(:,1);
    g_position_e = g_position_data(:,2);
    g_position_d = g_position_data(:,3);
    g_position_state = g_position_data(:,4);
    
    disp(strcat(G_POSITION_SUFFIX,'(g_position_n, g_position_e, g_position_e, g_position_state)'));
catch
end

clear g_position_file;
clear g_position_data;
clear G_POSITION_SUFFIX;

try
    waypoint_file = strcat(LOG_NAME,WAYPOINT_SUFFIX,LOG_TYPE);
    waypoint_data = dlmread(waypoint_file);
    
    waypoint_north = waypoint_data(:,1);
    waypoint_east = waypoint_data(:,2); 
    waypoint_z = waypoint_data(:,3);
    waypoint_thrust = waypoint_data(:,4);
    waypoint_state = waypoint_data(:,5);
    
    disp(strcat(WAYPOINT_SUFFIX,'(waypoint_north, waypoint_east, waypoint_z,waypoint_thrust, waypoint_state)'));

catch    
end
clear waypoint_file;
clear waypoint_data;
clear WAYPOINT_SUFFIX;

% AGGIUNGO ATTITUDE_CRT_TEST
try
    attitude_ctr_test_file = strcat(LOG_NAME,ATTITUDE_CTR_TEST_SUFFIX,LOG_TYPE);
    attitude_ctr_test_data = dlmread(attitude_ctr_test_file);
    
    attitude_ctr_test_T = attitude_ctr_test_data(:,1);
    attitude_ctr_test_r = attitude_ctr_test_data(:,2);
    attitude_ctr_test_p = attitude_ctr_test_data(:,3);
    attitude_ctr_test_y = attitude_ctr_test_data(:,4);
    attitude_ctr_test_d2 = attitude_ctr_test_data(:,6);
    attitude_ctr_test_d4 = attitude_ctr_test_data(:,8);
    
    disp(strcat(ATTITUDE_CTR_TEST_SUFFIX,'(attitude_ctr_test_T,attitude_ctr_test_r, attitude_ctr_test_p, attitude_ctr_test_y, attitude_ctr_test_d2, attitude_ctr_test_d4)'));
catch
end

clear attitude_ctr_file;
clear attitude_ctr_data;
clear ATTITUDE_CTR_SUFFIX;

clear LOG_NAME;
clear LOG_TYPE;
clear LOGS_FOLDER;
clear ans;

%% save data

save(SAVE_FILE)
clear SAVE_FILE;

%% clear temp files

cd('../..')

%% END of Code