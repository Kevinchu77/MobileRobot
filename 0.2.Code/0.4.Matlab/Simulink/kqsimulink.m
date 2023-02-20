function kqsimulink(xo,yo,thetao,e2,wr,wl,w,s,cros)
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
text(1400,0,'O','FontSize',12);
text(1000,600,'A','FontSize',12);
text(-1000,600,'B','FontSize',12);
text(-1400,0,'C','FontSize',12);
text(-1000,-600,'D','FontSize',12);
text(1000,-600,'E','FontSize',12);
time=0:0.1:(length(xo)*0.1-0.1);
time=time';
axis([-1600 1600 -1200 1200]);
k=1;
r=40;
str='OABCDE';
    for i=1:1:length(xo)
        vexe(xo(i),yo(i),thetao(i));
        [ssx(i),ssy(i),sstheta(i)]=vitricambien(xo(i),yo(i),thetao(i));
        [btx(i),bty(i),bpx(i),bpy(i)]=vitribanh(xo(i),yo(i),thetao(i));
        if(cros(i)==1)
           fprintf('Quang duong %c%c la: %f\n',str(1),str(k+1),s(i-1));
           sovong=s(i-1)/(2*pi*r);
           fprintf('So vong banh xe tren doan duong %c%c la: %f\n',str(1),str(k+1),sovong);
           soxung=round(sovong*44*21.3);
           fprintf('So xung tren doan duong %c%c la: %f\n',str(1),str(k+1),soxung);
           fprintf('Thoi gian di het doan duong %c%c la %f\n',str(1),str(k+1),time(i-1));
           k=k+1;
        end
    end
    p7=plot(ssx,ssy,'bl');
    set(p7,'LineWidth',2);
    %p8=plot(xo,yo,'gr');
    %set(p8,'LineWidth',2);
    %p9=plot(btx,bty,'gr');
    %set(p9,'LineWidth',1.5);
    %p10=plot(bpx,bpy,'bl');
    %set(p10,'LineWidth',1.5);
    figure
    plot(time,w);
    xlabel('Thoi gian (s)');
    ylabel('Van toc goc xe (rad/s)'); 
    title('Van toc goc xe theo thoi gian');
    figure
    plot(time,e2);
    xlabel('Thoi gian (s)');
    ylabel('Sai so e (mm)'); 
    title('Sai so e theo thoi gian');
    figure
    plot(time,wr,'r');
    hold on
    plot(time,wl,'g');
    xlabel('Thoi gian (s)');
    ylabel('Van toc goc (rad/s)'); 
    title('Van toc goc tung banh xe');
    legend('wr','wl');
end