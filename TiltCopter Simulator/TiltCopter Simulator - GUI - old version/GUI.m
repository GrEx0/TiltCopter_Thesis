function varargout = GUI(varargin)
% GUI MATLAB code for GUI.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI

% Last Modified by GUIDE v2.5 24-Apr-2016 17:33:10

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI is made visible.
function GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI (see VARARGIN)

% Choose default command line output for GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI wait for user response (see UIRESUME)
% uiwait(handles.GUI);

% % Create the data to plot.
% handles.peaks=peaks(35);
% handles.membrane=membrane;
% [x,y] = meshgrid(-8:.5:8);
% r = sqrt(x.^2+y.^2) + eps;
% sinc = sin(r)./r;
% handles.sinc = sinc;
% % Set the current data value.
% handles.current_data = handles.peaks;
% surf(handles.current_data)


% Variable definitions
global index_view;
global old_position;
global ad
index_view = 0;
old_position = [0 0 0];
paramFile='TiltCopter_Parameters_v2';
handles.paramFile = paramFile;

guidata(hObject,handles);

% Set Plot_1 axes properties
    xlabel(handles.Plot_1,'Time [s]');
    ylabel(handles.Plot_1,'Position [m]');
    title(handles.Plot_1,'Earth Frame Position');
    grid(handles.Plot_1,'on');
    box(handles.Plot_1,'on');
   
% The the parameters for the 3D plot
    set(hObject,'menubar','figure','renderer','opengl');
    set(handles.Plot_2,'Visible','On','Box','On','XGrid', 'on','YGrid', 'on','ZGrid',...
        'on','projection','perspective'); 
    hold on;
    cameratoolbar('show');
    axis vis3d;
    view(3);
    zoom(0.9);
    

% --- Outputs from this function are returned to the command line.
function varargout = GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function to update Simulink parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function updateSimulink(handles)

%Update SIM model

% Function to obtain the fields of a block
%get_param(handles.block_Thrust_ref,'dialogparameters')
set_param(handles.block_Roll_ref,'After',handles.roll_value.String);
set_param(handles.block_Pitch_ref,'After',handles.pitch_value.String);
set_param(handles.block_Yaw_ref,'After',handles.yaw_value.String);
set_param(handles.block_Thrust_ref,'After',handles.height_value.String);
set_param(handles.block_Fx,'Value',handles.Fx_value.String);
set_param(handles.block_Fy,'Value',handles.Fy_value.String);
set_param(handles.modelname,'StopTime',handles.sim_time.String);

if handles.checkbox_h.Value == 1
    set_param(handles.block_Thrust_ref,'Time',handles.h_time.String);
else
    set_param(handles.block_Thrust_ref,'Time','0');
end

%Checkbox Roll
if handles.checkbox_r.Value == 1
    set_param(handles.block_Roll_ref,'Time',handles.r_time.String);
else
    set_param(handles.block_Roll_ref,'Time','0');
end
%Checkbox Pitch
if handles.checkbox_p.Value == 1
    set_param(handles.block_Pitch_ref,'Time',handles.p_time.String);
else
    set_param(handles.block_Pitch_ref,'Time','0');
end
%Checkbox yaw
if handles.checkbox_y.Value == 1
    set_param(handles.block_Yaw_ref,'Time',handles.y_time.String);
else
    set_param(handles.block_Yaw_ref,'Time','0');
end

% --- Executes on button press in Load_btn.
function Load_btn_Callback(hObject, eventdata, handles)
% hObject    handle to Load_btn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
modelname = handles.Model_name.String;
handles.modelname = modelname;
% Do some simple error checking on the input
if ~localValidateInputs(modelname)
    estr = sprintf('The model %s.mdl cannot be found.',modelname);
    errordlg(estr,'Model not found error','modal');
    return
end

% Load the model if required (it may have been closed manually).
if ~modelIsLoaded(modelname)
    load_system(modelname);
%     options = simset('SrcWorkspace','current', 'DstWorkspace', 'current');
% sim(modelname, [], options);
end

% Define a struct for blocks that are to have listeners applied
handles.viewing = struct(...
    'blockName','',...
    'blockHandle',[],...
    'blockEvent','',...
    'blockFcn',[],...
    'lineHandles',[]);

% Set the listener for the P_e Scope
% Every block has a name
handles.viewing(1).blockName = sprintf('%s/P_e_Scope',handles.modelname);
% (This will be used in the graphics drawing callback, and is done here
% as it should speed things up rather than searching for the handle
% during every event callback.)
handles.viewing(1).blockHandle = get_param(handles.viewing(1).blockName,'Handle');
% List the block event to be listened for
handles.viewing(1).blockEvent = 'PostOutputs';
% (These must be subfunctions within this mfile).
handles.viewing(1).blockFcn = @localEventListener;


% %Set the listener for the Alpha_e Scope
% % Every block has a name
% handles.viewing(2).blockName = sprintf('%s/Alpha_e_Scope',handles.modelname);
% % (This will be used in the graphics drawing callback, and is done here
% % as it should speed things up rather than searching for the handle
% % during every event callback.)
% handles.viewing(2).blockHandle = get_param(handles.viewing(2).blockName,'Handle');
% % List the block event to be listened for
% handles.viewing(2).blockEvent = 'PostOutputs';
% % (These must be subfunctions within this mfile).
% handles.viewing(2).blockFcn = @localEventListener;

% Define parameters
handles.block_Thrust_ref      = sprintf('%s/Thrust_ref',modelname);
handles.block_Roll_ref        = sprintf('%s/Roll_ref',modelname);
handles.block_Pitch_ref       = sprintf('%s/Pitch_ref',modelname);
handles.block_Yaw_ref         = sprintf('%s/Yaw_ref',modelname);
handles.block_Fx              = sprintf('%s/Fx_ref',modelname);
handles.block_Fy              = sprintf('%s/Fy_ref',modelname);


%Get the simulink values and loads into GUI
Thrust_ref = get_param(handles.block_Thrust_ref,'Time');

Fx=get_param(handles.block_Fx,'Value');
Fy=get_param(handles.block_Fy,'Value');

% Put an empty line on the axes for each signal that will be
% monitored
% Save the line handles, which will be useful to have in an
% array during the graphics updating routine.
%             nlines = 3*length(handles.viewing);   
              nlines = 3;
              nviewings = length(handles.viewing);
            hl = nan(1,nlines);
%             colourOrder = get(handles.Plot_1,'ColorOrder');
%             colourOrder_2 = get(handles.Plot_2,'ColorOrder');
%             for idx = 1:nlines
%                 if idx <=3
%                 hl(idx) = line('Parent',handles.Plot_1,...
%                     'XData',[],...
%                     'YData',[],...
%                     'Color',colourOrder(mod(idx-1,size(colourOrder,1))+1,:),...
%                     'EraseMode','xor',...
%                     'Tag',sprintf('signalLine%d',idx));
%                 else
%                     hl(idx) = line('Parent',handles.Plot_2,...
%                     'XData',[],...
%                     'YData',[],...
%                     'Color',colourOrder(mod(idx-1,size(colourOrder,1))+1,:),...
%                     'EraseMode','xor',...
%                     'Tag',sprintf('signalLine%d',idx));
%                 end
%             end
            for idv = 1:nviewings
                switch idv
                    case 1
                        colourOrder   = get(handles.Plot_1,'ColorOrder');
                        Parent_figure = handles.Plot_1;
                        Plot_axe      = handles.Plot_1;
%                     case 2
%                          colourOrder = get(handles.Plot_2,'ColorOrder');
%                           Parent_figure = handles.Plot_2;
%                           Plot_axe      = handles.Plot_2;
                end
             
                for idx = 1:nlines
                     hl(idx) = line('Parent',Parent_figure,...
                    'XData',[],...
                    'YData',[],...
                    'Color',colourOrder(mod(idx-1,size(colourOrder,1))+1,:),...
                    'EraseMode','xor',...
                    'Tag',sprintf('signalLine%d',idx));
                end
                handles.viewing(idv).lineHandles = hl;
                legend(Plot_axe,'N','E','D');
            end
            
%             handles.lineHandles = hl;
%             legend(handles.Plot_1,'N','E','D');
             guidata(hObject,handles);

set(handles.Start_sim,'Enable','on');
msgbox('Model loaded','Success');



% --- Executes on button press in Start_sim.
function Start_sim_Callback(hObject, eventdata, handles)
% hObject    handle to Start_sim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

flag=get(hObject,'string');

if strcmp(flag,'Start Simulation')==1
        set(hObject,'string','Stop Simulation');
        
        resetGraph(handles)
        % Call the simulation with parameters
        % Update Simulink values with current
        updateSimulink(handles)
        run(handles.paramFile);
        
%         % set the simulation mode to normal
%         set_param(handles.modelname,'SimulationMode','normal');
%         
%         % Set a listener on the Blocks in the model's StartFcn
%        % set_param(handles.modelname,'StartFcn','localAddEventListener');
%         
%         %Start the simulation
%         set_param(handles.modelname,'SimulationCommand','Start');

% The axes limits may also need changing
newXLim = [0 str2num(handles.sim_time.String)];
set(handles.Plot_1,'Xlim',newXLim);
newYLim = [-2 -str2num(handles.height_value.String)+2];
set(handles.Plot_1,'Xlim',newXLim);
set(handles.Plot_1,'Ylim',newYLim);
        % set the stop time
        set_param(handles.modelname,'StopTime',handles.sim_time.String);
        % set the simulation mode to normal
        set_param(handles.modelname,'SimulationMode','normal');
        % Set a listener on the Gain block in the model's StartFcn
      set_param(handles.modelname,'StartFcn','localAddEventListener');
        % start the model
        set_param(handles.modelname,'SimulationCommand','start');
       
else
        set_param(handles.modelname,'SimulationCommand','Stop');
        set(hObject,'string','Start Simulation');
end





function simulation_time_Callback(hObject, eventdata, handles)
% hObject    handle to simulation_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of simulation_time as text
%        str2double(get(hObject,'String')) returns contents of simulation_time as a double


% --- Executes during object creation, after setting all properties.
function simulation_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to simulation_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function height_value_Callback(hObject, eventdata, handles)
% hObject    handle to height_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of height_value as text
%        str2double(get(hObject,'String')) returns contents of height_value as a double


% --- Executes during object creation, after setting all properties.
function height_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to height_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function roll_value_Callback(hObject, eventdata, handles)
% hObject    handle to roll_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of roll_value as text
%        str2double(get(hObject,'String')) returns contents of roll_value as a double


% --- Executes during object creation, after setting all properties.
function roll_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to roll_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function pitch_value_Callback(hObject, eventdata, handles)
% hObject    handle to pitch_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of pitch_value as text
%        str2double(get(hObject,'String')) returns contents of pitch_value as a double


% --- Executes during object creation, after setting all properties.
function pitch_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pitch_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function yaw_value_Callback(hObject, eventdata, handles)
% hObject    handle to yaw_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of yaw_value as text
%        str2double(get(hObject,'String')) returns contents of yaw_value as a double


% --- Executes during object creation, after setting all properties.
function yaw_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to yaw_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Fx_value_Callback(hObject, eventdata, handles)
% hObject    handle to Fx_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fx_value as text
%        str2double(get(hObject,'String')) returns contents of Fx_value as a double


% --- Executes during object creation, after setting all properties.
function Fx_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fx_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Fy_value_Callback(hObject, eventdata, handles)
% hObject    handle to Fy_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fy_value as text
%        str2double(get(hObject,'String')) returns contents of Fy_value as a double


% --- Executes during object creation, after setting all properties.
function Fy_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fy_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function GUI_CreateFcn(hObject, eventdata, handles)
% hObject    handle to GUI (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% add some additional data as a new field called numberOfErrors



function tsim_value_Callback(hObject, eventdata, handles)
% hObject    handle to tsim_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of tsim_value as text
%        str2double(get(hObject,'String')) returns contents of tsim_value as a double


% --- Executes during object creation, after setting all properties.
function tsim_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to tsim_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to height_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of height_value as text
%        str2double(get(hObject,'String')) returns contents of height_value as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to height_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to roll_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of roll_value as text
%        str2double(get(hObject,'String')) returns contents of roll_value as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to roll_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit12_Callback(hObject, eventdata, handles)
% hObject    handle to pitch_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of pitch_value as text
%        str2double(get(hObject,'String')) returns contents of pitch_value as a double


% --- Executes during object creation, after setting all properties.
function edit12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pitch_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit13_Callback(hObject, eventdata, handles)
% hObject    handle to yaw_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of yaw_value as text
%        str2double(get(hObject,'String')) returns contents of yaw_value as a double


% --- Executes during object creation, after setting all properties.
function edit13_CreateFcn(hObject, eventdata, handles)
% hObject    handle to yaw_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit14_Callback(hObject, eventdata, handles)
% hObject    handle to Fx_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fx_value as text
%        str2double(get(hObject,'String')) returns contents of Fx_value as a double


% --- Executes during object creation, after setting all properties.
function edit14_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fx_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit15_Callback(hObject, eventdata, handles)
% hObject    handle to Fy_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fy_value as text
%        str2double(get(hObject,'String')) returns contents of Fy_value as a double


% --- Executes during object creation, after setting all properties.
function edit15_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fy_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when Panel_axes is resized.
function Panel_axes_SizeChangedFcn(hObject, eventdata, handles)
% hObject    handle to Panel_axes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in Surf.
function Surf_Callback(hObject, eventdata, handles)
% hObject    handle to Surf (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in Stop_sim.
function Stop_sim_Callback(hObject, eventdata, handles)
% hObject    handle to Stop_sim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function to ensure that the model actually exists
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function modelExists = localValidateInputs(modelname)

num = exist(modelname,'file');
if num == 4
    modelExists = true;
else
    modelExists = false;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function to check that model is still loaded
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function modelLoaded = modelIsLoaded(modelname)

try
    modelLoaded = ...
        ~isempty(find_system('Type','block_diagram','Name',modelname));
catch ME %#ok
    % Return false if the model can't be found
    modelLoaded = false;
end


% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox1



function sim_time_Callback(hObject, eventdata, handles)
% hObject    handle to sim_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sim_time as text
%        str2double(get(hObject,'String')) returns contents of sim_time as a double


% --- Executes during object creation, after setting all properties.
function sim_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sim_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit19_Callback(hObject, eventdata, handles)
% hObject    handle to height_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of height_value as text
%        str2double(get(hObject,'String')) returns contents of height_value as a double


% --- Executes during object creation, after setting all properties.
function edit19_CreateFcn(hObject, eventdata, handles)
% hObject    handle to height_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit20_Callback(hObject, eventdata, handles)
% hObject    handle to roll_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of roll_value as text
%        str2double(get(hObject,'String')) returns contents of roll_value as a double


% --- Executes during object creation, after setting all properties.
function edit20_CreateFcn(hObject, eventdata, handles)
% hObject    handle to roll_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit21_Callback(hObject, eventdata, handles)
% hObject    handle to pitch_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of pitch_value as text
%        str2double(get(hObject,'String')) returns contents of pitch_value as a double


% --- Executes during object creation, after setting all properties.
function edit21_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pitch_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit22_Callback(hObject, eventdata, handles)
% hObject    handle to Fx_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fx_value as text
%        str2double(get(hObject,'String')) returns contents of Fx_value as a double


% --- Executes during object creation, after setting all properties.
function edit22_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fx_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit23_Callback(hObject, eventdata, handles)
% hObject    handle to Fy_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fy_value as text
%        str2double(get(hObject,'String')) returns contents of Fy_value as a double


% --- Executes during object creation, after setting all properties.
function edit23_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fy_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit24_Callback(hObject, eventdata, handles)
% hObject    handle to yaw_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of yaw_value as text
%        str2double(get(hObject,'String')) returns contents of yaw_value as a double


% --- Executes during object creation, after setting all properties.
function edit24_CreateFcn(hObject, eventdata, handles)
% hObject    handle to yaw_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox2

 % Turn off the Build button
       
       

% --- Executes on button press in checkbox_r.
function checkbox_r_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_r (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_r
if handles.checkbox_r.Value == 1
 set(handles.r_time,'Enable','on')
else
 set(handles.r_time,'Enable','off')   
end

% --- Executes on button press in checkbox_p.
function checkbox_p_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_p (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_p
if handles.checkbox_p.Value == 1
 set(handles.p_time,'Enable','on')
else
 set(handles.p_time,'Enable','off')   
end

% --- Executes on button press in checkbox_y.
function checkbox_y_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_y
if handles.checkbox_y.Value == 1
 set(handles.y_time,'Enable','on')
else
 set(handles.y_time,'Enable','off')   
end

% --- Executes on button press in checkbox_Fx.
function checkbox_Fx_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Fx (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_Fx
if handles.checkbox_Fx.Value == 1
 set(handles.Fx_time,'Enable','on')
else
 set(handles.Fx_time,'Enable','off')   
end

% --- Executes on button press in checkbox_Fy.
function checkbox_Fy_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Fy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_Fy
if handles.checkbox_Fy.Value == 1
 set(handles.Fy_time,'Enable','on')
else
 set(handles.Fy_time,'Enable','off')   
end


function h_time_Callback(hObject, eventdata, handles)
% hObject    handle to h_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of h_time as text
%        str2double(get(hObject,'String')) returns contents of h_time as a double


% --- Executes during object creation, after setting all properties.
function h_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to h_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function r_time_Callback(hObject, eventdata, handles)
% hObject    handle to r_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of r_time as text
%        str2double(get(hObject,'String')) returns contents of r_time as a double


% --- Executes during object creation, after setting all properties.
function r_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to r_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function p_time_Callback(hObject, eventdata, handles)
% hObject    handle to p_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of p_time as text
%        str2double(get(hObject,'String')) returns contents of p_time as a double


% --- Executes during object creation, after setting all properties.
function p_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to p_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Fx_time_Callback(hObject, eventdata, handles)
% hObject    handle to Fx_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fx_time as text
%        str2double(get(hObject,'String')) returns contents of Fx_time as a double


% --- Executes during object creation, after setting all properties.
function Fx_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fx_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Fy_time_Callback(hObject, eventdata, handles)
% hObject    handle to Fy_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fy_time as text
%        str2double(get(hObject,'String')) returns contents of Fy_time as a double


% --- Executes during object creation, after setting all properties.
function Fy_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fy_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function y_time_Callback(hObject, eventdata, handles)
% hObject    handle to y_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of y_time as text
%        str2double(get(hObject,'String')) returns contents of y_time as a double


% --- Executes during object creation, after setting all properties.
function y_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to y_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_h.
function checkbox_h_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_h (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_h
if handles.checkbox_h.Value == 1
 set(handles.h_time,'Enable','on')
else
 set(handles.h_time,'Enable','off')   
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function to ensure that the model actually exists
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


function Model_name_Callback(hObject, eventdata, handles)
% hObject    handle to Model_name (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Model_name as text
%        str2double(get(hObject,'String')) returns contents of Model_name as a double


% --- Executes during object creation, after setting all properties.
function Model_name_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Model_name (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Callback Function for adding an event listener to the gain block
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function localAddEventListener
% get the application data
handles = guidata(gcbo);

% For this example all events call into the same function
handles.eventHandle = cell(1,length(handles.viewing));

for idx = 1:length(handles.viewing)
        handles.eventHandle{idx} = ...
        add_exec_event_listener(handles.viewing(idx).blockName,...
        handles.viewing(idx).blockEvent, handles.viewing(idx).blockFcn);
end
% store the changed app data
guidata(gcbo,handles);

function localEventListener(block, eventdata) %#ok

% Note: this callback is called by all the block listeners.  No effort has
% been made to time synchronise the data from each signal.  Rather it is
% assumed that since each block calls this function at every time step and
% hence the time synchronisation will come "for free".  This may not be the
% case for other models and additional code may be required for them to
% work/display data correctly.
% get the application data
hf = findall(0,'tag',mfilename);
ad = guidata(hf);
% Get the handle to the line that currently needs updating
thisLineHandle = ad.viewing([ad.viewing.blockHandle]==block.BlockHandle).lineHandles;
% Height correction
if (ad.viewing(1).blockHandle == block.BlockHandle)
    Gain = -1;
else
    Gain = 1;
end
draw_mod_gui(block.InputPort(1).Data)
for i=1:length(thisLineHandle)
% Get the data currently being displayed on the axis
xdata = get(thisLineHandle(i),'XData');
ydata = get(thisLineHandle(i),'YData');
% Get the simulation time and the block data
sTime = block.CurrentTime;
if i==3
   data =  Gain*block.InputPort(1).Data(i);
else
    data =  block.InputPort(1).Data(i);
end
    newXData = [xdata sTime];
    newYData = [ydata data];


% Display the new data set
if (mod(sTime,0.002)== 0)
set(thisLineHandle(i),...
    'XData',newXData,...
    'YData',newYData);
end


end



% --- Executes on button press in Clear_btn.
function Clear_btn_Callback(hObject, eventdata, handles)
% hObject    handle to Clear_btn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
resetGraph(handles)

function resetGraph(handles)
       % reset the line(s)
        for idv = 1:length(handles.viewing)
            for idx = 1:length(handles.viewing(idv).lineHandles)
                set(handles.viewing(idv).lineHandles(idx),'XData',[],'YData',[]);
            end
        end
