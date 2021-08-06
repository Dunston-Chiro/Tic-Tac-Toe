#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include <windows.h>

using namespace std;

int check_win( char plr, int y, int x);

bool gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

char k_box[3][3];

int main()
{
   char a=196,b=179;
   int i, j;

   gotoxy(30,2);
   cout<<"CONTROLS";

   cout<<"\n\n\t\t\tW for up\n\t\t\tA for left\n\t\t\tS for down\n\t\t\tD for right"
       <<"\n\n\t\t\tSpacebar to jump to blank spaces"
       <<"\n\n\t\t\tEnter to set mark X or O ";

   for(j=1;j<=11;j++)
    {
       gotoxy(j,3);
       cout<<a;
       gotoxy(j,5);
       cout<<a;
    }

   for(i=1;i<=7;i++)
    {
       gotoxy(4,i);
       cout<<b;
       gotoxy(8,i);
       cout<<b;
    }

  char ch;

  for(i=0; i<3; i++)
   for(j=0; j<3; j++)
    k_box[i][j]='\0';

  int run_w, run_a, run_s, run_d, run, run1;
  i=0, j=0;
  int p=1, end=0;

  gotoxy(1,9);
  cout<<"Player X...";

  gotoxy(2,2);

   while(1)
    {
       ch=getch();
       switch(ch)
		{
			case 'w':         //for up

				run_w:

				if(i==0)
					i=2;
				else
					i--;

				gotoxy( (4*j)+2, (2*i)+2);

				if(k_box[i][j]!='\0')
					goto run_w;
				else
					break;


			case 'a':         //for left

				run_a:

					if(j==0)
						j=2;
					else
						j--;

					gotoxy( (4*j)+2, (2*i)+2);

					if(k_box[i][j]!='\0')
						goto run_a;
					else
						break;


			case 's':         //for down

				run_s:

					if(i==2)
						i=0;
					else
						i++;

					gotoxy( (4*j)+2, (2*i)+2);

					if(k_box[i][j]!='\0')
						goto run_s;
					else
						break;


			case 'd':         //for right

				run_d:

					if(j==2)
						j=0;
					else
						j++;

					gotoxy( (4*j)+2, (2*i)+2);

					if(k_box[i][j]!='\0')
						goto run_d;
					else
						break;


			case ' ':         //jump to another space

				run:{

					int k=0, last=0;
					j++;


					for(  ; i<3; i++)
					{
						for(  ; j<3; j++)
						{
							if( k_box[i][j]=='\0')
							{
								gotoxy( (4*j)+2, (2*i)+2);
								k=1;
								break;
							}
						}

						if(k==1)
							break;
						else if(i==2 && j==3)
						{
							i=-1, j=0;
							last++;

							if(last==2)
							{
								gotoxy(1,9);
								cout<<"Match Draw...";
								getch();
								exit (0);
							}
						}
						else
							j=0;

					}

					}break;


			default:

				if(p==1)
				{
					k_box[i][j]='X';
					cout<<"X";
					gotoxy(1,9);
					cout<<"Player O...";
					p=0;
					end=check_win('X',i,j);
				}
				else
				{
					k_box[i][j]='O';
					cout<<"O";
					gotoxy(1,9);
					cout<<"Player X...";
					p=1;
					end=check_win('O',i,j);
				}

				if(end==0)
				{
					goto run;
				}

				exit (0);

		}
    }

}

int check_win( char plr, int y, int x)       //to check winner
{
    int c, i[3], j[3], win=0;
    long dd;

     if(x==y)

	for(c=0; c<3; c++)
	 {
	    if(k_box[c][c]!=plr)
	     {
	       win=0; break;
	     }
	   else
	     win=1;

	   i[c]=c, j[c]=c;
	 }

     if(x==(2-y) && win==0)

	for(c=0; c<3; c++)
	 {
	    if(k_box[c][2-c]!=plr)
	     {
	       win=0; break;
	     }
	   else
	     win=1;

	   i[c]=c, j[c]=(2-c);
	 }


     if(win==0)

	for(c=0; c<3; c++)
	 {
	    if(k_box[c][x]!=plr)
	     {
	       win=0; break;
	     }
	   else
	     win=1;

	   i[c]=c, j[c]=x;
	 }

     if(win==0)

	for(c=0; c<3; c++)
	 {
	    if(k_box[y][c]!=plr)
	     {
	       win=0; break;
	     }
	   else
	     win=1;

	   i[c]=y, j[c]=x;
	 }


     if(win==1)
      {
	gotoxy(1,9);
	cout<<"Player "<<plr<<" is Winner...";

	while(!kbhit())
	 {
	   for(c=0; c<3; c++)
	    {
	      gotoxy( (4*j[c])+2, (2*i[c])+2);
	      cout<<" ";
	    }

	   for(dd=0; dd<209990000; dd++);

	   for(c=0; c<3; c++)
	    {
	      gotoxy( (4*j[c])+2, (2*i[c])+2);
	      cout<<plr;
	    }

	   for(dd=0; dd<209990000; dd++);
	 }
      }

    return win;
}
