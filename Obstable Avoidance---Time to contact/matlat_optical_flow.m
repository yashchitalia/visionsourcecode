close all; clear all; clc

% filename = 'example.avi';     %demonstrate with 2817.avi
% filename = 'sub_images_100.avi';
% filename = 'homography_video_modify2.avi';
% filename = 'duder_modify.avi';
% filename = 'MOV00862.avi'
filename = 'EECS442.avi'
% filename = 'IMG_2884.avi'
% filename = 'test_images_old.avi'
hvfr = vision.VideoFileReader(filename, 'ImageColorSpace', 'RGB',...
                              'VideoOutputDataType', 'single');

% hof = vision.OpticalFlow('Method','Horn-Schunck','ReferenceFrameDelay',3,'OutputValue','Horizontal and vertical components in complex form');
hof = vision.OpticalFlow( 'Method','Horn-Schunck',...
    'OutputValue', 'Horizontal and vertical components in complex form', ...
    'ReferenceFrameDelay', 3);
hsi = vision.ShapeInserter('Shape','Lines','BorderColor','Custom', 'CustomBorderColor', 255);
hvp = vision.VideoPlayer('Name', 'Motion Vector');

hshapeins2 = vision.ShapeInserter( 'Shape','Lines', ...
                                   'BorderColor', 'Custom', ...
                                   'CustomBorderColor', [255 255 0]);
hshapeins3=vision.ShapeInserter('CustomBorderColor', [15 150 0]);

                         
                                                
sz = get(0,'ScreenSize');
pos = [20 sz(4)-500 400 400];
hVideo2 = vision.VideoPlayer('Name','Motion Vector','Position',pos);
hVideo3 = vision.VideoPlayer('Name','FOE','Position',pos);   


counter=1;
FOE = [];
tau = [];


frame_size = step(hvfr);
left_column = [];
for i = 1:size(frame_size,2)
    left_column = [left_column;i*ones(size(frame_size,1),1)];
end
right_column = [];
for i = 1:size(frame_size,2)
    right_column = [right_column;linspace(1,size(frame_size,1),size(frame_size,1))'];
end

time_matrix = [left_column -right_column];
position_matrix = [left_column right_column];

velocity_v_p1_r = [];
velocity_v_p1_i = [];
velocity_v_p1_r1 = [];
velocity_v_p1_i1 = [];
FOE_distance_all = [];
sum_speed_norm_all = [];

while ~isDone(hvfr)
    frame = step(hvfr);
    grayFrame = rgb2gray(frame);
    frames_saved(:,:,counter)=grayFrame;
    ofVectors = step(hof,grayFrame);
    velocities(:,:,counter)=ofVectors;


    [R C] = size(ofVectors);            % Height and width in pixels
    RV = 5:5:(R-5);
    CV = 5:5:(C-5);
    [Y X] = meshgrid(CV,RV);

    tmp = ofVectors(RV,CV) .* 20;
    lines = [Y(:), X(:), Y(:) + real(tmp(:)), X(:) + imag(tmp(:))];
    motionVectors = step(hshapeins2, frame, lines);
    
    step(hVideo2, motionVectors);    % Video with motion vectors
    
    % calulating FOE
    size_frame = size(ofVectors);
    ofVectors2 = reshape(ofVectors,size_frame(1)*size_frame(2),1);
    A = [imag(ofVectors2),real(ofVectors2)]; % [v u]
    b_seperate = A.*time_matrix; % [v*x -u*y]
    b = b_seperate(:,1)+ b_seperate(:,2); % v*x-u*y
    
    velocity_v_p1_r = [velocity_v_p1_r median(real(ofVectors))];
    velocity_v_p1_i = [velocity_v_p1_i median(imag(ofVectors))];
    U(:,:,counter)=reshape(A(:,2),size_frame(1),size_frame(2));
    V(:,:,counter)=reshape(A(:,1),size_frame(1),size_frame(2));
    
     
    SU=sum(U(:,:,counter));
    SSU=sum(SU');
    SV=sum(V(:,:,counter));
    SSV=sum(SV');
    
    SSU1=sumsqr(U(:,:,counter));
    SSV1=sumsqr(V(:,:,counter));
    
    U_norm(counter)=SSU/sqrt(SSU1);
    V_norm(counter)=SSV/sqrt(SSV1);
    angle_theta(counter)=atan(V_norm(counter)/U_norm(counter));
    
    FOE_current = [1 0;0 -1] * inv(A'*A)*A'*b;
    FOE = [FOE FOE_current];
    
    
    FoE_points=step(hshapeins3,frame,[FOE_current(1,1) FOE_current(2,1) 8 8]);
    step(hVideo3,FoE_points);
     
    distance = position_matrix - ones(size_frame(1)*size_frame(2),1)*FOE_current';
    distance_norm = (distance(:,1).^2 + distance(:,2).^2).^0.5;
    
    
    speed_norm = (A(:,1).^2 + A(:,2).^2).^0.5;
    
    FOE_distance = norm(FOE_current - [size(frame_size,1)/2 ; size(frame_size,2)/2]);
    FOE_distance_all = [FOE_distance_all, FOE_distance];
    
    tau_one = FOE_distance/ sum(speed_norm);
    sum_speed_norm_all = [sum_speed_norm_all,sum(speed_norm)];
    
    tau_all = distance_norm ./ speed_norm;
    
    tau = [tau; median(tau_all)];
%     tau = [tau; tau_one];
    
    counter=counter+1;      
    
end

release(hvp);
release(hvfr); 
figure,plot(V_norm);
title('Integrated Optical Flow along y axis');
xlabel('Frame No');
ylabel('V(t)');

%filtering with Hanning window
filt=hann(20);
result=conv(V_norm,filt);
figure,plot(result);
[PeakLoc PeakMag]=peakfinder(V_norm,[],100,1);

%calculating the fft and plotting the frequency spectrum
L=length(V_norm);Fs=100;
NFFT = 2^nextpow2(L); % Next power of 2 from length of y
Y = fft(V_norm,NFFT)/L;
f = Fs/2*linspace(0,1,NFFT/2+1);
figure,plot(f,2*abs(Y(1:NFFT/2+1))) 
signal_mag=2*abs(Y(1:NFFT/2+1));
title('Single-Sided Amplitude Spectrum of V(t)')
xlabel('Frequency (Hz)')
ylabel('|V(f)|')
