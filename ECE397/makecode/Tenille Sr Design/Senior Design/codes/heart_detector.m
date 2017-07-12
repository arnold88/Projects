% This code will locate the murmurs of 9 heart signals
% four systolic, four diastolic, and one normal
% Tenille Medley, Senior Design 2006 - 2007
clear all;
[norm,fsn]=wavread('G:\Final Design\normal heart sound.wav');
[sys_1,fs_s1]=wavread('G:\Final Design\pansystolic.wav');
[sys_2,fs_s2]=wavread('G:\Final Design\late systolic.wav');
[sys_3,fs_s3]=wavread('G:\Final Design\early systolic.wav');
[sys_4,fs_s4]=wavread('G:\Final Design\ejectionclick.wav');
[dia_1,fs_d1]=wavread('G:\Final Design\AG.wav');
[dia_2,fs_d2]=wavread('G:\Final Design\s4.wav');
[dia_3,fs_d3]=wavread('G:\Final Design\dia atrial gallop.wav');
[dia_4,fs_d4]=wavread('G:\Final Design\openingsnap.wav');

%-------------
sz=[length(norm) length(sys_1) length(sys_2) length(sys_3) length(sys_4)...
        length(dia_1) length(dia_2) length(dia_3) length(dia_4)];
sz_max=max(sz);
%-------------

%-------------
%% pad matrices with zeros to combine
norm((size(norm)+1):sz_max,1)=0;
sys_1((size(sys_1)+1):sz_max,1)=0;
sys_2((size(sys_2)+1):sz_max,1)=0;
sys_3((size(sys_3)+1):sz_max,1)=0;
sys_4((size(sys_4)+1):sz_max,1)=0;
dia_1((size(dia_1)+1):sz_max,1)=0;
dia_2((size(dia_2)+1):sz_max,1)=0;
dia_3((size(dia_3)+1):sz_max,1)=0;
dia_4((size(dia_4)+1):sz_max,1)=0;
%-------------

h1=[norm sys_1 sys_2 sys_3 sys_4 dia_1 dia_2 dia_3 dia_4]; %% combine all nine signls to one array
f1=[fsn fs_s1 fs_s2 fs_s3 fs_s4 fs_d1 fs_d2 fs_d3 fs_d4]; %% combine all sampling frequencies to one array


for i=1:8
    %%---------------------------------
    %% Plot first two seconds of the nine signals
    dt1(1,i)=1/f1(1,i);%% time interval
    signal(1:2*f1(1,i),i)=h1(1:2*f1(1,i),i); %% each column represents a different signal
    t1(1:2*f1(1,i))=(1:2*f1(1,i)).*dt1(1,i); %%time vector
    figure(i)
    AmpSig(1:2*f1(1,i),i)=1000*abs(signal(1:2*f1(1,i),i).^2);
    subplot(1,2,1),plot(AmpSig(1:2*f1(1,i),i))
    %%---------------------------------
    
    %%---------------------------------
    %% Find the four parameters of each of the nine signals
    %% 1. Heart Rate
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    [SigMax(i,1),SigInd(i,1)]=max(AmpSig(1:2*f1(1,i),i));
    thresh_1(i,1)=round(0.85*SigMax(i,1));
    q=0;
    while (AmpSig(q+1,i)<=thresh_1(i,1))& (q < 2*f1(1,i))%% Search for first peak
        q=q+1;
    end
    Peak1Loc(i,1)=q; %% Store peak location
    PeakMask(i,1)=Peak1Loc(i,1)+ 4000;%% create a mask of 4000 pts away from first peak
    r=PeakMask(i,1);
    while (AmpSig(r,i)<=thresh_1(i,1))&(q < 2*f1(1,i)) %% Search for second peak
        r=r+1;
    end
    Peak2Loc(i,1)=r; %% Store second peak location
    p2p(i,1)=Peak2Loc(i,1)-Peak1Loc(i,1);%% number of samples between 1 beat
    %% Heart rate Calculations
    samp_sec(i,1)=f1(1,i); %% calculate samples per second
    beat_samp(i,1)=1/p2p(i,1); %% calculate beats per sample
    RateSec(i,1)=samp_sec(i,1).*beat_samp(i,1); %% calculate heart rate per sec
    RateMin(i,1)=RateSec(i,1)*60; %% beats per min
    %% Heart rate segment done
    %%--------------------------------
    
    %%--------------------------------
    %% 2. Murmur Type (Systolic or Diastolic)
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% Calculate mean, median, standard deviation for each signal
    %% For the three dimensional array, n represents number of values for
    %% each stat, i represents each signal (1-9). I will use these values
    %% to decide location of murmur
    n=1;
    for m=1:500:(2*f1(1,i)-500)
        %% window size = 500. calulates the mean med and std for all nine
        %% signals over each window size and stores value in columns 1-3 of
        %% stats array
        stats(n,1,i)=max(mean(AmpSig(m:m+500,i)));
        stats(n,2,i)=max(median(AmpSig(m:m+500,i)));
        stats(n,3,i)=max(std(AmpSig(m:m+500,i)));
        %% StorStat(1-3) array stores mean, med, std, respectively for all nine signals
        %% i.e. StorStat1 is 44x9 array of all the mean values from
        %% stats(n,1,i)
        StorStat1(n,i)=stats(n,1,i);
        StorStat2(n,i)=stats(n,2,i);
        StorStat3(n,i)=stats(n,3,i);
        %figure(i)
        subplot(1,2,2),plot(StorStat1(:,i))
        n=n+1;
    end
    %% Now find S1 and S2 values, then store the arrays
    if i==7
        LowThresh=44;
    else
        LowThresh=25;
    end
    p=1;t=1;
    while t<44
        while StorStat1(t,i)>=LowThresh
            t=t+1;
        end
        SArray(i,p)=t;
        g=t;
        while g<44 & StorStat1(g,i)< LowThresh
            g=g+1;
        end
        SArray(i,p+1)=g;
        t=g;
        p=2*p+1;
    end
    SArray(i,:)=abs(sort(-SArray(i,:)));
    Sray(i,1:12)=sort(SArray(i,1:12));
    if i==7
        Sray(i,2)=4;
    end
    c=1;
    while Sray(i,c)<=1
        c=c+1;
    end
    [M(i,1),I(i,1)]=max(StorStat1(1:Sray(i,c),i));
%     b=1;
%     while b < length(Sray(i,:))
%         [M(i,b+1),I(i,b+1)]=max(StorStat1(Sray(i,2*b):Sray(i,2*b+1),i))
%         b=b+1;
%     end
end
%save('G:\Final Design\status.xls', 'StorStat1', 'StorStat2', 'StorStat3', '-tabs','-ASCII');



