function outLLR = ldpcDecoder(inLLR,frameLength,var,minSumAppr)

if nargin < 4
    error('Not enough input arguments'); 
end
if ~isreal(inLLR)
    error('inLRR must be a real array');
end
if ~isreal(frameLength)
    error('Frame Length must be a real');
end
if ~isreal(var)
    error('Variance must be a real');
end

tmpLLR = reshape(inLLR,1,[]);

outLLR = ldpcDecoderBP_mex(tmpLLR,frameLength,var,minSumAppr);
clear tmpLLR;
end