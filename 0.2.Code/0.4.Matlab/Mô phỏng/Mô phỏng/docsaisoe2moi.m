function e2=docsaisoe2moi(x,y,theta)
Dc=257;
out=-1;
ssx=x+Dc*cosd(theta);
ssy=y+Dc*sind(theta);  
sstheta=theta+90;  % Toa do cua day cam bien
 r=-ssx*sind(sstheta)+ssy*cosd(sstheta); %tim phuong trinh duong sensor
 check=1;
 e2=-1;                      
 A=[-sind(sstheta) cosd(sstheta); 0 1];   %phuong trinh duong line duoi
 B= [r ; -500];
 temp=A\B;
 xR=temp(1);
 yR=temp(2);
 if(isinf(xR)==0&&isinf(yR)==0&&isnan(xR)==0&&isnan(yR)==0)
     if((xR>-1000)&&(xR<1000))
         e2fake=sqrt((xR-ssx)^2+(yR-ssy)^2);
         if (check==1||e2fake<e2)
             if(ssy<yR)
             out=1;
             else
              out=0;
             end
            e2=e2fake;
            check=0;
         end
     end
 end
 A=[-sind(sstheta) cosd(sstheta); 0 1];   %phuong trinh duong line tren
 B= [r ; 500];
 temp=A\B;
 xR=temp(1);
 yR=temp(2);
 if(isinf(xR)==0&&isinf(yR)==0&&isnan(xR)==0&&isnan(yR)==0)
      if(xR>-1000&&xR<1000)
         e2fake=sqrt((xR-ssx)^2+(yR-ssy)^2);
          if (check==1||e2fake<e2)
              if(ssy>yR)
             out=1;
             else
              out=0;
             end
              e2=e2fake;
              check=0;
          end
      end
 end              
if(abs(cosd(sstheta))<0.001)                        %phuong trinh duong line phai
   xR(1)=r/(-sind(sstheta)); 
   xR(2)=r/(-sind(sstheta)); 
   if(250000-(xR(1)-1000)^2>=0)
     yR(1)=sqrt(250000-(xR(1)-1000)^2);
     yR(2)=-sqrt(250000-(xR(1)-1000)^2);
   else
     yR(1)=1+2j;
     yR(2)=1+2j;
   end
else
    p=[1+tand(sstheta)^2 2*r*tand(sstheta)/cosd(sstheta)-2000 750000+(r/cosd(sstheta))^2];
    temp=roots(p);
    xR(1)=temp(1);
    xR(2)=temp(2);
    yR(1)=(r+sind(sstheta)*xR(1))/cosd(sstheta);
    yR(2)=(r+sind(sstheta)*xR(2))/cosd(sstheta);
end
     if(xR(1)>=1000&&imag(xR(1))==0&&imag(yR(1))==0)
        e2fake=sqrt((xR(1)-ssx)^2+(yR(1)-ssy)^2);
         if (check==1||e2fake<e2)
            if((ssx-1000)^2+ssy^2>250000)
            out=1;
            else
            out=0;
            end
            e2=e2fake;
            check=0;
         end
     end
     if(xR(2)>=1000&&imag(xR(2))==0&&imag(yR(2))==0)
        e2fake=sqrt((xR(2)-ssx)^2+(yR(2)-ssy)^2);
         if (check==1||e2fake<e2)
            if((ssx-1000)^2+ssy^2>250000)
            out=1;
            else
            out=0;
            end
            e2=e2fake;
            check=0;
         end
     end
 if(abs(cosd(sstheta))<0.001)                        %phuong trinh duong line trai
   xR(1)=r/(-sind(sstheta)); 
   xR(2)=r/(-sind(sstheta)); 
   if(250000-(xR(1)+1000)^2>=0)
     yR(1)=sqrt(250000-(xR(1)+1000)^2);
     yR(2)=-sqrt(250000-(xR(1)+1000)^2);
   else
     yR(1)=1+2j;
     yR(2)=1+2j;
   end
else
    p=[1+tand(sstheta)^2 2*r*tand(sstheta)/cosd(sstheta)+2000 750000+(r/cosd(sstheta))^2];
    temp=roots(p);
    xR(1)=temp(1);
    xR(2)=temp(2);
    yR(1)=(r+sind(sstheta)*xR(1))/cosd(sstheta);
    yR(2)=(r+sind(sstheta)*xR(2))/cosd(sstheta);
end
     if(xR(1)<= -1000&&imag(xR(1))==0&&imag(yR(1))==0)
        e2fake=sqrt((xR(1)-ssx)^2+(yR(1)-ssy)^2);
         if (check==1||e2fake<e2)
             if((ssx+1000)^2+ssy^2>250000)
            out=1;
            else
            out=0;
            end
            e2=e2fake;
            check=0;
         end
     end
     if(xR(2)<= -1000&&imag(xR(2))==0&&imag(yR(2))==0)
        e2fake=sqrt((xR(2)-ssx)^2+(yR(2)-ssy)^2);
         if (check==1||e2fake<e2)
             if((ssx+1000)^2+ssy^2>250000)
            out=1;
            else
            out=0;
            end
            e2=e2fake;
         end
     end
   e2=e2*(-1)^(out+1);
   e2=double(e2);
end