
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
int getkey(){
union REGS j,o;
j.h.ah=0;
int86(22,&j,&o);
return(o.h.ah);
}
void display()
{
	int i,j,xi,yj,brick[5][12],k,rlx=0,rrx=50,rly=0,rry=30,bx=225,by=350,dx=4,dy=-2,x1=330,x2=400,key;

	rectangle(0,0,600,440); //boundary rectangle
	rectangle(x1,410,x2,420); //Striker.
	for(i=0;i<5;i++)
	{
		for(j=0;j<12;j++)
		{
			rectangle(rlx,rly,rrx,rry);
			rlx+=50;
			rrx+=50;
			brick[i][j] = 1;
		}
		rly+=30;
		rry+=30;
	       rlx=0;
	       rrx=50;
	}

	while(1)
	{


		if(by+10>440)
		{
			dy = -dy;
		}
	    if(bx+10>=600 || bx-10<=0)
		{
			dx=-dx;
		}
		if(by-10<=0 )
		{
			dy=-dy;
		}
		if(by+10==410 && bx>=x1)
		{
			setcolor(WHITE);
			rectangle(x1, 410, x2, 420);
			dy=-dy;
		}
		if(by+10==410 && bx>x2)
		{
			setcolor(WHITE);
			rectangle(x1, 410, x2, 420);
			dy = -dy;
			dx = +dx;
		}
		if(by-10<=150)
		{

			i=(by-10)/30;
			j=bx/50;

			if(brick[i][j]==1)
			{
				brick[i][j] = 0;
				dy=-dy;
				rly = i*30;
				rlx = j*50;
				rrx = (j+1)*50;
				rry = (i+1)*30;
				setcolor(BLACK);
				rectangle(rlx, rly,rrx, rry);
				setcolor(WHITE);
				rectangle(0, 0, 600, 440);
				if(brick[i][j-1] == 1)  //left brick
				{
					setcolor(WHITE);
					rectangle((j-1)*50,i*30,j*50,(i+1)*30);
				 }
				 if(brick[i-1][j] == 1) //upper brick
				 {
					setcolor(WHITE);
					rectangle(j*50, (i-1)*30, (j+1)*50, i*30);
				 }
				if(i !=2 && j !=11)    //right brick
				{
					if(brick[i][j+1] == 1)
					{
						setcolor(WHITE);
						rectangle((j+1)*50, i*30, (j+2)*50,(i+1)*30);
					}
				}
			}
		}
		bx=bx+dx;
		by=by+dy;
		setcolor(WHITE);
		circle(bx,by,10);
		 delay(20);
		setcolor(BLACK);
		circle(bx,by,10);

		if(kbhit())
		{
			setcolor(BLACK);
			rectangle(x1,410,x2,420);
			key=getkey();
			if(key==75 && x1>0)
			{
				x1=x1-10;     +
				x2=x2-10;
			}
			if(key==77 && x2<600)
			{
				x1=x1+10;
				x2=x2+10;
			}
			if(key==1)
			{
				exit(0);
			}
			setcolor(WHITE);
			rectangle(x1,410,x2,420);

		}
	}
 }

void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:/TURBOC3/BGI");
	display();
	getch();
	closegraph();

}