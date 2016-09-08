% script per fare software in the loop
Ts = 0.01;
INFLIGHT = 0;                       % In-flight tests, 0 disabled 1 enabled

if INFLIGHT
    t  = Ts * [0:numel(radio_roll)-1];
    sim_time = Ts*numel(radio_roll);
else
    t  = Ts * [0:numel(attitude_ctr_test_r)-1];
    sim_time = Ts*numel(attitude_ctr_test_r);
end

% VERSIONE INFLIGHT
if INFLIGHT
roll_stick  = deg2rad(radio_roll*30);
pitch_stick = deg2rad(radio_pitch*30);
omega = x1(1)*radio_thrust*100+x1(2);
else

% VERSIONE TESTBED
roll_stick  = deg2rad(attitude_ctr_test_r*30);
pitch_stick = deg2rad(attitude_ctr_test_p*30);
radio_dN = zeros(1,length(roll_stick))';
radio_dE = zeros(1,length(roll_stick))';
radio_sec_arm = zeros(1,length(roll_stick))';
end


roll_stick = [t' roll_stick];
pitch_stick = [t' pitch_stick ];


%thrust_stick = [t' omega];
u_stick = [t' radio_dN];
v_stick = [t' radio_dE];
Flight_mode = [t' radio_sec_arm];
