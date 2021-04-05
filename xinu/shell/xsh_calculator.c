/* xsh_calculator.c - xsh_calculator */

#include <xinu.h>
#include <stdio.h>

extern did32 dev1;

/*------------------------------------------------------------------------
 * xsh_calculator - clear the display window (assumes xterm / VT100)
 *------------------------------------------------------------------------
 */
shellcmd xsh_calculator(int nargs, char *args[])
{

char	buf[SHELL_BUFLEN];	/* Input line (large enough for	*/
					/*   one line from a tty device	*/
	int32	len;			/* Length of line read		*/
	char	tokbuf[SHELL_BUFLEN +	/* Buffer to hold a set of	*/
			SHELL_MAXTOK];  /* Contiguous null-terminated	*/
					/* Strings of tokens		*/
	int32	tlen;			/* Current length of all data	*/
					/*   in array tokbuf		*/
	int32	tok[SHELL_MAXTOK];	/* Index of each token in	*/
					/*   array tokbuf		*/
	int32	toktyp[SHELL_MAXTOK];	/* Type of each token in tokbuf	*/
	int32	ntok;			/* Number of tokens on line	*/
	pid32	child;			/* Process ID of spawned child	*/
	bool8	backgnd;		/* Run command in background?	*/
	char	*outname, *inname;	/* Pointers to strings for file	*/
					/*   names that follow > and <	*/
	did32	stdinput, stdoutput;	/* Descriptors for redirected	*/
					/*   input and output		*/
	int32	i;			/* Index into array of tokens	*/
	int32	j;			/* Index into array of commands	*/
	int32	msg;			/* Message from receive() for	*/
					/*   child termination		*/
	int32	tmparg;			/* Address of this var is used	*/
					/*   when first creating child	*/
					/*   process, but is replaced	*/
	char	*src, *cmp;		/* Pointers used during name	*/
					/*   comparison			*/
	bool8	diff;			/* Was difference found during	*/
					/*   comparison			*/
			/*   builtin commands		*/

	/* Read a command */
	
	while(TRUE){
		len = read(dev1 , buf, sizeof(buf));
		fprintf(dev1, buf);

		if(buf[0] == 'q'){
			break;
		}

		fprintf(dev1 , SHELL_PROMPT);
		

		int32 jj = 0;
		//kprintf("%d",  len);
		
		while( jj < len ){
			kprintf("%c",buf[jj] );
			jj++;
		}
		
		
		if (len == EOF) {
			kprintf("  BREAKING PROCESS WIN  " );
			break;
		}

		/* If line contains only NEWLINE, go to next line */
		//len = 0;
		if (len <= 1) {
			//kprintf("  CONTINUE PROCESS WIN  " );
			continue;
		}	
		buf[len] = SH_NEWLINE;	/* terminate line */
			
		
	}


    /* Insure no arguments were passed */

    if (nargs > 1) {
	fprintf(stderr,"use is: %s\n", args[0]);
	return 1;
    }

    printf("\033[0m\033[2J\033[H\n");
    

    return 0;
}
