% Testbench
clear
clc

% Config params

cfg = loadSimCfg(0);
% cfg.modulType    = 1;
% % --- SNR ----
% cfg.startSNRdB      = -2;
% cfg.stepSizeSNRdB   = 0.5;
% cfg.endSNRdB        = 2;
% % --- Coder/Decoder settings ---
% cfg.coderON         = 1;
% cfg.codeRate        = 0.5;
% cfg.minSumAppr      = 1;
% cfg.maxIterCount    = 20;
% % --- Simullation parameters ---
% cfg.chanelON        = 1;
% cfg.frameLen        = 10;
% cfg.seed            = 13;
% % --- Outputs ------
% cfg.saveResToMatFile = 1;
% cfg.plotResults      = 0;

rand('seed',cfg.seed);
codeWordLen     = 672;
infoWordLen     = codeWordLen*cfg.codeRate;

allVallFlags = [];
allVallFlags_Right = [];


if (cfg.modulType == 0)
    numBitPerSymb = 1;
else
    numBitPerSymb = cfg.modulType*2;
end

count = 0;
count_data_in = 2^(numBitPerSymb) - 1;
SNRdB = cfg.startSNRdB;
for ii = 1:(cfg.endSNRdB-cfg.startSNRdB)/cfg.stepSizeSNRdB
    arrSNRdB(ii)=cfg.startSNRdB + (ii-1)*cfg.stepSizeSNRdB;
end

tic;
for ii = 1:(cfg.endSNRdB-cfg.startSNRdB)/cfg.stepSizeSNRdB
 SNRdB = arrSNRdB(ii)   
 var   = 1./(2.*10.^(SNRdB/10));
 
 infoBER        = [];
 infoBLER       = [];
 codeBLER       = [];
 infoBER_Right  = [];
 infoBLER_Right = [];
 codeBLER_Right = [];
 
 for jj = 1:1:(cfg.frameLen/10000 + 1) 
     infoW = round(rand(1,infoWordLen*cfg.frameLen));

         if cfg.coderON
         codeW = ldpcEncoder(infoW,cfg.frameLen,cfg.codeRate);
         else
         codeW = infoW;
         end

     inCons = mapper(cfg.modulType,codeW);

         if cfg.chanelON
         outCons = chanelAWGN(inCons,SNRdB);
         else
         outCons = inCons;
         end

     llr  = demapper(cfg.modulType,outCons,var);

         if cfg.coderON
          [dataFromDecoder, tmpItCount, validFlagsArr] = ldpcDecoder(llr,cfg.frameLen,cfg.codeRate,cfg.maxIterCount,cfg.minSumAppr);
          [dataFromDecoder_Right, tmpItCount_Right, validFlagsArr_Right] = ldpcDecodeRight(reshape(llr,1,[]), cfg.maxIterCount, cfg.minSumAppr, 0);
         else
         data = llr;
         end
    %  --- my LDPC-decoder results --- 
         itCount(ii) = mean(tmpItCount);
         infoBER =  [infoBER; 1 - mean(dataFromDecoder == infoW)]
         codeBLER = [codeBLER; 1 - mean(validFlagsArr)]
         allVallFlags = [allVallFlags, validFlagsArr];
         infoBLER = [infoBLER; 1 - mean( prod( (reshape(dataFromDecoder,infoWordLen,[]) == reshape(infoW,infoWordLen,[])) * 1 ) )]

    %   --- Right LDPC-decoder results ---
         itCount_Right(ii) =  mean(tmpItCount_Right);
         infoBER_Right =  [infoBER_Right; 1 - mean(dataFromDecoder_Right == infoW)]
         codeBLER_Right = [codeBLER_Right; 1 - mean(validFlagsArr_Right)]
         allVallFlags_Right = [allVallFlags_Right, validFlagsArr_Right];
         infoBLER_Right = [infoBLER_Right; 1 - mean( prod( (reshape(dataFromDecoder_Right,infoWordLen,[]) == reshape(infoW,infoWordLen,[])) * 1 ) )]
 end       
         
         arrInfoBER(ii)         = mean(infoBER);
         arrCodeBLER(ii)        = mean(codeBLER);
         arrInfoBLER(ii)        = mean(infoBLER);
         arrInfoBER_Right(ii)   = mean(infoBER_Right);
         arrCodeBLER_Right(ii)  = mean(codeBLER_Right);
         arrInfoBLER_Right(ii)  = mean(infoBLER_Right);
% --------------------------------------------------
end

if cfg.saveResToMatFile
    switch(cfg.modulType)    
        case 0,
            modulName = 'BPSK';
        case 1,
            modulName = 'QPSK';
        case 2,
            modulName = '16QAM';
        case 3,
            modulName = '64QPSK';
        otherwise
            modulName = 'UnknownModulation';
    end  
    switch (cfg.minSumAppr)
        case 0
            apprName = 'tanh';
        case 1
            apprName = 'minSum';
        otherwise
            apprName = 'UnknownApprox';
    end
    
sFile = strcat('results/res_',modulName,'_',num2str(cfg.startSNRdB),'_',num2str(cfg.endSNRdB),'_frameLen=',int2str(cfg.frameLen),'_',apprName,'_maxIterCount=',int2str(cfg.maxIterCount),'_seed=',int2str(cfg.seed),'.mat');
save(sFile,'arrSNRdB','arrCodeBLER','arrInfoBER','arrInfoBLER','arrCodeBLER_Right','arrInfoBER_Right','arrInfoBLER_Right');
end

if cfg.plotResults
    figure(1)
    semilogy(arrSNRdB,arrCodeBLER,'ko-')
    hold on
    semilogy(arrSNRdB,arrCodeBLER_Right,'kx--')
    if cfg.coderON
        semilogy(arrSNRdB,arrInfoBER,'bo-')
        semilogy(arrSNRdB,arrInfoBLER,'go-')
        semilogy(arrSNRdB,arrInfoBER_Right,'bx--')
        semilogy(arrSNRdB,arrInfoBLER_Right,'gx--')
        legend codeBLER codeBlER_Right infoBER infoBLER infoBER_Right infoBLER_Right
    else
        legend codeBER codeBLER
    end
    grid on;

    hold off;

    figure(2)
    hold on
    plot(arrSNRdB,itCount,'bo-')
    plot(arrSNRdB,itCount_Right,'bx--')
    grid on;
    hold off;
end


    toc