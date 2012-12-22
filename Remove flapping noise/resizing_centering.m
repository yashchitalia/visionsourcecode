
clear all;close all;clc;
fnames = dir('*.jpg');
numfids = length(fnames);
for K = 1:numfids
   II = imread(fnames(K).name);
   I_new=II;
  resized_image=zeros(1000,1000);%1500,1500
for i=1:480
    for j=1:640
        resized_image1(i+260,j+180)=II(i,j);%510,430
    end
end

for i=1:1000%1500
    for j=1:1000%1500
        if (II(i,j)~=0)
            II(i,j)=255;
        end
    end
end
s  = regionprops(II, 'centroid');
centroids = cat(1, s.Centroid);
ar=regionprops(II, 'area');
area=cat(1, ar.Area);
[B,IX] = sort(area,'descend');
ind=IX(1);
cent=round(centroids(ind,1));
width=cent-500;%750(1500/2)
if(width>=0)
part1_image=I_new(:,width+1:1000);%1500
part2_image=zeros(1000,width);%1500
final_image=zeros(1000,1000);%1500,1500
final_image=[part1_image part2_image];
else
    part2_image=I_new(:,1:1000+width);%1500
    part1_image=zeros(1000,-width);%1500
    final_image=zeros(1000,1000);%1500,1500
    final_image=[part1_image part2_image];
end
imwrite(final_image,strcat('\\storage.adsroot.itcs.umich.edu\home\windat.v2\Desktop\442 project code\demo_videos2\893_shifted\',fnames(K).name),'jpg');
end