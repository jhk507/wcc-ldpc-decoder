function [outInfoWord, iterCount, validFlags] = ldpcDecoder(inLLR,frameLength,codeRate,maxIterCount,apprType)

%---------------------------------------------------------------------------------------------------- 
% DESCRIPTION:
%
% [outInfoWord, iterCount, validFlags] = ldpcDecoder(inLLR,frameLength,codeRate,maxIterCount,apprType)
%
% decode InfoWord from codeWord with BP algorythm
%
% INPUTS:
% inLLR         - input LLR (codeWord)
% frameLength   - length of transport-block
% codeRate      - ratio of code
% maxIterCount  - maximum count iterations of algorithm
% apprType      - 1 - min-Sum approximation
%                 0 - tanh-approximation
% 
% OUTPUTS:
% outInfoWord   - output decoded bits
% iterCount     - array of iteration's count of BP algorythm
% validFlags    - array of correct coding - 0 - block with error
%                                         - 1 - block error free
%----------------------------------------------------------------------------------------------------   

if nargin < 4
    error('Not enough input arguments'); 
end
if ~isreal(inLLR)
    error('inLRR must be a real array');
end
if ~isreal(frameLength)
    error('Frame Length must be a real');
end
tmp = reshape(inLLR,1,[]);
[outInfoWord, iterCount, validFlags] = ldpcDecoderBP_mex(tmp,frameLength,codeRate,maxIterCount,apprType);
clear tmp;
end