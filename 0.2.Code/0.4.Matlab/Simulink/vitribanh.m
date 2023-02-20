function [btx,bty,bpx,bpy]=vitribanh(x,y,theta)
theta=theta*pi/180;
btx=x+88.5*cos(theta+pi/2);
bty=y+88.5*sin(theta+pi/2);
bpx=x+88.5*cos(theta-pi/2);
bpy=y+88.5*sin(theta-pi/2);
end