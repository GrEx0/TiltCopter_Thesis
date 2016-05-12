%% Servo motor identification 

% Initial estimate of denumerator 
A_0_est = []

% order of denumerator
n = 
% order of numerator
m = 

% Sampling time
Ts = 
% Number of samples
N_samples =

% Raw data
y_raw = 
u_raw = x


for i:n
    y_filter = A_0_est
    y_filtered(i) = y_filter*y_raw(i)