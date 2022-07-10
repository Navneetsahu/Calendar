#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>

#define LEAP_YEAR (year%4==0 && year%100 ! = 0) || year%400==0)
#define TRUE 1
#define CH '-'
#define MAX_NO 91


//Zellers algorithm
int getZELLER(int month,int year)
{
int Day = 1, Zmonth,Zyear,ZELLER;

  if(month < 3)
    Zmonth = month+10;
  else
    Zmonth = month-2;
  if(Zmonth > 10)
    Zyear = year -1;
  else
    Zyear = year;
  ZELLER =((int)((13*Zmonth -1)/5)+Day+Zyear%100+(int)((Zyear%100)/4)-2*(int)(Zyear/100)+(int)(Zyear/400)+77)%7;
return ZELLER;
}
//function of get key
getkey()
{
union REGS i,o;
while(!kbhit());
i.h.ah = 0;
int86(22,&i,&o);
return (o.h.ah);
}
//printchar
void printchar(char c)
{
int i;
printf("\n\t");
for(i=1;i<=51;i++)
	printf("%c",c);
printf("\n");
}
//print file
void PRINTFILE(int M,int Y,int Z)
{
int i,j;
int Month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char filename[12];
char stryear[5];
char *Month_shortname[] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

FILE *stream;

strcpy(filename,Month_shortname[M-1]);
itoa(Y,stryear,10);
strcat(filename, stryear);
strcat(filename,".txt");

if((stream=fopen(filename,"w"))==NULL)
{
printf("\nERRROR- cannot create file.");
getch();
exit(1);
}
fprintf(stream,"\n\t\t%s %d\n\n\t",Month_shortname[M-1],Y);
for(i=1;i<=MAX_NO;i++)
fprintf(stream, "-");
fprintf(stream,"\n\tSUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\m\t");
for(i=1;i<=MAX_NO;i++)
fprintf(stream,"_");
//setting start positoin
fprintf(stream,"\n");
for(i=1;i<=Z;i++)
fprintf(stream,"\t -");
j = Z;
//printing  dates
for(i =1;i<=Month_day[M-1];i++)
{
if(j++ % 7 == 0)
fprintf(stream,"\n");
fprintf(stream,"\t%2d",i);
}
fprintf(stream,"\n\t");
for(i=1;i<=MAX_NO;i++)
fprintf(stream,"-");
fprintf(stream,"\n\n\t\tCreated by:NAVNEET SAHU & SACHIN DWIvEDI ");
fclose(stream);
}



main()

{
int gd =DETECT, gm,x=150,y=0,month,year,ZELLER,i,j,keycode;
int Month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *Month_name[] = {"JANUARY","FEBURARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
char *Month_shortname[] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
textcolor(CYAN);
setbkcolor(BLUE);
settextstyle(COMPLEX_FONT,HORIZ_DIR,7);

clrscr();
outtextxy(x,y,"CALENDAR");

printf("\n\n\n\n\n\n\t TYPE DATE IN GIVEN FORMAT....\" MONTH(00)-YEAR(0000) \"	\nTO SHOW MONTH OF CALENDAR ");

getch();
//using loop to take inputs
while(TRUE)
{
	fflush(stdin);
	printf("\n\n\n\n\t ENTER MM-YYYY: ");
	scanf("%d-%d", &month,&year);
		if(year <0)
		{
		printf("\n Invalid year value...");
		continue;
		}
		if(year < 100)
		 year += 1900;
		if(year < 1582 || year >4902)
		{
		printf("\n Invalid year value...");
		continue;
		}
		if(month < 1 || month > 12)
		{
		   printf("\n Invalid month value...");
		   continue;
		}

		break;

		}

//looping
do
{
ZELLER =  getZELLER(month,year);
clrscr();
printf("\n\n\t\t\t");
textbackground(month);
printf("%s %d\n",Month_name[month-1],year);
textbackground(BLACK);
//leap year

printchar(CH);
textcolor(12);
printf("\t SUN");
textcolor(LIGHTGREEN);
printf("     MON     TUE     WED     THU     FRI     SAT ");
textcolor(7);
printchar(CH);
for(i=1; i<=ZELLER; i++)
printf("\t - ");
j=ZELLER;
for(i = 1;i<=Month_day[month-1];i++)
{
if(j++ % 7 ==0)
{
printf("\n\t");
textcolor(12);
printf("%2d",i);
textcolor(WHITE);
}
else
printf("	%2d",i);
}
printchar(CH);
printf("\n\n\t\t\t ==> use LEFT,RIGHT,UP,DOWN ARROW KEYS");
printf("\n\n\t\t\t ==> PRESS I for plain interface");
printf("\n\n\t\t\t ==> PRESS P TO PRINT FILE");
printf("\n\n\t\t\t ==> PRESS ESC TO EXIT\n\n\t\t\t");
textcolor(11);
textbackground(9);
textcolor(CYAN);
textbackground(BLACK);

keycode =getkey();
if(keycode ==72)
year++;
if(keycode ==80)
year--;
if(keycode ==77)
{
month++;
if(month>12)
{
month  = 1;
year++;
}
}
if(keycode == 75)
{
month--;
if(month<1)
{
month = 12;
year--;
}
}
if(keycode == 25)
PRINTFILE(month,year,ZELLER);
if(keycode == 23)
{
setbkcolor(WHITE);
textcolor(BLACK);
}
if(keycode == 98)
{
setbkcolor(BLACK);
textcolor(WHITE);
}
goto Top;
Top:
{
printf("over");
}
}
while(keycode!=1);
}











