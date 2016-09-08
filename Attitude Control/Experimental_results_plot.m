% This script elaborates the acquired data and plot the results

Ts = 0.01;
t  = Ts * [0:numel(radio_roll)-1];

seconds = 2;
test_bed = [0 0.25 -0.25 0.25 -0.25 0.5 -0.5 0.5 -0.5 0];  % history commands (Roll/RollMax)

Nsamples = seconds/Ts;                                    % number of samples for each command
input_signal = ones(1,length(test_bed)*Nsamples);         % creates a vector with same length of the measured output
nextBlock = 0;                                            % Initialize the block counter
for i=1:length(test_bed)
input_signal(1+nextBlock:nextBlock+Nsamples-1) = input_signal(1+nextBlock:nextBlock+Nsamples-1)*test_bed(i);
nextBlock = nextBlock+Nsamples-1;
end
Ndelay = length(radio_roll)-length(input_signal)+Nsamples+15;
input_signal = [ zeros(1,Ndelay) input_signal]*rad2deg(rollMax);
figure;plot(input_signal);
