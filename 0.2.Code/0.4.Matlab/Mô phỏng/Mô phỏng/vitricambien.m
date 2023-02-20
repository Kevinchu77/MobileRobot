function [ssx,ssy,sstheta]= vitricambien(x,y,theta)
Dc=257;
ssx=x+Dc*cosd(theta);
ssy=y+Dc*sind(theta);  
sstheta=theta+90;