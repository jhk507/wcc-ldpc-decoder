function outSymb = chanelAWGN( inSymb, locSNRdB )

nCompl = (1/sqrt(2*10^(locSNRdB/10)))*(randn(size(inSymb)) + 1j*randn(size(inSymb)));
outSymb = inSymb + nCompl;
end

