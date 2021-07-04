#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/io.h>
#include <features.h>

#define port 0xff00 //this will vary depending on what ATA port is being used

static inline void outb(unsigned short port, unsigned char value)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (value));

}


// if(!(ioperm(port,1,1))){
// 	fprintf(stderr,"Acess denied"), exit(1);
// }else{
	i=0;
	for(x=0;x=7;x++){
		y = pow(2,i);
		outb(port,y);
		sleep(1);
		i=i+1;
	//}	
}


