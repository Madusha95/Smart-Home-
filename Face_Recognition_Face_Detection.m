function faceimage= getFace(img,contrast) 
faceimage=rgb2gray(img); % make it gray scale 
%Detect the face 
faceDetector = vision.CascadeObjectDetector; 
for i=1:2:50 
    set(faceDetector,'MergeThreshold',i) 
    bboxes=step(faceDetector,faceimage); 
    if size(bboxes,1)==1 
        break; 
    end 
end 
  
faceimage=imcrop(faceimage,bboxes); 
figure(2) 
imshow(faceimage) 
if contrast  
    faceimage = imadjust(faceimage); 
end 
  
%Prepare img for password check 
  
faceimage=imresize(faceimage,[16,16],'nearest'); %Resizing the 
Image to be 16x16 pixels. 
faceimage=im2double(faceimage); %Converting Image Data to 
Double(Required to DCT function). 
Time = dctmtx(8);
dct = @(block_struct) Time * block_struct.data * Time'; 
Box = blockproc(faceimage,[8 8],dct); 
mask = [1,1,1,1,0,0,0,0; 
        1,1,1,0,0,0,0,0; 
        1,1,0,0,0,0,0,0; 
        1,0,0,0,0,0,0,0; 
        0,0,0,0,0,0,0,0; 
        0,0,0,0,0,0,0,0; 
        0,0,0,0,0,0,0,0; 
        0,0,0,0,0,0,0,0]; 
Box = blockproc(Box,[8 8],@(block_struct) mask .* 
block_struct.data); 
inversedct = @(block_struct) Time' * block_struct.data * Time; 
faceimage = blockproc(Box,[8 8],inversedct); 
faceimage=reshape(faceimage,256,1);