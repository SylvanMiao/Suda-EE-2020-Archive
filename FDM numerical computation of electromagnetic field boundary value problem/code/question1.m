hy=27;hx=20;phim=160;
v1=ones(hy,hx);

v1(hy,:)=zeros(1,hx);
v1(1 , :)=zeros(1,hx);

for i=1:hy
	v1(i,1)=0;
	v1(i,hx)=0;
end
for i=1:hy
    v1(i,hx)=phim*sin(pi*(i-1)/26);
end

v2=v1;maxt=1;t=0;
k=0;alpha=1+rand;
while(maxt>1e-5)
	k=k+1;
	maxt=0;
	for i=2:hy-1
		for j=2:hx-1
	      		v2(i,j)=v1(i,j)+(v1(i,j+1)+v1(i+1,j)+v2(i-1,j)+v2(i,j-1)-4*v1(i,j))*alpha/4;
			t=abs(v2(i,j)-v1(i,j));
			if(t>maxt) 
                maxt=t;end
		end
	end
	v1=v2;
end



subplot(1,2,1),mesh(v2)
axis([0,hx,0,hy,0,10])
subplot(1,2,2),contour(v2,15)
hold on
x=1:1:hx;
y=1:1:hy;
[xx,yy]=meshgrid(x,y);
[Gx,Gy]=gradient(-v2,5,5);
quiver(xx,yy,Gx,Gy,2,'r')
axis([-5,hx+5,-5,hy+5])
plot([1,1,hx,hx,1],[1,hy,hy,1,1],'k')
startx=1:2.5:51;
starty=ones(size(startx))*51;
hold off
	