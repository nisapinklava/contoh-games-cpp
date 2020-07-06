//PROGRAM OF A GAME CALLED CRAZY BALLS
//					DEVELOPED BY
//									SUKET ARORA
//									MCA 2ND SEMESTER


													//HEARDER FILES SECTION
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

music(int type);

void main()
{
	char c;                            	//FOR KEY STROKES
	char seconds[4];                  	//FOR MEAURING TIME
	int ptr,x,y;                        //CAUGHTER BALL CORDINATES
	int ballx,bally;							//DESIRED BALL CORDINATEDS
	int move;                				//VALUE FOR BALL MOVEMENT
	int speed;                          //VALUE FOR CRAZY BALLS MOVEMENT
	int score;                          //SCORE VARIABLE
	int driver=DETECT,mode;             //GRAPHICS DRIVERS AND MODE VARIABLES
	time_t start,end;							//TIME VARIABLES

	initgraph(&driver,&mode,"");        //INITIALIZING GRAPHIC SCREEN

	{                            			//LOADING
	cleardevice();
	setcolor(GREEN);
	settextstyle(8,HORIZ_DIR,8);
	outtext(" CRAZY BALLS");
	int midx=getmaxx()/2;
	int midy=getmaxy()/2;
	settextstyle(8,HORIZ_DIR,5);
	outtextxy(midx-90,midy,"Loading");
	settextstyle(8,HORIZ_DIR,5);
	outtextxy(1,midy+150,"Devolped by:");
	setcolor(LIGHTGREEN);
	settextstyle(8,HORIZ_DIR,5);
	outtextxy(midx-20,midy+150,"SUKET ARORA");
	setcolor(GREEN);
	for(int pass=1;pass<=9;pass++)
		for(int j=-90;j<=90;j=j+30)
		{
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,GREEN);
		circle(midx+j,midy+100,12);
		circle(midx+j,midy+100,10);
		floodfill(midx+j,midy+100,GREEN);
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,BLACK);
		delay(150);
		floodfill(midx+j,midy+100,BLACK);
		}
	 }
	cleardevice();
	int midx=getmaxx()/2;
	int midy=getmaxy()/2;

	settextstyle(8,HORIZ_DIR,8);
	setcolor(LIGHTGREEN);
	outtextxy(20,20,"PRESS CHOICE");
	setcolor(GREEN);
	settextstyle(8,HORIZ_DIR,4);
	outtextxy(50,midy-50,"GAME HELP     H/h");
	outtextxy(50,midy,"PLAY           ANY OTHER KEY");
	//music(3);
	//cleardevice();
	while(1)                                //CHECK IF WANNA PLAY AGAIN
	{
		char c=music(3);
		if(c=='h' || c=='H')
		{
			cleardevice();
			highvideo();
			textcolor(GREEN);
			printf("
				GAME HELP");
			printf("

This is a very interesting game");
			printf("

In the game there are 10 CRAZY BALLS which moves across the screen.");
			printf("

User have to catch the GREEN BALL on the screen");
			printf("

Which are located randomely on the screen.");
			printf("

But beware of the CRAZY BALLS.");
			printf("

If you hit with any of them then your game will be over.");
			printf("

The level of difficulty will increases with more GREEN BALLS you collect.");
			printf("




				ENJOY GAME");
			printf("



			PRESS ANY KEY TO START GAME");
			getch();
			break;
		}
		else
			break;
	}
start:closegraph();
	initgraph(&driver,&mode,"");
	sleep(1);										    //START GAME

	randomize();                        //RANDOM NUMBER GENERATOR

	settextstyle(4,0,8);               //DESIGNING CRAZY BALLS
	setcolor(BLUE);
	circle(4,4,4);
	setfillstyle(SOLID_FILL,BLUE);
	floodfill(4,4,BLUE);
	unsigned size_balls=imagesize(0,0,8,8);
	void *ball;
	ball=malloc(size_balls);
	getimage(0,0,8,8,ball);

	cleardevice();

	setcolor(RED); 							//DESIGNING CAUGHTER BALL
	circle(15,15,15);
	setfillstyle(SOLID_FILL,RED);
	floodfill(15,15,RED);
	unsigned size_caughter=imagesize(0,0,30,30);
	void *caughter;
	caughter=malloc(size_caughter);
	getimage(0,0,30,30,caughter);

	cleardevice();

	setcolor(GREEN);								//DESINING BACKGROUND
	outtext("  Crazy Balls");
	setlinestyle(1,1,1);
	rectangle(0,100,getmaxx(),getmaxy());
	setviewport(1,101,getmaxx()-1,getmaxy()-1,0);

	x=0;                             //INITALIZING CORDINATES OF CRAZY BALLS
	y=0;
	int yy[10]={100,300,100,350,200,250,300,150,280,351};
	int xx[10]={2,135,97,190,213,540,460,570,110,350};
	int i[10]={1,1,1,1,1,1,1,1,1,1};
	int j[10]={1,1,1,1,1,1,1,1,1,1};

	move=15;                        			//MOVEMENT FOR CAGTHTER
	speed=15;                              //LEVEL 1
	score=0;                               //SCORE EQUALS TO ZERO

	start=time(NULL);                      //STARTING TIMER

	circle(ballx=random(630),bally=random(380),2);  //DESIRED BALL LOCATING

	while(1)
	{
		for(int ptrx=0;ptrx<30;ptrx++)		//CHECK FOR BALL CAUGHT
			for(int ptry=0;ptry<30;ptry++)
				if(ballx==x+ptrx && bally==y+ptry)
				{
					clearviewport();
					music(1);
					circle(ballx=random(630),bally=random(370),2);
					score++;                   //SCORING

					switch(score)              //DETERMINING LEVEL
					{
						case 8:
						case 16:
						case 24:
						case 32:
						case 40:speed=speed-3;	//CHANGING LEVEL
					}
					break;
				}

		putimage(x,y,caughter,XOR_PUT);

		for(ptr=0;ptr<10;ptr++)        		//CRAZY BALL HITTING CHECK
			if(xx[ptr] != -10000 && yy[ptr] != -10000)
				for(int loc=1;loc<=30;loc++)
					for(int temp=1;temp<=8;temp++)
						if(x+loc==abs(xx[ptr]) && y==abs(yy[ptr]+temp) || x==abs(xx[ptr]+temp) && y+loc==abs(yy[ptr]))
						{	music(2);goto end;  }          //IF HITTED GOTO END OF PROGRAM

		if(!kbhit())  								//CRAZY BALLS MOVEMENT
		{
			for(ptr=0;ptr<10;ptr++)          //FOR TEN CRAZY BALLS
			{
				if(ptr%2==0)                  //FIVE BALLS UPWARD DIRCTION
				{
					yy[ptr]+=i[ptr];
					xx[ptr]+=j[ptr];
				}
				else                       	//FIVE BALLS DOWNWARD DIRECTION
				{
					yy[ptr]-=i[ptr];
					xx[ptr]-=j[ptr];
				}
				putimage(xx[ptr],yy[ptr],ball,XOR_PUT);
			}

			delay(speed);                   //TIME DELAY ACCORDING TO LEVEL

			for(ptr=0;ptr<10;ptr++)        //CHECK FOR CRAZY BALL HITTING END OF VIEWPORT
			{
				putimage(xx[ptr],yy[ptr],ball,XOR_PUT);
				if(yy[ptr]>=getmaxy()-110 || yy[ptr]<0)  //CHANGING DIRECTION
					i[ptr]*=-1;
				if(xx[ptr]>=getmaxx()-10 || xx[ptr]<0)   //CHANGING DIRECTION
					j[ptr]*=-1;
			}
		putimage(x,y,caughter,XOR_PUT);
		}

		else if(kbhit())                    //CAUGHTER BALL MOVEMENT
		{
			c=getche();
			if(c==27)                        //Esc FOR EXIT
				break;
			else if(c==75)                   //HORIZONTAL LEFT MOVEMENT
			{
				if(x-move<=0)
					x=0;
				else
				x=x-move;
			}
			else if(c==77)                   //HORIZONTAL RIGHT MOVE
			{
				if(x+30+move>=getmaxx()-2)
					x=getmaxx()-2-30;
				else
					x=x+move;
			}
			else if(c==72)                   //VERTICAL UPWARR MOVE
			{
				if(y-move<=0)
					y=0;
				else
					y=y-move;
			}
			else if(c==80)                   //VERTICAL DOWNWARD MOVE
			{
				if(y+30+move>=getmaxy()-102)
					y=getmaxy()-102-30;
				else
					y=y+move;
			}
		}
	}

end:                                      //END OF GAME

	clearviewport();

	end=time(NULL); 								//END TIME

	fflush(stdin);
	cleardevice();

	settextstyle(7,0,9); 						//SCORE DISPLAY
	outtextxy(0,-120," You Collect");
	outtext("  ");
	outtext(itoa(score,seconds,10));
	outtext("  Balls");
	outtextxy(0,120,"     In");
	outtextxy(20,240,itoa((int)difftime(end,start)/60,seconds,10));
	outtextxy(80,240,":");
	outtextxy(120,240,itoa((int)difftime(end,start)%60,seconds,10));
	outtextxy(240,240,"Minutes");
	sleep(5);
	clrscr();
	cleardevice();
	settextstyle(8,0,3);
	outtext("play agian PRESS y/n : ");

	fflush(stdin);
	while(1)                                //CHECK IF WANNA PLAY AGAIN
	{
		char c=getch();
		if(c=='y'||c=='Y')
			goto start;
		else if(c=='n'||c=='N')
			exit(0);
	}
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
		 delay(3);
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
	  return(getch());

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
	return (0);
}
