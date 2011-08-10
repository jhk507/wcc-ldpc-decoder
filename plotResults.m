clc
if ~exist('pltArrSNRdB','var')
    pltArrSNRdB = [];
end
if ~exist('pltArrCodeBLER','var')
    pltArrCodeBLER = [];
end
if ~exist('pltArrCodeBLER_Right','var')
    pltArrCodeBLER_Right = [];
end
if ~exist('pltArrInfoBLER','var')
    pltArrInfoBLER = [];
end
if ~exist('pltArrInfoBLER_Right','var')
    pltArrInfoBLER_Right = [];
end
if ~exist('pltArrInfoBER','var')
    pltArrInfoBER = [];
end
if ~exist('pltArrInfoBER_Right','var')
    pltArrInfoBER_Right = [];
end

pltArrSNRdB = [pltArrSNRdB,arrSNRdB];
pltArrCodeBLER = [pltArrCodeBLER, arrCodeBLER];
pltArrCodeBLER_Right = [pltArrCodeBLER_Right, arrCodeBLER_Right];
pltArrInfoBER = [pltArrInfoBER, arrInfoBER];
pltArrInfoBER_Right = [pltArrInfoBER_Right, arrInfoBER_Right];
pltArrInfoBLER = [pltArrInfoBLER, arrInfoBLER];
pltArrInfoBLER_Right = [pltArrInfoBLER_Right, arrInfoBLER_Right];

    figure(1)
    semilogy(pltArrSNRdB,pltArrCodeBLER,'ko-')
    hold on
%     semilogy(pltArrSNRdB,pltArrCodeBLER_Right,'kx--')
    
        semilogy(pltArrSNRdB,pltArrInfoBER,'bo-')
        semilogy(pltArrSNRdB,pltArrInfoBLER,'go-')
%         semilogy(pltArrSNRdB,pltArrInfoBER_Right,'bx--')
%         semilogy(pltArrSNRdB,pltArrInfoBLER_Right,'gx--')
%         legend codeBLER codeBlER_Right infoBER infoBLER infoBER_Right infoBLER_Right
          legend codeBLER infoBER infoBLER
    
    grid on;

    hold off;