function [outLLR, iterCount] = ldpcDecoder(inLLR,frameLength,minSumAppr)

if nargin < 3
    error('Not enough input arguments'); 
end
if ~isreal(inLLR)
    error('inLRR must be a real array');
end
if ~isreal(frameLength)
    error('Frame Length must be a real');
end

tmpLLR = reshape(inLLR,1,[]);

[outLLR, iterCount] = ldpcDecoderBP_mex(tmpLLR,frameLength,minSumAppr);
clear tmpLLR;
end