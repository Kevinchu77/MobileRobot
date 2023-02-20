function e2=docsaisoe2(x,y,theta)
Dc=200;
out=-1;
ssx=x+Dc*cosd(theta); ssy=y+Dc*sind(theta);  sstheta=theta+90;  % Toa do cua day cam bien
 r=-ssx*sind(sstheta)+ssy*cosd(sstheta); %tim phuong trinh duong sensor
 check=1;
 e2=-1;
 syms xx yy
 ptss=-xx*sind(sstheta)+yy*cosd(sstheta)-r; %phuong trinh sensor
 % Giao diem voi duong line duoi
 pt1=0*xx+yy+500;                       %phuong trinh duong line duoi
 [xR,yR]=solve(ptss,pt1,[xx yy]);
 if(isempty(xR)==0&&isempty(yR)==0)
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
     pt2=0*xx+yy-500;                        %phuong trinh duong line tren
     [xR,yR]=solve(ptss,pt2,[xx yy]);
 if(isempty(xR)==0&&isempty(yR)==0)
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
 pt3=(xx-1000)^2+yy^2-250000;                       %phuong trinh duong line phai
 [xR,yR]=solve(ptss,pt3,[xx yy]);
 if(isempty(xR(1))==0&&isempty(yR(1))==0)
     xR=double(xR);
     yR=double(yR);
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
 end
 if(isempty(xR(2))==0&&isempty(yR(2))==0)
     xR=double(xR);
     yR=double(yR);
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
 end
  pt4=(xx+1000)^2+yy^2-250000;                        %phuong trinh duong line trai
 [xR,yR]=solve(ptss,pt4,[xx yy]);
 if(isempty(xR(1))==0&&isempty(yR(1))==0)
     xR=double(xR);
     yR=double(yR);
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
   if(isempty(xR(2))==0&&isempty(yR(2))==0) 
     xR=double(xR);
     yR=double(yR);
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
   end
   e2=e2*(-1)^(out+1);
   e2=double(e2);
end