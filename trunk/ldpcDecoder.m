function outLLR = ldpcDecoder(inLLR,var)

if nargin < 2
    error('Not enough input arguments'); 
end
if ~isreal(inLLR)
    error('infoWord must be a real array');
end

tmpLLR = reshape(inLLR,1,[]);

outLLR = ldpcDecoderBP_mex(tmpLLR,var);
clear tmpLLR;
end