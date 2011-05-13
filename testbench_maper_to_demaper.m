% Testbench
clear
clc

% Config params
t_modul_type    = 0;
frameLen        = 100;
minSumAppr      = 0;
infoWordLen     = 336;
startSNRdB      = -5;
stepSizeSNRdB   = 1;
endSNRdB        = 10;
coderON         = 1;
rate            = 0.5;
chanelON        = 1;

if coderON
    codeWordLen = infoWordLen/rate;
else
    codeWordLen = infoWordLen;
end


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
 var   = 1./(2.*10.^(SNRdB/10));
 infoW = round(rand(1,infoWordLen*frameLen));
 
     if coderON
     codeW = ldpcEncoder(infoW,frameLen);
     else
     codeW = infoW;
     end
 
 fid = fopen('vs_projects/ldpcEncoder/ldpcEncoder/code.txt','w');
 fprintf(fid,'%i\n',codeW);
 fclose(fid);
 
 inCons = mapper(t_modul_type,codeW);
 
     if chanelON
     outCons = chanelAWGN(inCons,SNRdB);
     else
     outCons = inCons;
     end
 
 llr  = demapper(t_modul_type,outCons,var);
 
     if coderON
     [data, itCount(ii)] = ldpcDecoder(llr,frameLen,minSumAppr);
     else
     data = llr;
     end
 
 out_llr = reshape(llr,[],1);
 
 fid = fopen('vs_projects/ldpcEncoder/ldpcEncoder/llr.txt','w');
 fprintf(fid,'%f\n',llr);
 fclose(fid);
 
 dataFromDecoder = reshape(data>0,1,[]);
 sum(dataFromDecoder == codeW);
 codeBER =  (codeWordLen*frameLen - sum(dataFromDecoder == codeW))/(frameLen*codeWordLen)
 arrCodeBER(ii) = codeBER;
 codeBLER = 0;
 for m = 0:frameLen-1
     codeBLER = codeBLER + ( (codeWordLen - sum(dataFromDecoder(m*codeWordLen + 1:codeWordLen*(m+1)) == codeW(m*codeWordLen + 1:codeWordLen*(m+1)))) > 0);
 end
 codeBLER = codeBLER/frameLen
 arrCodeBLER(ii) = codeBLER;

if coderON
    tmp = reshape(dataFromDecoder,336,[]);
    infoWordFromDecoder = reshape(tmp(:,1:2:end),1,[]);
    clear tmp;
    infoBER =  (infoWordLen*frameLen - sum(infoWordFromDecoder == infoW))/(frameLen*infoWordLen)
    infoBLER = 0;
    for m = 0:frameLen-1
      infoBLER = infoBLER + ( (infoWordLen - sum(infoWordFromDecoder(m*infoWordLen + 1:infoWordLen*(m+1)) == infoW(m*infoWordLen + 1:infoWordLen*(m+1)))) > 0);
    end
    infoBLER = infoBLER/frameLen
    arrInfoBLER(ii) = infoBLER;
    arrInfoBER(ii) = infoBER;
end
end




figure(1)
semilogy(arrSNRdB,arrCodeBER,'ro-')
hold on
semilogy(arrSNRdB,arrCodeBLER,'ko-')
if coderON
    semilogy(arrSNRdB,arrInfoBER,'bo-')
    semilogy(arrSNRdB,arrInfoBLER,'go-')
    legend codeBER codeBLER infoBER infoBLER
else
    legend codeBER codeBLER
end
grid on;


toc
