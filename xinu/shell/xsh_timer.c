/* xsh_timer.c - xsh_timer */


#include <xinu.h>
#include <ctype.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_timer - clear the display window (assumes xterm / VT100)
 *------------------------------------------------------------------------
 */
shellcmd xsh_timer(int nargs, char *args[])
{

    /* Insure no arguments were passed */

    if (nargs ==  2) {
	int num = 0;
	int i=0;
	for(i=0; args[1][i] != '\0';i++){
	   if( ! isdigit( args[1][i] ) ){
		fprintf(stderr,"Expected integer found string ( %s )\n", args[1]);
		return 1;
	   }
	   num += num * 10 +  (args[1][i] - '0' ) ;
	}
	if( num > 500 ){
		fprintf(stderr," integer value passes maximum limit ( %s )\n", args[1]);
		return 1;
	}
	fprintf(stderr," WORKING FINE \n");
	return 1;
	
    }
    else{
	fprintf(stderr,"use is: %s Integer\n", args[0]);
	return 1;
    }

    printf("\033[0m\033[2J\033[H\n");
    return 0;
}
