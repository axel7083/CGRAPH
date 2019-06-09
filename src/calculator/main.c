#ifndef COMPILE_PC

#include <tice.h>
#include <fileioc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <graphx.h>

#include "../dbg.h"

#include "../ast.h"
#include "../parser.h"
#include "../export.h"

#include "../cas/cas.h"
#include "../cas/mapping.h"

#include "../draw/draw.h"
#include "../draw/functions.c"
#include "../draw/save.c"


extern char *ftoa(double f, char *buf, int precision);

void main() {
    ti_var_t y1;
    real_t real_value;

    const uint8_t *data;
    uint16_t size;
    float PATH = 0.22; //good = 0.22

	

    os_ClrHome();
    ti_CloseAll();

	//added by me
	gfx_Begin( gfx_8bpp );
	
    PATH = precision();
	
    y1 = ti_OpenVar(ti_Y1, "r", TI_EQU_TYPE);

    if(y1) {
        error_t err;
        ast_t *e;

        data = ti_GetDataPtr(y1);
        size = ti_GetSize(y1);

        e = parse(data, size, &err);

        ti_Close(y1);

        if(err != E_SUCCESS) {
            LOG(("Couldn't parse equation, reason: %s", error_text[err]));
        } else {
            char buffer[20];
            float x=0, y=0, z =0;
			
			
				int nb_edges = 21;
				int nb_points = 20;
				int loading = 0;
				
				int link =0;

				
            mapping_Init();

		
            //loop through your x and y values here
            for(x = -2; x < 2; x+=0.10) {
                ast_t *x_ast = ast_MakeNumber(num_CreateDecimal(ftoa(x, buffer, 10)));
                mapping_Set(SYM_X, x_ast);
                for(y = -2; y < 2; y+=PATH) {
                    ast_t *y_ast = ast_MakeNumber(num_CreateDecimal(ftoa(y, buffer, 10)));
                    mapping_Set(SYM_Y, y_ast);

                    z = approximate(e, &err);

                    if(err != E_SUCCESS) {
                        LOG(("Couldn't evaluate equation, reason: %s", error_text[err]));
                    } else {
						
						if(z <= 2 && z >= -2)
						{
							setVertex(nb_points,x,y,z); //set point
							nb_points++;
							link++;

												if(link>1 )
												{
													setSides(nb_edges,nb_points);
													nb_edges++;
												}
												
												    
						} //End -2 < z < 2
						else
						{	
						link=0;
						}
						
						
						

                    } //End Z is a sucess.
                }
				loading++;
				gfx_SetColor(0);
				gfx_Rectangle(20,110,280,20);
				gfx_SetColor(35);
				gfx_FillRectangle(20,110,loading*7,20);
				
				/*
				gfx_SetColor(255);
				gfx_FillRectangle(0,40,100,30);

				printIntXY(abs(x*100),20,50,8);
				gfx_PrintStringXY("x :",0,50);
				*/
								
				link=0;

            }
			
			/* useful for logs
			show(250);
			printIntXY(nb_edges, 10, 10, 8);
			printIntXY(nb_points, 10, 20, 8);*/
			
			computeMinMax(nb_points);
            //cleanup only after you have looped through all your values,
            //do not do this every time
            mapping_Cleanup();
        }
		
		print_string_centered("press enter",180);

    while( !os_GetCSC() );

		run();
		
        ast_Cleanup(e);

    } else {
        LOG(("Couldn't open equation"));
    }

gfx_End(); //ferme les graphiques
prgm_CleanUp(); //ferme le programme et retourne à l'écran d'accueil
	
    _OS(asm_ClrTxtShd);
}



#else
typedef int make_iso_compilers_happy;
#endif