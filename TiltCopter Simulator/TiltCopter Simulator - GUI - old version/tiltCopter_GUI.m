function tiltCopter_GUI(hObject,handles)
% Call the simulation with parameters
TiltCopter_Parameters_v2

%% Load Simulation parameters
roll   = str2double(handles.roll_value.String);
pitch  = str2double(handles.pitch_value.String);
yaw    = str2double(handles.yaw_value.String);
height = str2double(handles.height_value.String);
Fx     = str2double(handles.Fx_value.String);
Fy = str2double(handles.Fy_value.String);

%Set point u = [height[m] roll_a[rad] pitch_a[rad] yaw_r[rad/s]]
U = [height; degtorad(roll); pitch; yaw];
tsim = str2double(handles.tsim_value.String);
Fx
Fy
disp(U)
disp(tsim)

options = simset('SrcWorkspace','current', 'DstWorkspace', 'current');
sim(modelname, [], options);

% Retreive simulated data output
handles.P_e     = yout(: ,1:3);
handles.V_b     = yout(: ,4:6);
handles.Ome_b   = yout(: ,7:9);
handles.Alpha_e =  yout(: ,10:12);

% Synchronize handles 
guidata(hObject,handles);

% Plot
axes(handles.Plot_1);
plot(tout, handles.P_e*diag([1 1 -1]));
grid minor
xlabel('[s]')
ylabel('[m]')
legend('N', 'E', 'Height')

axes(handles.Plot_2);
plot(tout, handles.V_b);
grid minor
xlabel('[s]')
ylabel('[m/s]')
legend('u', 'v', 'w')


