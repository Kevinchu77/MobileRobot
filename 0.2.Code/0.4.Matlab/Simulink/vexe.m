function vexe(x,y,theta)
theta=theta*pi/180;
dx=[x+257*cos(theta) x+88.5*cos(theta+pi/2) x+88.5*cos(theta-pi/2) x+257*cos(theta)];
dy=[y+257*sin(theta) y+88.5*sin(theta+pi/2) y+88.5*sin(theta-pi/2) y+257*sin(theta)];
plot(dx,dy,'k'); drawnow
end