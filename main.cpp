/*
 * 2D - Transformations on Polygon
 *
 *  Created on: 15-Feb-2017
 *      Author: Devashish Katoriya
 */

#include<graphics.h>
#include<iostream>

using namespace std;

#define LIMIT 50
#define pi 3.1415926535

class Pixel
{
public :
	void setPixel(double x, double y, int colour)
	{
		putpixel(int(x),int(y),colour);
		//delay(5);
	}
};

class Bresenhem:private Pixel							//Bresenhem Class
{
public :
	void drawline(int,int,int,int);
};

void Bresenhem::drawline(int x1,int y1,int x2,int y2)
{
	int temp;
	if(x1>x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;

		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	double Dx,Dy,length,Xn,Yn,x,y;
	//DDA Algorithm
	Dx = x2-x1;
	Dy = y2-y1;

	if(Dx>Dy)
		length = Dx;
	else
		length = Dy;
	Xn = Dx/length;
	Yn = Dy/length;
	x = x1;
	y = y1;
    setPixel(x, y, WHITE);
	for(int i=1;i<length;i++)
	{
		x = x + Xn;
		y = y + Yn;
        setPixel(floor(x), floor(y), WHITE);
	}
}

class polygon
{
	int Px[LIMIT],Py[LIMIT],n,flag;
public :
	polygon()
	{
		n = 0;
		flag = 0;
	}
	void setFlag()
	{
		flag = 1;
	}
	void clrFlag()
	{
		flag = 0;
	}
	void fill();
	void translate();
	void scale();
	void rotate();
	void draw();
	void read();
	void Xshear();
	void Yshear();
	void reflect();
	void operator +(int P)
	{
		Bresenhem b;
			int Tx,Ty,i;

			Tx = Ty = P;
			/*
			cout<<"\nEnter translation factor :- \n";
			cin>>Tx>>Ty;
			*/
			Tx = Tx/2;
			Ty = Ty/2;

			cleardevice();
			for(i=0;i<n;i++)
			{
				Px[i] = Px[i] + Tx;
				Py[i] = Py[i] + Ty;
			}
			b.drawline(0,240,640,240);
			b.drawline(320,0,320,480);
			draw();
	}
};

void polygon::read()
{
	int i;
	cout<<"\nEnter how many vertices ? ";
	cin>>n;
	if(n<3)
	{
		cout<<"\nPlease enter Number of Sides!";
		return;
	}
	cout<<"\nEnter the vertices :- \n";
	for(i=0;i<n;i++)
	{
		cout<<"\n";
		cin>>Px[i];
		if(Px[i]<-640||Px[i]>640)
		{
			cout<<"\nPlease enter Valid coordinates!";
			cout<<"\n640x480";
			return;
		}
		cin>>Py[i];
		if(Py[i]<-480||Py[i]>480)
		{
			cout<<"\nPlease enter Valid coordinates!";
			cout<<"\n640x480";
			return;
		}
		Px[i] = (Px[i]/2) + 320;
		Py[i] = (Py[i]/2) + 240;
	}
}

void polygon::draw()
{
	int i;

	if(n<3)
	{
		cout<<"\nInvalid Polygon!";
		return;
	}

	//line(Px[0],Py[0],Py[1],Py[1]);
	for(i=0;i<n-1;i++)
	{
		line(Px[i],Py[i],Px[i+1],Py[i+1]);
	}
	line(Px[0],Py[0],Px[n-1],Py[n-1]);
	if(flag == 1)
		fill();
}

//scanline fill algorithm
void polygon::fill()
{
	setFlag();

	int i,k,inter_x[LIMIT],temp,y,Ymax = -480,Ymin = 480;
	float m[LIMIT],dx,dy;

	for(i=0;i<n;i++)
	{
		if(Py[i]>=Ymax)
			Ymax = Py[i];
		if(Py[i]<=Ymin)
			Ymin = Py[i];
	}
	for(i=0;i<n-1;i++)
	{
		dx = Px[i+1] - Px[i];
		dy = Py[i+1] - Py[i];

		if(dx==0)
			m[i] = 0;
		if(dy==0)
			m[i] = 1;
		if((dx!=0) && (dy!=0))
			m[i] = dx/dy;
	}
	dx = Px[n-1] - Px[0];
	dy = Py[n-1] - Py[0];

	if(dx==0)
		m[n-1] = 0;
	if(dy==0)
		m[n-1] = 1;
	if((dx!=0) && (dy!=0))
		m[n-1] = dx/dy;

	for(y=Ymax;y>=Ymin;y--)
	{
		int cnt = 0;
		for(i=0;i<n;i++)
		{
			if(((Py[i]>y) && (Py[i+1]<=y))||((Py[i]<=y) && (Py[i+1]>y)))
			{
				inter_x[cnt] = int(Px[i] + (m[i]*(y-Py[i])));
				cnt++;
			}
		}
		for(k=0;k<cnt;k++)
		{
			for(i=0;i<cnt-1;i++)
			{
				if(inter_x[i]>inter_x[i+1])
				{
					temp = inter_x[i];
					inter_x[i] = inter_x[i+1];
					inter_x[i+1] = temp;
				}
			}
		}
		for(i=0;i<cnt-1;i++)
		{
			line(inter_x[i],y,inter_x[i+1],y);
			delay(10);
		}
	}
}

void polygon::translate()
{
	Bresenhem b;
	int Tx,Ty,i;
	cout<<"\nEnter translation factor :- \n";
	cin>>Tx>>Ty;

	Tx = Tx/2;
	Ty = Ty/2;

	cleardevice();
	for(i=0;i<n;i++)
	{
		Px[i] = Px[i] + Tx;
		Py[i] = Py[i] + Ty;
	}
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	draw();
}

void polygon::scale()
{
	Bresenhem b;
	int i;
	float Sx,Sy;
	cout<<"\nEnter Scaling factor :- \n";
	cin>>Sx>>Sy;

	cleardevice();
	for(i=0;i<n;i++)
	{
		Px[i] = int(((Px[i]-320) * Sx) + 320);
		Py[i] = int(((Py[i]-240) * Sy) + 240);
	}
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	draw();
}

void polygon::rotate()
{
	Bresenhem b;
	int i,temp,temp2;
	double theta;
	char choice;
	cout<<"\nEnter Angle of rotation (in deg.): ";
	cin>>theta;
	theta = (theta*pi)/180;
	cout<<"\nCounter-clockwise or Clockwise ? ";
	cin>>choice;

	if(choice == 'l'||choice == 'L')
	{
		for(i=0;i<n;i++)
		{
			Px[i] = Px[i] - 320;
			Py[i] = Py[i] - 240;
		}
		temp = Px[0];
		temp2 = Py[0];
		for(i=0;i<n;i++)
		{
			Px[i] = Px[i] - temp;
			Py[i] = Py[i] - temp2;


			Px[i] = int((Px[i]*cos(theta)) - (Py[i]*sin(theta)));
			Py[i] = int((Px[i]*sin(theta)) + (Py[i]*cos(theta)));

			Px[i] = Px[i] + temp;
			Py[i] = Py[i] + temp2;

			Px[i] = Px[i] + 320;
			Py[i] = Py[i] + 240;
		}
	}
	else if(choice == 'r'||choice == 'R')
	{
		for(i=0;i<n;i++)
		{
			Px[i] = Px[i] - 320;
			Py[i] = Py[i] - 240;
		}

		temp = Px[0];
		temp2 = Py[0];

		for(i=0;i<n;i++)
		{
			Px[i] = Px[i] - temp;
			Py[i] = Py[i] - temp2;

			Px[i] = int((Px[i]*cos(theta)) + (Py[i]*sin(theta)));
			Py[i] = int((Px[i]*sin(theta)) - (Py[i]*cos(theta)));

			Px[i] = Px[i] + temp;
			Py[i] = Py[i] + temp2;

			Px[i] = Px[i] + 320;
			Py[i] = Py[i] + 240;
		}
	}
	else
	{
		cout<<"\nInvalid Rotation!";
	}
	cleardevice();
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	draw();
}

void polygon::Xshear()
{
	Bresenhem b;
	float Shx;
	int i;
	cout<<"\nEnter X-Shear factor :- \n";
	cin>>Shx;

	Shx = Shx/2;

	cleardevice();
	for(i=0;i<n;i++)
	{
        Px[i] = Px[i] - 320;
		Px[i] = int(Px[i] + (Shx*Py[i]));
        Px[i] = Px[i] + 320;
	}
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	draw();
}

void polygon::Yshear()
{
	Bresenhem b;
	float Shy;
	int i;
	cout<<"\nEnter Y-Shear factor :- \n";
	cin>>Shy;

	Shy = Shy/2;

	cleardevice();
	for(i=0;i<n;i++)
	{
        Py[i] = Py[i] - 240;
		Py[i] = int(Py[i] + (Shy*Px[i]));
        Py[i] = Py[i] + 240;
	}
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	draw();
}

void polygon::reflect()
{
	Bresenhem b;
	int i,ch,temp;
	cout<<"\n 1. About X-Axis";
    cout<<"\n 2. About Y-Axis";
    cout<<"\n 3. About Y = X";
    cout<<"\n 4. About Y = -X";
    cout<<"\n 5. About Origin";
    cout<<"\nEnter choice : ";
	cin>>ch;
	//about y-axis
    if(ch == 2)
	{
		for(i=0;i<n;i++)
		{
			Px[i] = Px[i] - 320;
			Px[i] = -1 * Px[i];
			Px[i] = Px[i] + 320;
		}
	}
    //about x-axis
	else if(ch == 1)
	{
		for(i=0;i<n;i++)
		{
			Py[i] = Py[i] - 240;
			Py[i] = -1 * Py[i];
			Py[i] = Py[i] + 240;
		}
	}
    //about y = x
    else if(ch == 3)
    {
        for (i = 0; i < n; i++)
        {
            Px[i] = Px[i] - 320;
            Py[i] = Py[i] - 240;

            temp = Px[i];
            Px[i] = Py[i];
            Py[i] = temp;

            Px[i] = Px[i] + 320;
            Py[i] = Py[i] + 240;
        }
    }
    //about y = -x
    else if(ch == 4)
    {
        for(i=0;i<n;i++)
        {
            Px[i] = Px[i] - 320;
            Py[i] = Py[i] - 240;

            temp = Px[i];
            Px[i] = -Py[i];
            Py[i] = -temp;

            Px[i] = Px[i] + 320;
            Py[i] = Py[i] + 240;
        }
    }
    //about origin
    else if(ch == 5)
    {
        for(i=0;i<n;i++)
        {
            Px[i] = Px[i] - 320;
            Py[i] = Py[i] - 240;

            Px[i] = -1 * Px[i];
            Py[i] = -1 * Py[i];

            Px[i] = Px[i] + 320;
            Py[i] = Py[i] + 240;
        }
    }
	else
	{
		cout<<"\nInvalid Axis";
        return;
	}
	cleardevice();
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	draw();
}

int main()
{
	float temp;
	int gd,gm,ch;
	gd = DETECT;
	polygon obj;
	Bresenhem b;

	initgraph(&gd,&gm,NULL);

	cout<<"\nProgram for 2D transformation on polygon.";

	obj.read();
	b.drawline(0,240,640,240);
	b.drawline(320,0,320,480);
	obj.draw();

	do
	{
        temp = ch = 0;
		cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout<<"\n 1 for Translation.";
		cout<<"\n 2 for Scaling.";
		cout<<"\n 3 for Rotation.";
		cout<<"\n 4 to  Re-Draw.";
		cout<<"\n 5 to  Fill.";
		cout<<"\n 6 for X-Shear.";
		cout<<"\n 7 for Y-Shear.";
		cout<<"\n 8 for Reflection";
		cout<<"\n 10 to Clear Fill.";
		cout<<"\n 0 to  Exit.";
		cout<<"\nEnter your choice : ";
		cin>>ch;
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		switch(ch)
		{
			case 1 : cout<<"\nEnter translation factor : ";
					 cin>>temp;
					 obj+temp;
					 break;
			case 2 : obj.scale();
					 break;
			case 3 : obj.rotate();
					 break;
			case 4 : cleardevice();
					 obj.read();
					 b.drawline(0,240,640,240);
					 b.drawline(320,0,320,480);
					 obj.clrFlag();
					 obj.draw();
					 break;
			case 5 : obj.fill();
					 break;
			case 6 : obj.Xshear();
					 break;
			case 7 : obj.Yshear();
					 break;
			case 8 : obj.reflect();
					 break;
			case 10 :cleardevice();
					 b.drawline(0,240,640,240);
					 b.drawline(320,0,320,480);
					 obj.clrFlag();
					 obj.draw();
					 break;
			case 0 : break;
			default: cout<<"\nInvalid Option!";
		}
	}while(ch!=0);
	closegraph();
	return 0;
}
