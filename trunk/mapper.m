function map_data = mapper(modul_type, in_data)
%-------------------------------------------------------------------------- 
% DESCRIPTION:
%
%   map_data = mapper(modul_type, in_data)
%
% Map binary data to complex symbols
%
% INPUTS:
% modul_type - type of modulation (0 - BPSK, 1 - QPSK, 2 - 16QAM, 3 - 64QAM)
% in_data    - input binary data
% 
% OUTPUTS:
% map_data - output complex symbol
%--------------------------------------------------------------------------  
switch (modul_type)
    case 0,
        numBitsPerSymb = 1;
    case 1,
        numBitsPerSymb = 2;
    case 2,
        numBitsPerSymb = 4;
    case 3,
        numBitsPerSymb = 6;
    otherwise
         error('unknown modulation format');
end

in_data = reshape(in_data, numBitsPerSymb, []);

switch (modul_type)
    case 0,
        map_data = 2.*in_data - 1;
    case 1,
        map_data = (1./sqrt(2)).*((2.*in_data(1,:) - 1.) + 1j*(2.*in_data(2,:) - 1.));
    case 2,
        map_data = (1./sqrt(10)).*((-1. + 2.*in_data(1,:))*(3.-2.*in_data(2,:)) +  1j*(-1. + 2.*in_data(3,:))*(3.-2.*in_data(4,:)));
    case 3,
        map_data = (1./sqrt(42)).*((-1. + 2.*in_data(1,:))*(7. - 6.*in_data(2,:) - 2.*((-1)^in_data(2,:))*in_data(3,:))...
                    + 1j*(-1. + 2.*in_data(4,:))*(7. - 6.*in_data(5,:) - 2.*((-1)^in_data(5,:))*in_data(6,:)) );
end

end