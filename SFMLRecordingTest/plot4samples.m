%Plot 4 samples

figure

subplot(2,2,1)
time0 = Sample0{:,1};
soundSample0 = Sample0{:,2};
plot(time0,soundSample0);
grid on;
title(' DTMF 0')

subplot(2,2,2)
time1 = Sample1{:,1};
soundSample1 = Sample1{:,2};
plot(time1,soundSample1);
grid on;
title('DTMF 1')

subplot(2,2,3);
time2 = Sample2{:,1};
soundSample2 = Sample2{:,2};
plot(time2,soundSample2);
grid on;
title('DTMF 2')

subplot(2,2,4)
time3 = Sample3{:,1};
soundSample3 = Sample3{:,2};
plot(time3,soundSample3);
grid on;
title('DTMF 3')