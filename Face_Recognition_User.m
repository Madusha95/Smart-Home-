%web cam 
camList = webcamlist; 
cam=webcam; 
for i=1:6 
img =snapshot(cam); 
subplot(2,3,i) 
image(img);
 pause(2); %Delay between different screenshots 
    img_wg= getFace(img,1); 
    
    %Saving Reshaped Compressed Image of User 
    if i==1 
        TMP1=img_wg; 
    elseif i==2 
        TMP2=img_wg; 
    elseif i==3 
        TMP3=img_wg; 
    elseif i==4 
        TMP4=img_wg; 
    elseif i==5 
        TMP5=img_wg;     
    end 
end 
user_images=[TMP1 TMP2 TMP3 TMP4 TMP5]; %Collect all in one 
matrix 
save user.mat user_images 
load ('user.mat') 
delete(cam);