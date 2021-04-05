/*  main.c  - main */

#include <xinu.h>

//#include "Win.c"
extern void Win(did32 dev );

process	main(void)
{
	/* Run the Xinu shell */

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	//kprintf("\n process number   %d " , currpid);
	
	//resume(create(Win, 1024, 20, "Win",0)); // creating my first process
	

	/* Wait for shell to exit and recreate it */

	while (  TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	
	kprintf(" process number   %d " , currpid);

	return OK;
    
}
