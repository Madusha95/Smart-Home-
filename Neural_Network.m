function nn 
%web cam 
camList = webcamlist; 
cam=webcam; 
preview(cam); 
%take a picture 
frame =snapshot(cam); 
figure(1); 
image(frame) 
FACE=getFace(frame,1); 
load user 
net = selforgmap([16 16]); 
net.trainParam.epochs=1000; 
[net,~] = train(net,user_images); 
sx=net(user_images); 
[~,m]=size(sx); 
for u=1:1:m 
    sm(u)=find(sx(:,u)); 
end 
initial_result=sim(net,FACE); 
final_result=find(initial_result); 
  
temp=find((sm - final_result)==min(abs((sm-final_result)))) 
if isempty(temp) 
    say('Sorry, I do not know you'); 
    channelID = 811395;
    thingSpeakWrite(channelID,'Fields',[5],'Values',{50},'WriteKey','AE9YB
 CK1NHDTQJS0','Timeout',5) 
  
elseif (temp > 0) && (temp <= 5) 
    say('Welcome MADUSHA How are you today?'); 
    channelID = 811395; 
    
thingSpeakWrite(channelID,'Fields',[5],'Values',{100},'WriteKey','AE9Y
 BCK1NHDTQJS0','Timeout',5) 
end    