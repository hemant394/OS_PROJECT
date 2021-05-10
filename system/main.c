/*  main.c  - main */

#include <xinu.h>
#include<ctype.h>
#include<stdlib.h>

void showmenu(void);
void tasksheduler(void);
void calculator(void);
void timer(void);
void filemanagement(void);

/*
struct timpids {
	pid32 prid;
	int32 prtime;
	struct timpids *next;
};

struct timpids *timerpids;
struct timpids *timerlist;

struct timpids *alltimer;
*/

pid32 minar[200];

int32 timertim = -1;

int16 iscalcmin = 0;
int16 istimermin = 0;
int16 istaskmin = 0;

pid32 pidmain;
pid32 pidcalc;
pid32 pidtimer;
pid32 pidtask;

int32 mincount = 0;


bpid32 bufferpoolptr1;
struct bpentry *head1,*tail1;
int count1;

bpid32 bufferpoolptr;
struct bpentry *head,*tail;
int count;

bpid32 bufferpoolptr2;
struct bpentry *head2,*tail2;
int count2;

char  timerbuffer[40];


char  fopbuffer[20];
char  fdatabuffer[20];
int fibuffer;
int flag;
int updateflag;
int fdataindex;

/////////////////////////////////////////////////////////////////
//this function shows all the minimized processes which user can open by following given instructions and also 
//user is having choice not to open it  also

void minapps(void){
        int j;
        j = mincount - 1;
	//showing minimized application
        kprintf("---------------------------MINIMIZED APPLICATIONS -----------------------------------------------\n");
	
	int zz = 0;
        while(zz < mincount){
		if(minar[zz] > 0){
struct procent *ptold;
	    ptold = &proctab[minar[zz]];
	    kprintf("use %d to open %s\n", zz,ptold->prname);
		}
zz++;

	}		
	kprintf("--------------------------------------------------------------------------------------------------------\n");
// here we can open any of the minimized apps and also can choose not to open any of them also
	kprintf("\ninput:\n");
        char  p[10];
        int   cnt=10;
        int i;
        int valid = 1;
        int option = 0;
    	while(valid == 1){
            i = 0;
	    valid = 0;  
            int first = 0;
            while ( i<cnt ){
                if (( p[i++] = getchar()) == '\n' ) {
		    break;
		}
            if(!isdigit(p[i-1])){
	        valid = 1;
		return;
	        break;	
             }
             else{
                 first=first*10+(p[i-1]-'0');
	     }
        }
        if(valid == 1){
		return;
            //kprintf("INVALID INPUT!!!!\n");
        }
        else{ 
            option = first; }
        }
        
	if(option < mincount){
		if(minar[option] > 0){
			struct procent *ptold;
		ptold = &proctab[minar[option]];
		ptold->prstate = PR_READY;
		insert(minar[option], readylist, ptold->prprio); // we have inserted our minimzed application inside ready list
		minar[option] = -1;
		reschedule();// here we will reschedule old process
		}
	
	}
        kprintf("------------------INVALID INPUT-----------\n");
}




process	main(void)
{
	/* Run the Xinu shell */
        recvclr();
	pidmain = currpid;
        resume(create(showmenu, 1024, 20, "showmenu", 0)); ///main menu of our os
        bufferpoolptr1 = mkbufpool(124,7);
        head1=tail1=NULL;
        count1=1;

        bufferpoolptr = mkbufpool(124,4);
        head=tail=NULL;
        count=1;

        bufferpoolptr2 = mkbufpool(244,4);
        head2=tail2=NULL;
        count2=1;

        flag=0;
        updateflag=0;

        //////////////////////linked list for saving process ids of all minimized application
        minimizedpids->next = NULL;
	minimizedpids->prid = -1;
	//minipidlist->prid = -1;
        minipidlist = minimizedpids;
	
        /////////////////////////////// here we will give option to open any of the given application
	while (TRUE) {
		receive();
		sleepms(200);

                kprintf("\nMain input: ");
                char  p[10];
                int   cnt=10;
                int i;
    
                i = 0;
                while ( i<cnt ){
                    if (( p[i++] = getchar()) == '\n' ) {
                        break;
                    }
                }
     
                if(p[0]=='c'){
                    resume(create(calculator, 1024, 20, "calculator", 0));
                }
                else if(p[0]=='t'){
                    resume(create(timer, 1024, 20, "timer", 0));
                }
                else if(p[0]=='s'){
                    resume(create(tasksheduler, 1024, 20, "tasksheduler", 0));
                }
                else if(p[0]=='f'){
                    resume(create(filemanagement, 1024, 20, "filemanagement", 0));
                }
		else if(p[0] == '#'){
		    //minapps
		     resume(create(minapps, 1024, 20, "minapps", 0));
		    //
		}
                else{
                    resume(create(showmenu, 1024, 20, "showmenu", 0));
                }
	}
	return OK;
    
}

void showmenu(void){
            kprintf("\n-------------------------------\n");
	    kprintf("Enter t for timer:\n");
	    kprintf("Enter c for calculator:\n");
            kprintf("Enter s to schedule task of the day:\n");
            kprintf("Enter f to open file management:\n");
	    kprintf("Enter # to see minimized applications:\n");
            kprintf("Enter # Inside any application to minimize that applications:\n");
            kprintf("--------------------------------\n");
}

/////////////////////////////// todo list
void tasksheduler(void){
    
    pidtask = currpid;
    while(1){
	    kprintf("Add Task: ");
	    char  p[80];
	    int   cnt=80;
	    int i;
	    
	    i = 0;
	    while ( i<cnt ){
		 if (( p[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
	    if(p[0] == '#'){// for managing minimization 
		struct procent *ptold;
		ptold = &proctab[pidmain];
		ptold->prstate = PR_READY;
		insert(pidmain, readylist, ptold->prprio);
		istaskmin = 1;
		minar[mincount] = pidtask;
		
		mincount++;	
		reschedule();
            }
	    else if(p[0]=='q' && p[1]=='u' && p[2]=='i' && p[3]=='t'){
                /* print the data from the buffers */
                struct bpentry* temp1 = head1;
                kprintf("\n");
	        while(temp1!=NULL){
	            kprintf("%s\n",temp1->d.s);
                    temp1=temp1->bpnext;
	        }
		break;
	    }
            else{
                /* initialization of linklist */
                if(head1==NULL){
                    struct bpentry* bufferptr;
                    /* get a buffer from the buffer pool */
                    bufferptr = (struct bpentry*) getbuf(bufferpoolptr1);
                    /* fill data in buffer */
                    p[i-1]='\0';
                    strcpy(bufferptr->d.s,p);
                    bufferptr->bpnext = NULL;
                    head1=tail1= bufferptr;
                }
                else{
                     /* free the oldest buffer */
                     if(count1>7){
	                 char *ch = (char *)head1;
		         head1 = head1->bpnext;
		         freebuf(ch);
                     }
                     /* fill the data in new buffer and locate it at the last of linklist */
	             struct bpentry* bufferptr = (struct bpentry*) getbuf(bufferpoolptr1);  
                     p[i-1]='\0';  
                     strcpy(bufferptr->d.s,p);
		     tail1->bpnext = bufferptr;
		     tail1=bufferptr;
		     tail1->bpnext = NULL;
	        }
                count1++;
            }
    }
}

//////////////////calculator process
void calculator(void){

	pidcalc = currpid;
    while(1){
            l1:
	    kprintf("\nfirst input: ");
	    char  a[10];
	    int   cnt=10;
	    int i,k;
	    
	    i = 0;
	    while ( i<cnt ){
		 if (( a[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
	    if(a[0] == '#'){
		struct procent *ptold;
		ptold = &proctab[pidmain];
		ptold->prstate = PR_READY;
		insert(pidmain, readylist, ptold->prprio);
		iscalcmin = 1;
		minar[mincount] = pidcalc;
		
		mincount++;
		reschedule();
		pidcalc = currpid;
            }
            int first = 0;
            for(k=0;k<i-1;k++){
                int temp = a[k]-'0';
                if(temp>=0 && temp<=9){
                    first=first*10+(a[k]-'0');
                }
                else{
                    goto l1;
                }
            }
            
            l2:
            kprintf("\nsecond input: ");
	    char  b[10];
	    
	    i = 0;
	    while ( i<cnt ){
		 if (( b[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
            if(b[0] == '#'){
		struct procent *ptold;
		ptold = &proctab[pidmain];
		ptold->prstate = PR_READY;
		insert(pidmain, readylist, ptold->prprio);
		iscalcmin = 1;
		minar[mincount] = pidcalc;
		mincount++;
		reschedule();
		pidcalc = currpid;
            }
            int second = 0;
            for(k=0;k<i-1;k++){
                int temp = b[k]-'0';
                if(temp>=0 && temp<=9){
                    second=second*10+(b[k]-'0');
                }
                else{
                    goto l2;
                }
                
            }
            
            l3:
            kprintf("\nEnter operation: ");
	    char  c[10];
	    
	    i = 0;
	    while ( i<cnt ){
		 if (( c[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
            if(c[0] == '#'){
		struct procent *ptold;
		ptold = &proctab[pidmain];
		ptold->prstate = PR_READY;
		insert(pidmain, readylist, ptold->prprio);
		iscalcmin = 1;
		minar[mincount] = pidcalc;
		mincount++;
		reschedule();
		
            }
            int res = 0;
            if(c[0]=='+'){
                res=first+second;
            }
            else if(c[0]=='-'){
                res=first-second;
            }
            else if(c[0]=='*'){
                res=first*second;
            }
            else if(c[0]=='/'){
                res=first/second;
            }
            else{
                goto l3;
            }
            
            kprintf("%d %c %d = %d\n",first,c[0],second,res);




                /* initialization of linklist */
                if(head==NULL){
                    struct bpentry* bufferptr;
                    /* get a buffer from the buffer pool */
                    bufferptr = (struct bpentry*) getbuf(bufferpoolptr);
                    /* fill data in buffer */
                    bufferptr->d.first = first;
                    bufferptr->d.second = second;
                    bufferptr->d.third = res;
                    strcpy(bufferptr->d.s,c);
                    bufferptr->bpnext = NULL;
                    head=tail= bufferptr;
                }
                else{
                     /* free the oldest buffer */
                     if(count>4){
	                 char *ch = (char *)head;
		         head = head->bpnext;
		         freebuf(ch);
                     }
                     /* fill the data in new buffer and locate it at the last of linklist */
	             struct bpentry* bufferptr = (struct bpentry*) getbuf(bufferpoolptr);    
                     bufferptr->d.first = first;
		     bufferptr->d.second = second;
		     bufferptr->d.third = res;
                     strcpy(bufferptr->d.s,c);
		     tail->bpnext = bufferptr;
		     tail=bufferptr;
		     tail->bpnext = NULL;
	        }
                count++;

            kprintf("do you want to quit: ");
	    char  p[10];
	    
	    i = 0;
	    while ( i<cnt ){
		 if (( p[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
	    
	    
	    if(p[0]=='y' && p[1]=='e' && p[2]=='s'){
		
                /* print the data from the buffers */
                struct bpentry* temp = head;
	        while(temp!=NULL){
	            kprintf("%d  %c  %d  =  %d\n", temp->d.first, temp->d.s[0], temp->d.second, temp->d.third);
                    temp=temp->bpnext;
	        }
		break;

	    }
    }
}

////////////////////////timer process
void timer(void){
   
	    kprintf("\nEnter Time in minutes:\n");
	    char  p[10];
	    int   cnt=10;
	    int i,k;
	    pidtimer = currpid;
	    i = 0;
	    while ( i<cnt ){
		 if (( p[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
            if(p[0] == '#'){
		struct procent *ptold;
		ptold = &proctab[pidmain];
		ptold->prstate = PR_READY;
		insert(pidmain, readylist, ptold->prprio);
		istimermin = 1;
		minar[mincount] = pidtimer;
		mincount++;
		reschedule();
            }
            int second = 0;
            for(k=0;k<i-1;k++){
                second=second*10+(p[k]-'0');
            }

            kprintf("\nAdd Task: ");
	    int   cnt1=40;
	    
	    i = 0;
	    while ( i<cnt1 ){
		 if (( timerbuffer[i++] = getchar()) == '\n' ) {
		       break;
		 }
	    }
            timerbuffer[i-1]='\0';
	    kprintf("alert after %d minutes for %s\n",second,timerbuffer);

	    timertim = second;
		

}

//////////////////////////file management
void filemanagement(void){

    while(1){
            kprintf("filecmd>: ");
	    char  p[20];
	    int   cnt=20;
	    int i,k;
	    
            if(flag==0){
                i = 0;
	        while ( i<cnt ){
		   if (( p[i++] = getchar()) == '\n' ) {
		       break;
		   }
	        }
            }
            else{
                kprintf("%s",fopbuffer);
                strcpy(p,fopbuffer);
                i=fibuffer;
            }
	    
	    
	    if(i==5 && p[0]=='s' && p[1]=='h' && p[2]=='o' && p[3]=='w'){
                strcpy(fopbuffer,p);
                fopbuffer[i]= '\0';
                fibuffer=i;
                /* print the data from the buffers */
                struct bpentry* temp = head2;
	        while(temp!=NULL){
	            kprintf("%s\t",temp->fd.name);
                    temp=temp->bpnext;
	        }
                kprintf("\n");
	    }
            else if(i==5 && p[0]=='h' && p[1]=='e' && p[2]=='l' && p[3]=='p'){
                strcpy(fopbuffer,p);
                fibuffer=i;
                fopbuffer[i]= '\0';
                kprintf("\n---------------------------------------------\n");
                kprintf("cmd for making a new file <make filename>:\n");
                kprintf("cmd for read a file       <read filename>:\n");
                kprintf("cmd for delete a file     <delete filename>:\n");
                kprintf("cmd for updating a file   <update filename>:\n");
                kprintf("cmd for showing all the files <show>:\n");
                kprintf("cmd for exit <quit>:\n");
                kprintf("---------------------------------------------\n\n");
	    }
            else if(i>5 && p[0]=='r' && p[1]=='e' && p[2]=='a' && p[3]=='d'){
                strcpy(fopbuffer,p);
                fibuffer=i;
                fopbuffer[i]= '\0';
                char  p1[20];
                for(k=5;k<i-1;k++){
                    p1[k-5]=p[k];
                }
                p1[k-5]='\0';
                
                struct bpentry* temp = head2;
	        while(temp!=NULL){
                    if(strcmp(temp->fd.name,p1)==0){
                        kprintf("%s\n",temp->fd.data);
                        break;
                    }
                    temp=temp->bpnext;
	        }
	    }
            else if(i==5 && p[0]=='q' && p[1]=='u' && p[2]=='i' && p[3]=='t'){
                flag=1;
		break;
	    }
            else if(p[0]=='m'){
                 strcpy(fopbuffer,p);
                 fibuffer=i;
                 fopbuffer[i]= '\0';
                 char  p1[20];
                 for(k=5;k<i-1;k++){
                     p1[k-5]=p[k];
                 }
                 p1[k-5]='\0';
                /* initialization of linklist */
                if(head2==NULL){
                    struct bpentry* bufferptr;
                    /* get a buffer from the buffer pool */
                    bufferptr = (struct bpentry*) getbuf(bufferpoolptr2);
                    /* fill data in buffer */
                    strcpy(bufferptr->fd.name,p1);
                    bufferptr->bpnext = NULL;
                    head2=tail2= bufferptr;
                    count2++;
                }
                else{
                     /* free the oldest buffer */
                     if(count2>4){
	                 kprintf("memory full can not create more files\n");
                     }
                     else{
                         /* fill the data in new buffer and locate it at the last of linklist */
	                 struct bpentry* bufferptr = (struct bpentry*) getbuf(bufferpoolptr2);    
                         strcpy(bufferptr->fd.name,p1);
		         tail2->bpnext = bufferptr;
		         tail2=bufferptr;
		         tail2->bpnext = NULL;
                         count2++;
                     }
                     
	        }
            }
            else if(p[0]=='u'){
                 strcpy(fopbuffer,p);
                 fibuffer=i;
                 fopbuffer[i]= '\0';
                 char  p1[20];
                 for(k=7;k<i-1;k++){
                     p1[k-7]=p[k];
                 }
                 p1[k-7]='\0';
                 
                 struct bpentry* temp = head2;
	         while(temp!=NULL){
                     if(strcmp(temp->fd.name,p1)==0){
                         kprintf("%s",temp->fd.data);
                         if(updateflag==1){
                             kprintf("%s",fdatabuffer);
                         }
                         
                         char  p2[20];
			 int   cnt2=20;
			 int i2;
			    
			 i2 = 0;
			 while ( i2<cnt2 ){
		             if (( p2[i2++] = getchar()) == '\n' && (p2[i2-2]==' ' || p2[i2-2]=='$' || p2[i2-2]=='r') ) {
			         break;
		             }
			 }
                         if(p2[i2-2]==' '){
                             updateflag=0;
                             strncat(temp->fd.data,fdatabuffer,fdataindex);
                             strncat(temp->fd.data,p2,i2-2);
                             fdatabuffer[0]='\0';
                             fdataindex=0;
                         }
                         else if(p2[i2-2]=='r'){
                             updateflag=0;
                             fdatabuffer[0]='\0';
                             fdataindex=0;
                         }
                         else{
                             updateflag=1;
                             fdataindex=i2-2;
                             strncat(fdatabuffer,p2,i2-2);
                         }
	                 
                         break;
                     }
                     temp=temp->bpnext;
	        }
            }
            
            else if(p[0]=='d'){
                 strcpy(fopbuffer,p);
                 fibuffer=i;
                 fopbuffer[i]= '\0';
                 char  p1[20];
                 for(k=7;k<i-1;k++){
                     p1[k-7]=p[k];
                 }
                 p1[k-7]='\0';
                 
                 struct bpentry* temp = head2;
                 struct bpentry* prev = head2;
	         while(temp!=NULL){
                     if(strcmp(temp->fd.name,p1)==0){
                         if(tail2==head2){
                             char *ch = (char *)head2;
		             head2 = tail2 = NULL;
		             freebuf(ch);
                         }
                         else if(temp==head2){
                             char *ch = (char *)head2;
		             head2 = head2->bpnext;
		             freebuf(ch);
                         }
                         else if(temp==tail2){
                             char *ch = (char *)tail2;
		             tail2 = prev;
                             tail2->bpnext=NULL;
		             freebuf(ch);
                         }
                         else{
                             char *ch = (char *)temp;
		             prev->bpnext=tail->bpnext;
		             freebuf(ch);
                         }
                         break;
                     }
                     prev=temp;
                     temp=temp->bpnext;
	        }
            }
            flag=0;
    }
}
