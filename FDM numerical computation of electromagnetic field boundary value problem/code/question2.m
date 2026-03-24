hy=53;hx=39;phim=160;times=100;m=0;
H=[];
V=[];


while(m<(times))
v1=ones(hy,hx);

v1(hy,:)=zeros(1,hx);
v1(1 , :)=zeros(1,hx);



    alpha=1+rand;
    for i=1:hy
	v1(i,1)=0;
	v1(i,hx)=0;
    end
for i=1:hy
    v1(i,hx)=phim*sin(pi*(i-1)/52/2);
end


v2=v1;maxt=1;t=0;
k=0;

   
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

    H=[H alpha];
    m=m+1;
    V=[V k];
end
plot(H,V,'b *')
axis([1,2,0,1800])


