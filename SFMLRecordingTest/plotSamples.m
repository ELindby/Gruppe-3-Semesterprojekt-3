time = SampleDTMF1{:,1};
soundSample = SampleDTMF1{:,2};

figure
p=plot(time,soundSample,'.');
grid on;
hold on;
title('Function');
ylabel('Sample');
xlabel('Time');