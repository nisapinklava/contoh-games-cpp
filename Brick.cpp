#include<process.h>
#include<dos.h>
#include<iostream.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>

#define NULL 0
#define YES 1
#define NO 0

int maxx,maxy,midx,midy;
int bri[3][16];
char str[20];

int music(int type);
int erasebrick(int b,int l);
int drawbrick(int lx,int ly);
int mainscreen();
int bricks();

void main()
{
 again:
 //union REGS ii,oo;
 int ballx,bally,paddlex,paddley,dx=1,dy=-1,oldx,oldy;
 int gm=VGAHI,gd=VGA,playerlevel;
 int i,flag=0,speed=25,welldone=NO,score=0,chance=4,area;
 int layer[3]={25, 50, 75},limit=75,currentlayer=2;
 void *p1, *p2;
 char aga;

 initgraph (&gd,&gm,"");

 maxx=getmaxx();
 maxy=getmaxy();

 midx=getmaxy()/2;
 midy=getmaxy()/2;

 playerlevel=mainscreen();

 switch (playerlevel)
 {
  case 'A':
  case 'a':
	speed=15;
	break;

  case 'N':
  case 'n':
	speed=10;
	break;

  case 'E':
  case'e':
  speed=5;
 }

 rectangle(0,0,maxx,maxy-13-13);
 bricks();

 setfillstyle(SOLID_FILL, YELLOW);
 rectangle(midx-25,maxy-50,midx+25,maxy-20-9);
 floodfill(midx,maxy-33,WHITE);

 setfillstyle(SOLID_FILL,LIGHTBLUE);
 circle (midx,maxy-50-13,12);
 floodfill(midx,maxy-50-15, WHITE);

 area=imagesize(midx-12,maxy-50-12-12-1,midx+12,maxy-50-1);

 p1=malloc(area);

 area=imagesize(midx-25,maxy-50,midx+25,maxy-20-9);
 p2=malloc(area);

 if(p1==NULL || p2==NULL)
 {
 cout<<"insufficient memory!!";
 exit(1);
 }

 getimage(midx-12,maxy-50-12-12-1,midx+12,maxy-50-1,p1);
 getimage(midx-25,maxy-50,midx+25,maxy-20-9,p2);

 paddlex=midx-25;
 paddley=maxy-50;
 ballx=midx-12;
 bally=maxy-50-12-12-1;

 settextstyle(0,0,1);
 outtextxy(300,470,"Balls remaining:");

 for (i=0;i<3;i++)
 {
  circle(515+i*40,maxy-12,12);
  floodfill(515+i*40,maxy-12,WHITE);
 }

 outtextxy (50,470,"Your Score:");
 sprintf(str,"%4d",score);
 outtextxy(140,470,str);

 settextjustify(CENTER_TEXT,CENTER_TEXT);
 settextstyle(0,HORIZ_DIR,0);

 while (1)
 {
 flag=0;

 oldx=ballx;
 oldy=bally;

 ballx=ballx+dx;
 bally=bally+dy;

 if(bally>50)
 {
 limit=75;
 currentlayer=2;
 }
 else
 {
 if(bally>25)
 {
 limit=50;
 currentlayer=1;
 }
 else
 {
 limit=25;
 currentlayer=0;
 }
 }

 if (ballx<1)
 {
 music(5);
 ballx=1;
 dx=-dx;
 }
 if(ballx>(maxx-24-1))
 {
 music(5);
 ballx=maxx-24-1;
 dx=-dx;
 }

 if(bally<1)
 {
 music(5);
 bally=1;
 dy=-dy;
 }

if (bally<=limit)
{
 if (bri[currentlayer][(ballx+10)/40]==1)
 {
 for(i=1;i<=6;i++)
 {
 if(bri[currentlayer][(ballx+i+10)/40]==0)
 {
 ballx=ballx+i;
 flag=1;
 break;
 }

 if(bri[currentlayer][(ballx-i+10)/40]==0)
 {
 ballx = ballx -i;
 flag = 1;
 break;
 }
}

 if(!flag)
 {
 if(bally<layer[currentlayer - 1])
 {
 currentlayer--;
 limit=layer[currentlayer];
 }

 putimage(oldx,oldy,p1,OR_PUT);

 putimage(oldx,oldy,p1,XOR_PUT);

 putimage(ballx,bally,p1,XOR_PUT);

 delay(speed);

 continue;
 }
}
 music (4);

 erasebrick((ballx+10)/40,currentlayer);

 if((ballx+10)/40>=15)
  line(maxx,0,maxx,75) ;

 if((ballx+10)/40==0)
  line(0,0,0,75);

 if(currentlayer==0)
  line(0,0,maxx,0);

 bri[currentlayer][(ballx+10)/40]=1;

 bally=bally+1;
 dy=-dy;
 score+=5;

 setviewport(150,470,180,479,1);
 clearviewport();
 setviewport(0,0,maxx,maxy,1);

 sprintf(str,"%4d",score);
 outtextxy(152,475,str);
 if(welldone == NO)
  welldone = YES;
 else
 {
 settextstyle(7,0,4);
 outtextxy(midx,midy,"Well done!");
 music(1);
 settextstyle(0,0,1);
 }
}

 if(bally>75 && welldone == YES)
 {
 setviewport(midx-40*2.5,midy-40/2,midx+40*2.5,midy+40/2,1);
 clearviewport();
 setviewport(0,0,maxx,maxy,1);
 welldone = NO;
 }
 if(bally>maxy-12-12-50-1)
 {
  welldone = NO;
  if(ballx<paddlex-20 || ballx>paddlex + 50)
 {
  while(bally<maxy)
	{
	putimage(oldx,oldy,p1,XOR_PUT);

	putimage(ballx,bally,p1,XOR_PUT);
	delay(speed);
	oldx=ballx;
	oldy=bally;
	ballx=ballx + dx;
	bally = bally + dy;
	}
  chance--;
  score-=20;
  setviewport(150,470,180,479,1);
  clearviewport();
  setviewport(0,0,maxx,maxy,1);
  //str<<setw(4)<<score;
  outtextxy(152,475,str);
  music(2);
  if (chance)
  {
	setcolor(BLACK);
	putimage(515+(chance-1)*40-12,maxy-19-5,p1,XOR_PUT);
  }

  if(!chance)
  {
	settextstyle(7,0,4);
	outtextxy(midx,midy,"Try again");
	music(3);
	cleardevice();
	outtext("Wanna play again y/n :");
	aga=getch();
	cleardevice();
	if(aga=='y'||aga=='Y')
		goto again;

	closegraph();
	restorecrtmode();
	exit(0);
  }
}
 music(5);
 bally=maxy-12-12-50-1;
 dy = -dy;
}
  putimage(oldx,oldy,p1,OR_PUT);
  putimage(oldx,oldy,p1,XOR_PUT);
  putimage(ballx,bally,p1,XOR_PUT);
 if(score==(48*5)-((4-chance)*20))
  {
  settextstyle(7,0,4);
  outtextxy(midx,midy,"You win!!!");

  if(score<240)
  {
  outtextxy(midx,midy+30,"Try to score 240");
  getch();
  }
  else
  {
  outtextxy(midx,midy+30,"You are simply GREAT!");
  music(3);
  getch();
  }
  closegraph();
  restorecrtmode();
  exit(0);
}
  delay(speed);
  if(kbhit())
  {
  char c;
  c=getche();
  //ii.h.ah = 0;
  //int86(22,&ii,&oo);
  //putimage(paddlex,paddley,p2,OR_PUT);
  putimage(paddlex,paddley,p2,XOR_PUT);

  if(/*oo.h.ah*/c==27/* 1*/)
  exit(0);
  if(/*oo.h.ah*/c==75)
	paddlex=paddlex-20;//cout<<"hello",getch();
  if(/*oo.h.ah*/c==77)
  paddlex=paddlex+20;
  if(paddlex<1)
	paddlex = 1;

 if(paddlex>588)
  paddlex=588;

  putimage(paddlex,paddley,p2,XOR_PUT);
 }
 }
}
 mainscreen()
{

 int ff[12][40] = {
			  1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,
			  1,1,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,
			  0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,
			  0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,
			  1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
			  0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,
			  0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,
			  0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,
			  0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,
			  1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,
			  0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,
			  0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
			  0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,
			  0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,
			  0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
			  1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,0,0,0,
			  0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,
			  0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,
			  0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,0,0,0,
		  };
 int i,j,lx=0,ly=0,ch;
 rectangle (0,0,maxx,maxy);

 for(i=0;i<12;i++)
 {
 for(j=0;j<40;j++)
 {
  if(ff[i][j])
  {
	 setfillstyle(SOLID_FILL,RED);
	 rectangle(lx,ly,lx+15,ly+9);
	 floodfill(lx+3,ly+3,WHITE);
  }
	  lx=lx+16;
 }
 lx = 0;
 ly=ly+10;
}

 line(0,maxy-12,maxx,maxy-12);
 setfillstyle(XHATCH_FILL,WHITE);

 setfillstyle(SOLID_FILL,WHITE);
// rectangle(midx-25,maxy-7-12-50,midx+25,maxy-12-50);
// circle(midx,maxy-13-12-50, 12);
 settextstyle(3,0,4);
 //outtextxy(midx-200,midy,"MCA (SOFTWARE SYSTEM) PROJECT");
 
 outtextxy(midx-200,midy+50,"Submitted By :Abhishek Sharma");

 music (3);

 while (1)
 {
  setviewport(1,125-12,maxx-1,maxy-1,1);
  clearviewport();

  setviewport(0,0,maxx,maxy,1);
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT,0,2);
  outtextxy(20,235,"Select any of the following:");
  outtextxy(20,265,"Play (P)");
  outtextxy(20,295,"Instructions (I)");
  outtextxy(20,325,"Exit (E)");

  ch =0;

  while (!(ch=='E'|| ch=='I'|| ch=='P'))
  {
	fflush (stdin);
	if((ch=getch())==0)
	 getch();
	else
	 ch=toupper(ch);
  }

  if(ch=='P')
	 break;

  switch (ch)
  {
	 case 'I':
	 setviewport(1,125-12,maxx- 1,maxy -1,1);
	 clearviewport();

	 setviewport(0,0,maxx,maxy,1);
	 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	 outtextxy(20,200,"Instructions:-");
	 settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	 outtextxy(20,240,"Use left and right arrow keys to move paddle.");
	 outtextxy(20,270,"If you don't collect the ball on the paddle, you lose the ball.");
	 outtextxy(20,300,"On loosing a ball you loose 20 points");
	 outtextxy(20,330,"On taking a brick you gain 5 points.");
	 outtextxy(20,365,"Press any key...");
	 fflush(stdin);
	 if(getch()==0)
		 getch();
		 break;

	 case 'E':
	closegraph();
	restorecrtmode();
	exit(0);
  }
 }

 setviewport(1,125- 12,maxx-1,maxy-1,1);
 clearviewport();

 setviewport(0,0,maxx,maxy,1);
 settextstyle(DEFAULT_FONT,0,2);
 outtextxy(20,150,"Select any of the following levels:");
 outtextxy(20,200,"Novice(N)");
 outtextxy(20,245,"Advanced(A)");
 outtextxy(20,290,"Expert(E)");

 fflush(stdin);
 if((ch=getch())==0)
	  getch();

 clearviewport();

 return (ch);
}
bricks()
 {
  int i,j,lx=1,ly=0;

  for(i=0;i<3;i++)
  {
	 for(j=0;j<=16;j++)
	 {
		drawbrick (lx,ly);

		lx=lx+40;
	 }
	 lx=0;
	 ly=ly+25;
	}
  }

 drawbrick(int lx,int ly)
 {
  setfillstyle(SOLID_FILL,RED);
  setcolor(WHITE);
  rectangle(lx,ly,lx+40,ly+25);
  rectangle(lx+2,ly+2,lx+40-2,ly+25-2);
  floodfill(lx+3,ly+3,WHITE);
 }
 erasebrick(int b,int l)
 {
  setfillstyle(SOLID_FILL,BLACK);
  setcolor(BLACK);
  rectangle(b*40,1*25,(b*40)+40,(l*25)+25);
  rectangle(b*40+1,l*25,(b*40)+40-1,(l*25)+25-1);
  rectangle(b*40+2,l*25,(b*40)+40-2,(l*25)+25-2);
  floodfill(b*40+3,l*25+3,BLACK);
  setcolor(WHITE);
 }

 music(int type)
 {
  float octave[7]={130.81,146.83,164.81,174.61,
			196,220,246.94};
  int n,i;

  switch(type)
  {
	 case 1:
	 for(i=0;i<7;i++)
	 {
		 sound(octave[i]*8);
		 delay(30);
	 }
	 nosound();
	 break;

	 case 2:
	 for(i=0;i<15;i++)
	 {
		n=random(7);
		sound(octave[n]*4);
		delay(100);
	 }
	 nosound();
	 break;

	 case 3:
	 while(!kbhit())
	 {
		n=random(7);
		sound(octave[n]*4);
		delay(100);
	 }
	 nosound();

	if(getch()==0)
	  getch();

	break;

	 case 4:
	 for(i=4;i>=0;i--)
	 {
		sound(octave[i]*4);
		delay (15);
	 }
	 nosound();
	 break;

	 case 5:
	 sound(octave[6]*2);
	 delay(50);
	 nosound();
  }
}












