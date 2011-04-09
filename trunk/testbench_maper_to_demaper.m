% Testbench
clear
clc

% Config params
t_modul_type    = 2;
var             = 0.1;

if (t_modul_type == 0)
    numBitPerSymb = 1;
else
    numBitPerSymb = t_modul_type*2;
end

count = 0;
count_data_in = 2^(numBitPerSymb) - 1;

for k = 0:count_data_in
switch(t_modul_type)
    case 0,
        t_in_data = [mod(k,2)]
    case 1,
        t_in_data = [mod(k,2) mod(fix(k/2),2)]
    case 2,
        t_in_data = [mod(k,2) mod(fix(k/2),2) mod(fix(k/4),2) mod(fix(k/8),2)]
    case 3,
        t_in_data = [mod(k,2) mod(fix(k/2),2) mod(fix(k/4),2) mod(fix(k/8),2) mod(fix(k/16),2) mod(fix(k/32),2)]
    otherwise
        error('unknown modulation format');
end

cons = mapper(t_modul_type,t_in_data);
llr  = demapper(t_modul_type,cons,var);
for m = 1:numBitPerSymb
    t_out_data(m,:) = (llr(m) > 0);
end
t_out_data'
if (t_in_data == t_out_data')
   count = count + 1;
end
end

count
