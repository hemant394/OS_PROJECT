#include <xinu.h>
#include <stdio.h>

void Win( did32 dev ){
	
	kprintf("-----------------------------CREATED PROCESS Win-----------------------\n\n\n");
	kprintf("                 %d      ",currpid);
	kprintf("              Enter 1 for Calculator\n");
	kprintf("              Enter 2 for File Editor\n");
	kprintf("              Enter 3 for Timer\n");
	kprintf("              Enter 4 for Minimized Applications\n");

	kprintf("-----------------------------End of Screen      -----------------------\n\n\n");
	

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
	char	*args[SHELL_MAXTOK];	/* Argument vector passed to	*/
					/*   builtin commands		*/

	/* Read a command */
	
	while(TRUE){
		len = read(dev, buf, sizeof(buf));
		
		break;

		fprintf(dev, SHELL_PROMPT);
		

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
		/* Exit gracefully on end-of-file */

	
	kprintf("  Exit PROCESS WIN  %c%c%c" ,buf[0],buf[1],buf[2]);
}
