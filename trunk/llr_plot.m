% Config plot parameters
x = -4:0.01:4;
var =1;
modulType = 2;

%
y = demapper(modulType, x, var);
switch(modulType)
    case 0
        plot(x,y,'r');
        grid on;
        title('BPSK modulation');
    case 1,
        b0 = y(1:2:end);
        plot(x,b0,'r');
        grid on;
        title('QPSK modulation');
    case 2,
        b0 = y(1:4:end);
        b1 = y(2:4:end);
        plot(x,b0,'r');
        hold on
        plot(x,b1,'b--');
        hold off
        grid on
        title('16-QAM modulation');
        xlabel('Cons.val');
        ylabel('LLR');
        legend('b0','b1');
    case 3,
        b0 = y(1:6:end);
        b1 = y(2:6:end);
        b2 = y(3:6:end);
        plot(x,b0,'r');
        hold on
        plot(x,b1,'k--');
        plot(x,b2,'b-');
        hold off
        grid on
        title('64-QAM modulation');
        xlabel('Cons.val');
        ylabel('LLR');
        legend('b0','b1','b2');
     otherwise
        error('unknown modulation format');
end
