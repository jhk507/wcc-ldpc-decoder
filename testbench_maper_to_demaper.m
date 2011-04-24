% Testbench
clear
clc

% Config params
t_modul_type    = 1;
infoWordLen     = 336;
frameLen        = 100;
minSumAppr      = 1;
codeWordLen     = 672;
infoWordLen     = 336;
startSNRdB      = 1;
stepSizeSNRdB   = 1;
endSNRdB        = 25;



if (t_modul_type == 0)
    numBitPerSymb = 1;
else
    numBitPerSymb = t_modul_type*2;
end

count = 0;
count_data_in = 2^(numBitPerSymb) - 1;
SNRdB = startSNRdB;
for ii = 1:(endSNRdB-startSNRdB)/stepSizeSNRdB
    arrSNRdB(ii)=startSNRdB + (ii-1)*stepSizeSNRdB;
end

tic;

for ii = 1:(endSNRdB-startSNRdB)/stepSizeSNRdB
 SNRdB = arrSNRdB(ii)   
 var   = 1./(2.*10.^(SNRdB/10.));
 infoW = round(rand(1,infoWordLen*frameLen));
 codeW = ldpcEncoder(infoW,frameLen);
 
 fid = fopen('vs_projects/ldpcEncoder/ldpcEncoder/code.txt','w');
 fprintf(fid,'%i\n',codeW);
 fclose(fid);
 
 inCons = mapper(t_modul_type,codeW);
 outCons = chanelAWGN(inCons,SNRdB);
 
 llr  = demapper(t_modul_type,outCons,var);
 [data, itCount(ii)] = ldpcDecoder(llr,frameLen,minSumAppr);
 
 out_llr = reshape(llr,[],1);
 
 fid = fopen('vs_projects/ldpcEncoder/ldpcEncoder/llr.txt','w');
 fprintf(fid,'%f\n',llr);
 fclose(fid);
 
 dataFromDecoder = reshape(data>0,1,[]);
 sum(dataFromDecoder == codeW)
 codeBER =  (codeWordLen*frameLen - sum(dataFromDecoder == codeW))/(frameLen*codeWordLen)
 arrCodeBER(ii) = codeBER;
 codeBLER = 0;
 for m = 0:frameLen-1
     codeBLER = codeBLER + ( (codeWordLen - sum(dataFromDecoder(m*codeWordLen + 1:codeWordLen*(m+1)) == codeW(m*codeWordLen + 1:codeWordLen*(m+1)))) > 0);
 end
 codeBLER = codeBLER/frameLen;
 arrCodeBLER(ii) = codeBLER;
 
tmp = reshape(dataFromDecoder,336,[]);
infoWordFromDecoder = reshape(tmp(:,1:2:end),1,[]);
clear tmp;
infoBER =  (infoWordLen*frameLen - sum(infoWordFromDecoder == infoW))/(frameLen*infoWordLen)
arrInfoBER(ii) = infoBER;
end



figure(1)
semilogy(arrSNRdB,arrCodeBER,'ro-')
hold on
semilogy(arrSNRdB,arrInfoBER,'bo-')
grid on;
 figure(2)
 plot(arrSNRdB,codeBLER,'bo-')
toc

 
% for m = 1:numBitPerSymb
%     t_out_data(m,:) = (llr(m) > 0);
% end
% t_out_data'
% if (t_in_data == t_out_data')
%    count = count + 1;
% end
%end

