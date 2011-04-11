function DecodeWord = ldpcDecoderBP(codeWord, var)

if nargin < 2
    error('Not enough input arguments'); 
end
if ~isreal(infoWord)
    error('"infoWord" must be a real array');
end
if ~isreal(var)
    error('"var" must be real');
end

DecodeWord = ldpcDecoderBP_mex(codeWord, var);
end