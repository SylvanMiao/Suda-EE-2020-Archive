hy=261;hx=191;phim=160;h0=9.5-2.5/(2*sin(pi/3));x1=10.5;x2=15.5;
times=30;m=0;
H=[];
V=[];
while(m<(times))
alpha=1+rand;
v1=ones(hy,hx);

v1(hy,:)=zeros(1,hx);
v1(1,:)=zeros(1,hx);

for i=1:hy
    v1(i,1)=0;
    v1(i,hx)=0;
end
for i=1:hy
    v1(i,hx)=phim*sin(pi*(i-1)*0.1/26);
end

v2=v1;maxt=1;t=0;
k=0;
while(maxt>1e-5)
    k=k+1;
    maxt=0;
    for i=2:hy-1
        for j=2:hx-1
            if ((j-1)*0.1)==round(h0)&&(i-1)*0.1<=x2&&(i-1)*0.1>=x1...
                    ||round((j-1)-10*(((i-1)*0.1-x1)*tan(pi/3)+h0))==0&&(i-1)*0.1<=x2&&(i-1)*0.1>=x1&&(j-1)*0.1<=h0+5*sin(pi/3)...
                    ||round((j-1)-10*((x2-(i-1)*0.1)*tan(pi/3)+h0))==0&&(i-1)*0.1<=x2&&(i-1)*0.1>=x1&&(j-1)*0.1<=h0+5*sin(pi/3)
                v2(i,j)=phim;
            else
                v2(i,j)=v1(i,j)+(v1(i,j+1)+v1(i+1,j)+v2(i-1,j)+v2(i,j-1)-4*v1(i,j))*alpha/4;
                t=abs(v2(i,j)-v1(i,j));
            end
            if(t>maxt)
                maxt=t;end
        end
    end
    v1=v2;
end
  H=[H alpha];
  m=m+1;
  V=[V k];
end
plot(H,V,'b *')
axis([1,2,0,18000])


