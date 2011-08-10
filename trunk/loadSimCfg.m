function [ cfg ] = loadSimCfg( fileIdx )

fid = fopen(strcat('cfg/ldpc_',int2str(fileIdx),'.cfg'), 'r');
if (fid == -1)
    error('Cfg file cannot be open');
end

strF = fgets(fid);
while (strF ~= -1),
    % remove spaces
    strC = strF(setdiff(1:length(strF), strfind(strF, ' ')));
    strPosC = strfind(strC, '#');
    if (strPosC)
        strT = strC(1:strPosC(1));
    else
        strT = strC;
    end
    
    % ---modulType ---    			
    strPos1 = strfind(strT, 'modulType');
    if (strPos1)
        cfg.modulType = sscanf(strT,'modulType=%d');
    end
    
    %  --- SNR range ----
    strPos1 = strfind(strT, 'SNRdB');
    if (strPos1)
        ansTmp = sscanf(strT,'SNRdB=%f:%f:%f');
        if (length(ansTmp) ~= 3)
            error('SNR range should be specified as, for example, SNRdB = 1:1:5')
        end
        cfg.startSNRdB      = ansTmp(1);
        cfg.stepSizeSNRdB   = ansTmp(2);
        cfg.endSNRdB        = ansTmp(3);        
    end       

    % ---coderON ---    			
    strPos1 = strfind(strT, 'coderON');
    if (strPos1)
        cfg.coderON = sscanf(strT,'coderON=%d');
    end	
	
     % ---codeRate ---    			
    strPos1 = strfind(strT, 'codeRate');
    if (strPos1)
        cfg.codeRate = sscanf(strT,'codeRate=%f');
    end	   

    % ---minSumAppr ---    			
    strPos1 = strfind(strT, 'minSumAppr');
    if (strPos1)
        cfg.minSumAppr = sscanf(strT,'minSumAppr=%d');
    end	    

    % ---maxIterCount ---    			
    strPos1 = strfind(strT, 'maxIterCount');
    if (strPos1)
        cfg.maxIterCount = sscanf(strT,'maxIterCount=%d');
    end	      
    
     % ---chanelON ---    			
    strPos1 = strfind(strT, 'chanelON');
    if (strPos1)
        cfg.chanelON = sscanf(strT,'chanelON=%d');
    end	      
     
     % ---frameLen ---    			
    strPos1 = strfind(strT, 'frameLen');
    if (strPos1)
        cfg.frameLen = sscanf(strT,'frameLen=%d');
    end	        
	
     % ---seed ---    			
    strPos1 = strfind(strT, 'seed');
    if (strPos1)
        cfg.seed = sscanf(strT,'seed=%d');
    end	   	
	
     % ---saveResToMatFile---    			
    strPos1 = strfind(strT, 'saveResToMatFile');
    if (strPos1)
        cfg.saveResToMatFile = sscanf(strT,'saveResToMatFile=%d');
    end	   		
	
     % ---plotResults---    			
    strPos1 = strfind(strT, 'plotResults');
    if (strPos1)
        cfg.plotResults = sscanf(strT,'plotResults=%d');
    end
    
    % read next string
    strF = fgets(fid);
    
end


end

