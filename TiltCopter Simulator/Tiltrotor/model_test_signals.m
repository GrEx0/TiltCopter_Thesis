% Input/Output data from the identification campaign
load('test_hovering');



% motors input
% conversion from pwm -> TH% is TH% = 0.1 * PWM - 100
m_th = 0.1;
q_th = -100;
control_motor_4 = mixer_ctr_motor_4*m_th + q_th;
control_motor_2 = mixer_ctr_motor_2*m_th + q_th;
control_motor_1 = mixer_ctr_motor_1*m_th + q_th;
control_motor_3 = mixer_ctr_motor_3*m_th + q_th;

% servomotors input3
q_servo =1.5000e+03;
m_servo = 572.9578;
t  = .01 * [0:numel(mixer_ctr_servo_1)-1];
t = t';

control_servo_1  = (mixer_ctr_servo_1-q_servo)*1/m_servo*180/pi;
control_servo_2  = (mixer_ctr_servo_2-q_servo)*1/m_servo*180/pi;
control_servo_3  = (mixer_ctr_servo_3-q_servo)*1/m_servo*180/pi;
control_servo_4  = (mixer_ctr_servo_4-q_servo)*1/m_servo*180/pi;

control_servo_1 = [t control_servo_1];
control_servo_2 = [t control_servo_2];
control_servo_3 = [t control_servo_3];
control_servo_4 = [t control_servo_4];

control_motor_1 = [t control_motor_1];
control_motor_2 = [t control_motor_2];
control_motor_3 = [t control_motor_3];
control_motor_4 = [t control_motor_4];

u = [ control_motor_1; control_motor_2;control_motor_3;control_motor_4;...
      control_servo_1;control_servo_2;control_servo_3;control_servo_4 ];
  