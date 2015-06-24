#include <stdio.h>
#include <stdlib.h>


int main(int argc,char** argv)
{
	char buf[1024];
	int len=0;
	int i;
    int j=0;
    int times=100;
    if(argc>=2){
        times=atoi(argv[1]);
    }
    for(j=0;j<times;j++){        
		len=rand() % 1024;
		for(i=0;i<len;i++){
            buf[i]=32+rand() % 95;
        }
		buf[len]=0;
        fprintf(stdout,"%s\n",buf);
	}
}
