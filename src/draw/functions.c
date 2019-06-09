#ifdef COMPILE_PC


/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>



uint8_t key(void)
{
bool pressed = false;
kb_Reset();
kb_ScanGroup(7);
kb_Scan();

/*while(pressed == false) //tant que une touches n'a pas été enclenché attendre.
{ */

    kb_Scan();



    //groupe 1

if(kb_ScanGroup(kb_group_1) == kb_Graph) //Graphe
{
pressed = true;
return 15;
}

if(kb_ScanGroup(kb_group_1) == kb_Trace) //Trace
{
pressed = true;
return 14;
}

if(kb_ScanGroup(kb_group_1) == kb_Zoom) //Zoom
{
pressed = true;
return 13;
}

if(kb_ScanGroup(kb_group_1) == kb_Window) //fenêtre
{
pressed = true;
return 12;
}

if(kb_ScanGroup(kb_group_1) == kb_Yequ) //f(x)
{
pressed = true;
return 11;
}

if(kb_ScanGroup(kb_group_1) == kb_2nd) //2nd
{
pressed = true;
return 21;
}

if(kb_ScanGroup(kb_group_1) == kb_Mode) //Mode
{
pressed = true;
return 22;
}

if(kb_ScanGroup(kb_group_1) == kb_Del)
{
pressed = true;
return 23;
}

    //groupe 2
if(kb_ScanGroup(kb_group_2) == kb_Alpha)
{
pressed = true;
return 31;
}
    //groupe 3

if(kb_ScanGroup(kb_group_3) == kb_0) //0
{
pressed = true;
return 102;
}

if(kb_ScanGroup(kb_group_3) == kb_1) //1
{
pressed = true;
return 92;
}

if(kb_ScanGroup(kb_group_3) == kb_4) //4
{
pressed = true;
return 82;
}

if(kb_ScanGroup(kb_group_3) == kb_7) //7
{
pressed = true;
return 72;
}

    //groupe 4

if(kb_ScanGroup(kb_group_4) == kb_2) //2
{
pressed = true;
return 93;
}

if(kb_ScanGroup(kb_group_4) == kb_5) //5
{
pressed = true;
return 83;
}

if(kb_ScanGroup(kb_group_4) == kb_8) //8
{
pressed = true;
return 73;
}

    //groupe 5

if(kb_ScanGroup(kb_group_5) == kb_3) //3
{
pressed = true;
return 94;
}

if(kb_ScanGroup(kb_group_5) == kb_6) //6
{
pressed = true;
return 84;
}

if(kb_ScanGroup(kb_group_5) == kb_9) //9
{
pressed = true;
return 74;
}

    //groupe 6
if(kb_ScanGroup(kb_group_6) == kb_Enter) //press Enter
{
pressed = true;
return 105;
}

    //groupe 7

if(kb_ScanGroup(kb_group_7) == kb_Down) //Down
{
pressed = true;
return 34;
}

if(kb_ScanGroup(kb_group_7) == kb_Left) //Left
{
pressed = true;
return 24;
}

if(kb_ScanGroup(kb_group_7) == kb_Right) //Right
{
pressed = true;
return 26;
}

if(kb_ScanGroup(kb_group_7) == kb_Up) //Up
{
pressed = true;
return 25;
}
/*} //fin boucle*/

return 0;
} //fin fonction touches


#else
typedef int make_iso_compilers_happy;
#endif
