function [xn,yn,thetan]=xechay(x,y,theta,v,w)
T=0.1;
theta=theta*pi/180;
syms t
xn=double(int(v*cos(w*t+theta),t,0,T))+x;
yn=double(int(v*sin(w*t+theta),t,0,T))+y;
thetan=theta+w*T;
thetan=thetan*180/pi;
if(thetan>360)
thetan=thetan-360;
end
end