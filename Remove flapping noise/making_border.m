
I=imread('P:\demo_videos\MOV00876 (12-5-2012 1-00-50 AM)\MOV00876 001.jpg');

resized_image=zeros(1000,1000);
for i=1:480 % amrita's camrea size
    for j=1:640
        resized_image(i+260,j+180)=I(i,j); %510,430
    end
end
 resized_image=uint8(resized_image);  
 imwrite(resized_image,'P:\demo_videos\MOV00876 (12-5-2012 1-00-50 AM)\resized.jpg','jpg');
 
 
