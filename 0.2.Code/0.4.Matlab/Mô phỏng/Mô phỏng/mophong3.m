clear all
close all
clc
subplot(2,2,1);
hold on
axis equal
grid on
title('Sa ban Robot do line')
xlabel('x (mm)')
ylabel('y (mm)')
PHI_AB=linspace(0,90,1000);
X1=1000+500*cosd(PHI_AB);
Y1=0+500*sind(PHI_AB);
p1 = plot(X1,Y1,'r');
set(p1,'LineWidth',2)
X2=linspace(-1000,1000,2);
Y2=500+0*X2;
p2 = plot(X2,Y2,'r');
set(p2,'LineWidth',2)
PHI_CD=linspace(0,90,1000);
X3=-1000-500*cosd(PHI_CD);
Y3=500*sind(PHI_CD);
p3 = plot(X3,Y3,'r');
set(p3,'LineWidth',2)
PHI_DE=linspace(0,90,1000);
X4=-1000-500*cosd(PHI_DE);
Y4=-500*sind(PHI_DE);
p4 = plot(X4,Y4,'r');
set(p4,'LineWidth',2);
X5=linspace(-1000,1000,2);
Y5=-500+0*X2;
p5 = plot(X5,Y5,'r');
set(p5,'LineWidth',2);
PHI_FA=linspace(0,90,1000);
X6=1000+500*cosd(PHI_FA);
Y6=-500*sind(PHI_FA);
p6 = plot(X6,Y6,'r');
set(p6,'LineWidth',2);
axis([-1600 1600 -1200 1200]);
clear all
x(1)=1500;y(1)=0;theta(1)=100; %Toa do ban dau cua xe
Dc=257; % Khoang cach tu tam xe den tam cam bien
T=0.1;
r=40; %duong kinh banh xe
b=88.5; %khoang cach tu tam xe den banh xe
L=177;
subplot(2,2,2);
hold on
grid on
axis([0 10 -20 50]);
xlabel('Thoi gian (s)');
ylabel('Sai so e2 (mm)'); 
title('Sai so e2 theo thoi gian');
subplot(2,2,3);
hold on
grid on
axis([0 10 -2 4]);
xlabel('Thoi gian (s)');
ylabel('Van toc goc (rad/s)'); 
title('Van toc goc xe theo thoi gian');
subplot(2,2,4);
hold on
grid on
axis([0 10 0 30]);
xlabel('Thoi gian (s)');
ylabel('Van toc goc (rad/s)'); 
title('Van toc goc tung banh xe');
for i=1:1:85
    subplot(2,2,1);
    vexe(x(i),y(i),theta(i));
    time(i)=(i-1)*T;
    [e2(i)]=docsaisoe2moi(x(i),y(i),theta(i));
    [v(i),w(i)]=bodieukhien(e2(i));
    wl(i)=(v(i)-w(i)*L/2)/r;
    wr(i)=(v(i)+w(i)*L/2)/r;
    [x(i+1),y(i+1),theta(i+1)]=xechay(x(i),y(i),theta(i),v(i),w(i));
    if (i>1)
    subplot(2,2,2);
    plot([time(i-1) time(i)],[e2(i-1) e2(i)],'b'); drawnow
    subplot(2,2,3);
    plot([time(i-1) time(i)],[w(i-1) w(i)],'k'); drawnow
    subplot(2,2,4);
    plot([time(i-1) time(i)],[wr(i-1) wr(i)],'r'); drawnow
    plot([time(i-1) time(i)],[wl(i-1) wl(i)],'g'); drawnow
    legend('wr','wl');
    end
end


