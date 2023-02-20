function drawtria(x,y,theta)
dx=[x+100*cos(theta) x+30*cos(theta+2*pi/3) x+30*cos(theta-2*pi/3) x+100*cos(theta)];
dy=[y+100*sin(theta) y+30*sin(theta+2*pi/3) y+30*sin(theta-2*pi/3) y+100*sin(theta)];
plot(dx,dy);