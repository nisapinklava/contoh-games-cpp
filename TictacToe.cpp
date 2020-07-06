#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include<iostream.h>
#include<stdio.h>
void main()
{
	int gdriver = DETECT, gmode;
	int userfont;
	int i,midx=0, midy=0,x=40,score=0,remaining=3,speed,move,flag;
	char c,temp[5];
	void show(int score,int remaining);
	randomize();
	initgraph(&gdriver, &gmode, "");
	settextstyle(4,0,4);
	ellipse(10,15,0,360,10,15);
	setfillstyle(SOLID_FILL,WHITE);
	floodfill(10,15,WHITE);
	unsigned size_egg=imagesize(0,0,20,30);
	void *egg;
	egg=malloc(size_egg);
	getimage(0,0,20,30,egg);
	cleardevice();
	setcolor(BROWN);
	arc(x, 0,180 /*stangle*/,360 /*endangle*/,40 /*radius*/);
	arc(x, 1,180 /*stangle*/,360 /*endangle*/,39 /*radius*/);
	arc(x, 2,180 /*stangle*/,360 /*endangle*/,38 /*radius*/);
	arc(x, 3,180 /*stangle*/,360 /*endangle*/,37 /*radius*/);
	arc(x, 4,180 /*stangle*/,360 /*endangle*/,36 /*radius*/);
	arc(x, 5,180 /*stangle*/,360 /*endangle*/,35 /*radius*/);
	arc(x, 6,180 /*stangle*/,360 /*endangle*/,34 /*radius*/);
	setcolor(BROWN);
	line(x-34,10,x+34,10);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(x,12,BROWN);
	unsigned size_bucket=imagesize(0,0,80,40);
	void *bucket;
	bucket=malloc(size_bucket);
	getimage(0,0,80,40,bucket);
start:midx=0, midy=0,x=40,score=0,remaining=3,speed=5,move=5;
	cleardevice();
	setcolor(YELLOW);
	settextstyle(0,0,2);
 //outtextxy(0,0,"Eggitarian");
	outtext("Eggs : ");
	outtext(itoa(score,temp,10));
	outtext("  Buckets Left :");
	outtext(itoa(remaining,temp,10));
	while(1)
	{
		putimage(x,getmaxy()-40,bucket,1/*XOR_PUT*/);
		if(remaining==0)
			break;
		midy+=1;
		if(midy>getmaxy()-40)
		{
			midy=80;
			midx=random(getmaxx()-40);
			if(flag!=1)
			{
				remaining--;
				cleardevice();
				putimage(x,getmaxy()-40,bucket,1/*XOR_PUT*/);
				show(score,remaining);
			}
		}
		putimage(midx,midy,egg,XOR_PUT);
		delay(speed);
		delay(1);
		putimage(x,getmaxy()-40,bucket,1/*XOR_PUT*/);
		if(kbhit())
		{
			c=getche();
			if(c==27)
				break;
			else if(c==75)
			{
				if(x<=0)
					x=0;
				else
					x=x-move;
			}
			else if(c==77)
			{
				if(x>=getmaxx()-80)
					x=getmaxx()-80;
				else
					x=x+move;
			 }
		}
		flag=0;
		for(i=x+20;i<x+80;i++)
		{
			if(midx+20 == i && midy == getmaxy()-40)
			{
				flag=1;
				score++;
				if(score==5)
					speed=speed-1;
				else if(score==11)
					speed=speed-1;
				else if(score==17)
					speed=speed-2,move=6;
				else if(score==25)
					speed=speed-1,move=8;
				cleardevice();
				putimage(midx,midy,egg,XOR_PUT);
				show(score, remaining);
				break;
			}
		}
		putimage(midx,midy,egg,XOR_PUT);
	}
	cleardevice();
	fflush(stdin);
	flushall();
	settextstyle(0,0,10);
	outtextxy(0,getmaxy()/2-150,"  Game");
	outtextxy(0,getmaxy()/2-50,"  Over");
	sleep(4);
	fflush(stdin);
	settextstyle(1,0,4);
	outtextxy(0,getmaxy()/2+70,"         Wanna play again y/n: ");
	fflush(stdin);
	while(1)
	if(getch()=='y')
		goto start;
	else if(getch()=='n')
		exit(0);
	else
		continue;
}
void show(int score,int remaining)
{
	char temp[5];
	outtext("Eggs : ");
	outtext(itoa(score,temp,10));
	outtext("  Buckets Left :");
	outtext(itoa(remaining,temp,10));
}
