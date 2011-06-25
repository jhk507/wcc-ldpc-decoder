function [ estimatedBits,iterCount, validFlags ] = ldpcDecodeRight( llr, maxIterCount, approxType, algType)
%LDPCDECODE Summary of this function goes here
%   Detailed explanation goes here

% llr             - input llr(672)
% maxIterCount    - maximum iteration count
% approxType -   0 - atanh
%                1 - min-Sum
% algType    -   0 - BP
%                1 - LBP

% --- Outputs
% estimatedBits - output information bits ()
% iterCount - array of count completed iterations (length = codew word count)
% validFlags - array of correct coding - 0 - block with error
%                                      - 1 - block error free

[estimatedBits,iterCount, validFlags] = ldpc_decoder(llr, maxIterCount, approxType, algType);
end

