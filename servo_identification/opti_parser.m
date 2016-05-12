%% Import data from Optitrack logging.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all
close all
clc

%% Parsing

IMUsample = 1/100;
offset = 0;
start = 1;
delta = 22000;

filename = 'C:\Users\Mattia\Documents\MATLAB\Parsers\log.txt';
delimiter = ',';
startRow = 2;
formatSpec = '%f%f%f%s%f%f%f%f%f%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN,'HeaderLines' ,startRow-1, 'ReturnOnError', false);
fclose(fileID);
positionx = dataArray{:, 5};
positiony = dataArray{:, 6};
positionz = dataArray{:, 7};
orientation3 = dataArray{:, 8};
orientation2 = dataArray{:, 9};
orientation1 = dataArray{:, 10};
orientation0 = dataArray{:, 11};

positionx = positionx(offset+start:offset+start+delta-1);
positiony = positiony(offset+start:offset+start+delta-1);
positionz = positionz(offset+start:offset+start+delta-1);

orientation3 = orientation3(offset+start:offset+start+delta-1);
orientation2 = orientation2(offset+start:offset+start+delta-1);
orientation1 = orientation1(offset+start:offset+start+delta-1);
orientation0 = orientation0(offset+start:offset+start+delta-1);

OPTItime = (start*IMUsample:IMUsample:(start+delta-1)*IMUsample)';

OPTIposition = [positionx positiony positionz];
OPTIquaternion = [orientation0 -orientation2 -orientation3 orientation1];
OPTIeuler = quatern2euler(OPTIquaternion);

clear ans dataArray delimiter delta fileID filename formatSpec IMUsample start startRow

%% Plot data

figure('name','Optitrack Position')
plot3(positionx, positiony, positionz)
xlabel('x [m]')
ylabel('y [m]')
zlabel('z [m]')
axis equal
title('Optitrack Position')
grid

figure('name', 'Optitrack Quaternion')
plot(OPTItime, OPTIquaternion)
grid minor
title('Optitrack Quaternion')
xlabel('time [s]')
legend('q0', 'q1', 'q2', 'q3')

figure('name', 'Optitrack Euler')
plot(OPTItime, OPTIeuler)
grid minor
title('Optitrack Euler')
xlabel('time [s]')
legend('roll', 'pitch', 'yaw')

%% Save to .mat file
save('OPTIoutput.mat', 'OPTIposition', 'OPTIquaternion', 'OPTIeuler', 'OPTItime')

%% END OF CODE