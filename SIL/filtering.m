%% Filtering Acquired Data

d1 = designfilt('lowpassiir','FilterOrder',12,'HalfPowerFrequency',0.06,'DesignMethod','butter');
roll_filtered = filtfilt(d1,o_attitude_roll);
v_filtered = filtfilt(d1,o_position_body_v);

figure
subplot(2,1,1)
plot(t,radio_roll*30);hold on, plot(t,roll_filtered); hold off;
subplot(2,1,2)
plot(t,radio_dE),hold on, plot(v_simulated); plot(t,v_filtered)

figure;
plot(t,radio_dE),hold on, plot(v_simulated); plot(t,v_filtered)