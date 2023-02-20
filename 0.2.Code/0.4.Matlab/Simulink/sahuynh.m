function sahuynh
clear all
close all
clc
hold on
axis equal
grid on
title('Sa ban Robot do line')
xlabel('x (mm)')
ylabel('y (mm)')
PHI_AB=linspace(0,90,1000);
X1=1000+500*cosd(PHI_AB);
Y1=500*sind(PHI_AB);
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