% script per il comando in anello aperto thrust motori
clear all; close all; clc

% parametri
nprove = [1:10];
attesa = 2.5;
thr = .35;
ampiezza = 3;
fb_q = 4 * 2*pi;           % freq max in rad/s

pid = [120 .01 2 50];

carica_rbs = 'y';

dispositivo = '/dev/ttyS66';
baudrate = 115200; 

fclose(instrfind);
s = serial(dispositivo,'BaudRate',baudrate, 'DataBits', 8 ,'Terminator', 'CR/LF');
fopen(s);
fprintf(s,'help'); % tattico a inizio comunicazione
if 0 %not(exist('funzionato'))
%    fprintf(s,'sim_raspy 99 1 0');  % calibra
    pause(1)
%    fprintf(s,'sim_raspy 99 2 2 '); % passa in test
    pause(.3)
else
    funzionato = 1;
end

% costruisce vettore rbs di test, oppure lo carica da file
if not(carica_rbs=='y')
    N = 200;             % lunghezza del vettore
    B = ceil(fb_q);     %[rad/s]
    fecc = B/(2*pi);    %[Hz]
    tk   = 1/(2*fecc);  %[s]
    band   = [0 1];    % banda del segnale - espressa in frazioni della freq di niquist
    levels = 1 * [-1, 1];   % campo variazione segnale
    u_ident = idinput(N,'rbs',band,levels);
else
    N = 200;             % lunghezza del vettore
    B = (fb_q);     %[rad/s]
    fecc = B/(2*pi);    %[Hz]
    tk   = 1/(2*fecc);  %[s]
    load('rbs.mat');
end

%return

% lancia sequenza
nome_prova = input('Inserire nome: ', 's');

%% somministra rbs
for KK = nprove
        pause(.5);
        
        % matrice con storia di comando ai vari motori
        dstrb = ampiezza * u_ident(:,KK) * [1 1 -1 -1];

        % avvia motori
        fprintf(s,'test attitude_ctr %2.1f 0 0 0 %2.5f %2.5f %2.5f %2.5f\r',thr/3,pid);
        pause(.5)
        fprintf(s,'test attitude_ctr %2.1f 0 0 0 %2.5f %2.5f %2.5f %2.5f\r',thr/2,pid);
        pause(.5)
        fprintf(s,'test attitude_ctr %2.1f 0 0 0 %2.5f %2.5f %2.5f %2.5f\r',thr,pid);
        pause(.5)

        % logga dati di interesse
        fprintf(s,'log %s o_attitude imu_raw mixer_ctr\r',[nome_prova,'_t',num2str(KK)]);
        pause(.2)

        tic
        for ii = 1 : size(dstrb,1)
            % forse c'è un terminatore in eccesso
            pino = sprintf('test attitude_ctr %2.2f 0 0 0 %2.2f %2.2f %2.2f %2.2f %2.5f %2.5f %2.5f %2.5f\r', ...
                thr,dstrb(ii,1),dstrb(ii,2),dstrb(ii,3),dstrb(ii,4), pid); disp(pino);
            disp(pino)
            unix(sprintf('echo -ne "%s" > /dev/ttyS66', pino));
            pause(tk)   
        end

        disp(sprintf('La somministrazione è durata %3f secondi.', toc))

        % stoppa log 
        fprintf(s,'log stop');
        pause(.1)
        fprintf(s,'log stop');
        pause(.1)

        % ferma motori
            pino = sprintf('test attitude_ctr stop\r', ...
                thr,0,0,0,0); disp(pino);
            disp(pino)
            unix(sprintf('echo -ne "%s" > /dev/ttyS66', pino));
        pause(.5)
            fprintf(s,'test attitude_ctr stop');
        pause(.5)
end
fclose(s);



