% Testbench
clear
clc

% Config params
t_modul_type    = 2;
var             = 0.2;
infoWordLen     = 336;
frameLen        = 10;
minSumAppr      = 0;

if (t_modul_type == 0)
    numBitPerSymb = 1;
else
    numBitPerSymb = t_modul_type*2;
end

count = 0;
count_data_in = 2^(numBitPerSymb) - 1;

 infoW = round(rand(1,infoWordLen*frameLen));
 codeW = ldpcEncoder(infoW,frameLen);
 
 cons = mapper(t_modul_type,codeW);
 llr  = demapper(t_modul_type,cons,var);
 data = ldpcDecoder(llr,frameLen,var,minSumAppr);
 
 out_llr = reshape(llr,[],1);
 
 fid = fopen('llr.txt','w');
 fprintf(fid,'%f\n',llr);
 fclose(fid);
 
 dataFromDecoder = reshape(data>0,1,[]);
 sum(dataFromDecoder == codeW)     
 
 
% for m = 1:numBitPerSymb
%     t_out_data(m,:) = (llr(m) > 0);
% end
% t_out_data'
% if (t_in_data == t_out_data')
%    count = count + 1;
% end
%end

