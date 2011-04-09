function LLR = demapper(modul_type, in_data, var)
%-------------------------------------------------------------------------- 
% DESCRIPTION:
%
% LLR = demapper(ModulType, in_data, var)
%
% Calculates LLR of the received bits from the received symbols
%
% INPUTS:
% in_data    - input QAM symbols
% modul_type - type of modulation (0 - BPSK, 1 - QPSK, 2 - 16QAM, 3 - 64QAM)
% var        - variance of noise
% 
% OUTPUTS:
% LLR - demapped bits LLRs
%--------------------------------------------------------------------------   

switch(modul_type)
    case  0, %BPSK
        LLR = real(in_data)*(2./var);
    case  1, %QPSK
        symb = real(in_data.*exp(1j.*pi./4).*sqrt(2));
        LLR(1,:) = symb.*(2./(2.*var));
        
        symb = imag(in_data.*exp(1j.*pi./4).*sqrt(2));
        LLR(2,:) = symb.*(2./(2.*var));
    case 2, %16-QAM
        symb = real(in_data.*sqrt(10));
        
        idx = find(symb<-2);            
        LLR(1,idx) = 2.*symb(idx) + 2.;
        LLR(2,idx) =    symb(idx) + 2.;
        
        idx = find((symb>=-2) & (symb<0));
        LLR(1,idx) =    symb(idx);
        LLR(2,idx) =    symb(idx) + 2.;
        
        idx = find((symb>=0) & (symb<=2));
        LLR(1,idx) =    symb(idx);
        LLR(2,idx) =   -symb(idx) + 2.;
        
        idx = find(symb>2);
        LLR(1,idx) = 2.*symb(idx) - 2.;
        LLR(2,idx) =   -symb(idx) + 2.;
        
        symb = imag(in_data.*sqrt(10));
        
        idx = find(symb<-2);            
        LLR(3,idx) = 2.*symb(idx) + 2.;
        LLR(4,idx) =    symb(idx) + 2.;
        
        idx = find((symb>=-2) & (symb<0));
        LLR(3,idx) =    symb(idx);
        LLR(4,idx) =    symb(idx) + 2.;
        
        idx = find((symb>=0) & (symb<=2));
        LLR(3,idx) =    symb(idx);
        LLR(4,idx) =   -symb(idx) + 2.;
        
        idx = find(symb>2);
        LLR(3,idx) = 2.*symb(idx) - 2.;
        LLR(4,idx) =   -symb(idx) + 2.;  
        
        LLR(1,:) = LLR(1,:)*(2./(10.*var));
        LLR(2,:) = LLR(2,:)*(2./(10.*var));       
        LLR(3,:) = LLR(3,:)*(2./(10.*var));       
        LLR(4,:) = LLR(4,:)*(2./(10.*var));
    case 3, %64-QAM
        symb = real(in_data.*sqrt(42));
        
        idx = find(symb<-6);
        LLR(1,idx) = 4.*symb(idx) + 12.;
        LLR(2,idx) = 2.*symb(idx) + 10.;
        LLR(3,idx) =    symb(idx) + 6. ;
        
        idx = find((symb>= -6) & (symb<-4));
        LLR(1,idx) = 3.*symb(idx) + 6.;
        LLR(2,idx) =    symb(idx) + 4.;
        LLR(3,idx) =    symb(idx) + 6.;
        
        idx = find((symb>= -4) & (symb<-2));
        LLR(1,idx) = 2.*symb(idx) + 2.;
        LLR(2,idx) =    symb(idx) + 4.;
        LLR(3,idx) =   -symb(idx) - 2.;
        
        idx = find((symb>= -2) & (symb<0));
        LLR(1,idx) =    symb(idx);
        LLR(2,idx) = 2.*symb(idx) + 6.;
        LLR(3,idx) =   -symb(idx) - 2.;        
        
        idx = find((symb>= 0) & (symb<=2));
        LLR(1,idx) =    symb(idx);
        LLR(2,idx) = -2.*symb(idx) + 6.;
        LLR(3,idx) =   -symb(idx) - 2.;   
        
        idx = find((symb>  2) & (symb<=4));
        LLR(1,idx) = 2.*symb(idx) - 2.;
        LLR(2,idx) =   -symb(idx) + 4.;
        LLR(3,idx) =    symb(idx) - 2.;
        
        idx = find((symb>  4) & (symb<=6));
        LLR(1,idx) = 3.*symb(idx) - 6.;
        LLR(2,idx) =   -symb(idx) + 4.;
        LLR(3,idx) =   -symb(idx) + 6.;
        
        idx = find(symb>6);
        LLR(1,idx) =  4.*symb(idx) - 12.;
        LLR(2,idx) = -2.*symb(idx) + 10.;
        LLR(3,idx) =    -symb(idx) + 6. ;
        
        symb = imag(in_data.*sqrt(42));
        
        idx = find(symb<-6);
        LLR(4,idx) = 4.*symb(idx) + 12.;
        LLR(5,idx) = 2.*symb(idx) + 10.;
        LLR(6,idx) =    symb(idx) + 6. ;
        
        idx = find((symb>= -6) & (symb<-4));
        LLR(4,idx) = 3.*symb(idx) + 6.;
        LLR(5,idx) =    symb(idx) + 4.;
        LLR(6,idx) =    symb(idx) + 6.;
        
        idx = find((symb>= -4) & (symb<-2));
        LLR(4,idx) = 2.*symb(idx) + 2.;
        LLR(5,idx) =    symb(idx) + 4.;
        LLR(6,idx) =   -symb(idx) - 2.;
        
        idx = find((symb>= -2) & (symb<0));
        LLR(4,idx) =    symb(idx);
        LLR(5,idx) = 2.*symb(idx) + 6.;
        LLR(6,idx) =   -symb(idx) - 2.;        
        
        idx = find((symb>= 0) & (symb<=2));
        LLR(4,idx) =    symb(idx);
        LLR(5,idx) = -2.*symb(idx) + 6.;
        LLR(6,idx) =   -symb(idx) - 2.;   
        
        idx = find((symb>  2) & (symb<=4));
        LLR(4,idx) = 2.*symb(idx) - 2.;
        LLR(5,idx) =   -symb(idx) + 4.;
        LLR(6,idx) =    symb(idx) - 2.;
        
        idx = find((symb>  4) & (symb<=6));
        LLR(4,idx) = 3.*symb(idx) - 6.;
        LLR(5,idx) =   -symb(idx) + 4.;
        LLR(6,idx) =   -symb(idx) + 6.;
        
        idx = find(symb>6);
        LLR(4,idx) =  4.*symb(idx) - 12.;
        LLR(5,idx) = -2.*symb(idx) + 10.;
        LLR(6,idx) =    -symb(idx) + 6. ;
        
        LLR(1,:) = LLR(1,:)*(2./(42.*var));
        LLR(2,:) = LLR(2,:)*(2./(42.*var));       
        LLR(3,:) = LLR(3,:)*(2./(42.*var));       
        LLR(4,:) = LLR(4,:)*(2./(42.*var));        
        LLR(5,:) = LLR(5,:)*(2./(42.*var));       
        LLR(6,:) = LLR(6,:)*(2./(42.*var));                
    otherwise
        error('unknown modulation format');
end

end