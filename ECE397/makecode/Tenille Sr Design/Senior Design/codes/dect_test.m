[norm,fsn]=wavread('G:\Final Design\AG.wav');
norm=1000*abs(norm.^2);
n=1;
    for m=1:500:(2*fsn-500)
        stats(n,1)=max(mean(norm(m:m+500)));
        stats(n,2)=max(median(norm(m:m+500)));
        stats(n,3)=max(std(norm(m:m+500)));
    n=n+1;
    end
   % cov(wavread('G:\Final Design\normal heart sound.wav'),wavread('G:\Final Design\openingsnap.wav'))
stats
% for i=2:4
% figure(i)
% plot(stats(:,i))
% end
% plot(norm(1:2*fsn))
% save('G:\Final Design\stats.xls','stats','-tabs','-ASCII')
figure(10)
plot(wavread('G:\Final Design\S3G'))