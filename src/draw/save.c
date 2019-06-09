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
#include <tice.h>
#include <fileioc.h>

#include "../draw/save.h"

/* Declare some variables */
const char *appvarName = "MySAVE";

#define VAR1_VALUE 10
#define VAR2_VALUE 20

/* Main Function */
void save(void) {

    ti_var_t myAppVar;
	int map[10][10];

	/* Close any files that may be open already */
    ti_CloseAll();

    /* Open a new variable; deleting it if it already exists */
    myAppVar = ti_Open(appvarName, "w");

    /* Make sure we opened okay */
    if (!myAppVar)                                          goto err;

    /* Write the structure to the appvar */
    if (ti_Write(&map, sizeof(map), 1, myAppVar) != 1)  goto err;

    /* Go back to the start of the file */
    if (ti_Rewind(myAppVar) == EOF)                         goto err;

    /* Let's read it just to make sure we wrote it correctly */
    if (ti_Read(&map, sizeof(map), 1, myAppVar) != 1)   goto err;

    goto noerr;

err:
return;
noerr:

    /* Close all open files */
    ti_CloseAll();

}




void load(void)
{
	int map[10][10];


    ti_var_t myAppVar;

    /* Close any files that may be open already */
    ti_CloseAll();

    /* Open a new variable; deleting it if it already exists */
    myAppVar = ti_Open(appvarName, "w");

    /* Make sure we opened okay */
    if (!myAppVar)                                          goto err;

    /* Let's read it just to make sure we wrote it correctly */
    if (ti_Read(&map, sizeof(map), 1, myAppVar) != 1)   goto err;
    goto noerr;

err:

noerr:

    /* Close all open files */
    ti_CloseAll();



}



