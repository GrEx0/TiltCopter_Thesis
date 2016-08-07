mean_par_a1 = [-3.878866607, -3.834685535, -4.047992791]; % mean velocity
std_par_a1 = [0.15015509, 0.136170331,0.215205335]

figure
hold on
bar(1:3,mean_par_a1)
errorbar(1:3,mean_par_a1,std_par_a1,'.')