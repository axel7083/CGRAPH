#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>

#include "../draw/draw.h"



//VAR FOR 
float PATH = 0.20;



const int16_t numVerts = 800;
const int numEdges = 800;												//x1 //x2 //y1 //y2 //x- //y- /x+   /y+
float vertex[3][numVerts] = {{0, 1, 0, 0,   -2,-2,2 , 2 ,   -2,-2,2,2	,0  ,0   ,2   ,2.2 ,-2    ,2.2 ,2    ,2.2},
                             {0, 0, 1, 0,   -2,-2,-2,-2 ,    2, 2,2,2	,-2 ,-2  ,-2  ,-2  ,-2    ,-2  ,-2   ,-2 },
                             {0, 0, 0, 1,   -2, 2,2 ,-2 ,   -2, 2,2,-2	,-2 ,-2.2,0   ,0   ,-2.2  ,-2  ,-2.2 ,2  }};
							 
//float vertex_2[3][numVerts];
				
				// {{X1,X2,X3,X4, X5,X6,X7,X8},{Z1,Z2,Z3,Z4, Z5,Z6,Z7,Z8},{Y1,Y2,Y3,Y4, Y5,Y6,Y7,Y8}}

				
															      //x1/2 /y1/2  /x- /y- /x+  /y+
int sides[2][numEdges]= {{1, 1, 1,5,6,7,5,9 ,10,11,12,9,10,7 ,12,   13   ,15    ,17 ,18 ,19 , 20 }, //Point d'origine
                        {2 , 3, 4,6,7,8,8,10,11,12,9 ,5,6 ,11,8 ,   14   ,16    ,5  ,8  ,8  ,  7}}; //point d'arrivé
						
						
float min,max;

const uint16_t cx = LCD_WIDTH/2;
const uint16_t cy = LCD_HEIGHT/2;

float cameraPos[3] = {3.3, 4.5, -4.2};
float cameraRot[2] = {-0.73, -0.66};


float sensitivity = 0.5;


int coords[2][numVerts];

void run() {
    bool run = 1;
    uint8_t key;
	
	display();
	
    while(run) {
        float x = sensitivity*sin(cameraRot[1]);
        float y = sensitivity*cos(cameraRot[1]);

		
        key = kb_ScanGroup(kb_group_1);
		
		if(key == kb_2nd)
		{
			run = 0;
		}
		
    }
}

void display(void)
{
	asm_RunIndicOn();

	   gfx_SetDrawBuffer();
calculate();
gfx_ZeroScreen();
drawEdges();
asm_RunIndicOff();
        gfx_SwapDraw();
}




void stop() {
    gfx_End();
}

void calculate() {
    int iterator;
    float x;
    float y;
    float z;
    float f;
    for (iterator = 0; iterator < numVerts; iterator++) {
		

        x = vertex[0][iterator];
        y = vertex[1][iterator];
        z = vertex[2][iterator];

        x -= cameraPos[0];
        y -= cameraPos[1];
        z -= cameraPos[2];

        rotate2d(&x, &z, cameraRot[1]);
        rotate2d(&y, &z, cameraRot[0]);

        f = (float)200/z;

        x = x*f;
        y = y*f;

        coords[0][iterator] = (int)x+cx;
        coords[1][iterator] = cy-(int)y;
    }
	
}


void drawEdges() {
    int iterator;
    int start =0;
    int end =0;
    gfx_SetColor(232);
    gfx_FillScreen(255);


    for (iterator = 0; iterator < numEdges; iterator++) {

if(iterator==0) //Axes X
{
gfx_SetColor(160); //Rouge
}
else if(iterator==1) //Axes Y
{
gfx_SetColor(67); //Vert
}
else if(iterator==2) //Axes Z
{
gfx_SetColor(56); //Bleue
}
else if(iterator<=20) //Quadrillage
{
gfx_SetColor(181); //Gris

}
else 
{
	gfx_SetColor(selectColor(vertex[1][sides[0][iterator]-1]));
}

        start = sides[0][iterator]-1;
        end = sides[1][iterator]-1;
        gfx_Line(coords[0][start], coords[1][start], coords[0][end], coords[1][end]);

		//Set coordonnate on Screen
		if(iterator==15)
		{
		gfx_PrintStringXY("x",coords[0][end],coords[1][end]);
		}
		if(iterator==16) //y1/2
		{
		gfx_PrintStringXY("y",coords[0][end],coords[1][end]);
		}
		if(iterator==17) //x-
		{
		gfx_PrintStringXY("-2",coords[0][start]-8,coords[1][start]);
		}
		if(iterator==18) //y-
		{
		gfx_PrintStringXY("-2",coords[0][start]+2,coords[1][start]);
		}
		if(iterator==19) //x+
		{
		gfx_PrintStringXY("2",coords[0][start]-10,coords[1][start]);
		}
		if(iterator==20) //y+
		{
		gfx_PrintStringXY("2",coords[0][start],coords[1][start]);
		}

    }

}

void rotate2d(float* x, float* y, float rad) {
    float c = cos(rad);
    float s = sin(rad);
    float rox = *x;
    float roy = *y;

    rox = *x*c-*y*s;
    roy = *y*c+*x*s;

    *x = rox;
    *y = roy;
}


void setVertex(int nb_points,float x,float y,float z)
{

							vertex[0][nb_points]=	x;
							vertex[1][nb_points]=	z; //WARNING Z AND Y ARE REVERSED
							vertex[2][nb_points]=	y;

}

void setSides(int nb_edges,int nb_points)
{
							sides[0][nb_edges]=nb_points-1;
							sides[1][nb_edges]=nb_points;

}


void show(int nb_points)
{
	

				printIntXY(abs(vertex[0][nb_points]*100),20,80,8);
				gfx_PrintStringXY("x :",0,80);

				printIntXY(abs(vertex[1][nb_points]*100),20,90,8);
				gfx_PrintStringXY("y :",0,90);
				
				printIntXY(abs(vertex[2][nb_points]*100),20,100,8);
				gfx_PrintStringXY("z :",0,100);


}

void printIntXY(int var, int x, int y, int dec) {
          gfx_SetTextXY(x,y);
          gfx_PrintUInt(var,dec);
}


int selectColor(float height)
{

float size= (fabs(min)+fabs(max))/20;

if(min==max)
{
return 112;
}
	
if(height < max-size*20)
{
return 96;
}
else if(height < max-size*19)
{
return 128;
}
else if(height < max-size*18)
{
return 161;
}

else if(height < max-size*17)
{
return 194;
}

else if(height < max-size*16)
{
return 195;
}

else if(height < max-size*15)
{
return 228;
}

else if(height < max-size*14)
{
return 229;
}

else if(height < max-size*13)
{
return 230;
}

else if(height < max-size*12)
{
return 199;
}

else if(height < max-size*11)
{
return 134;
}

else if(height < max-size*10)
{
return 101;
}

else if(height < max-size*9)
{
return 142;
}

else if(height < max-size*8)
{
return 95;
}

else if(height < max-size*7)
{
return 126;
}

else if(height < max-size*6)
{
return 125;
}

else if(height < max-size*5)
{
return 92;
}

else if(height < max-size*4)
{
return 59;
}

else if(height < max-size*3)
{
return 58;
}

else if(height < max-size*2)
{
return 57;
}
else
{
return 8;
}









	return 255;
}

void computeMinMax(int nb_pt)
{
	int i;
	int posX=10;
	int posY=0;
	min = 0;
	max = 0;
	

for(i=20;i < nb_pt ; i++)
{


if(vertex[1][i]<min)
{
min = vertex[1][i];
}

if(vertex[1][i]>max)
{
max = vertex[1][i];	
}




}//end loop



}



//Select precision for PATH
float precision(void)
{
    bool start = 1;
    uint8_t key;
print_string_centered("Necessary precision?",50);
print_string_centered("from 1 to 6. ",60);
print_string_centered("1 : high precision",80);
print_string_centered("6 : low precision",90);
	
while(start) {

        key = kb_ScanGroup(kb_group_3);
        switch (key) {
        case kb_1	:
		gfx_ZeroScreen();
		    gfx_FillScreen(255);

print_string_centered("Loading with precision 1",50);
		return 0.22;
//
            break;
        case 	kb_4:
				gfx_ZeroScreen();
				    gfx_FillScreen(255);

print_string_centered("Loading with precision 4",90);
		return 0.35;
            break;
        }

        key = kb_ScanGroup(kb_group_4);
        switch (key) {
        case kb_2:
				gfx_ZeroScreen();
				    gfx_FillScreen(255);

print_string_centered("Loading with precision 2",90);
		return 0.25;

            break;
        case kb_5:
				gfx_ZeroScreen();
				    gfx_FillScreen(255);

print_string_centered("Loading with precision 5",90);
		return 0.40;

            break;
        }

		key = kb_ScanGroup(kb_group_5);
        switch (key) {
        case kb_3:
						gfx_ZeroScreen();
						    gfx_FillScreen(255);

print_string_centered("Loading with precision 3",90);
		return 0.30;

            break;
        case kb_6:
						gfx_ZeroScreen();
						    gfx_FillScreen(255);

print_string_centered("Loading with precision 6",90);
		return 0.50;

            break;
        }

}//end while
return 0.22;
}



void print_string_centered(const char *str,int y) {
   gfx_PrintStringXY(str, (gfx_lcdWidth-gfx_GetStringWidth(str)) / 2,y);
}



