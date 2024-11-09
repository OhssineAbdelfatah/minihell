#include<stdio.h>
#include<sys/stat.h>
#include<errno.h>

int main(){

	struct stat fielstat;

	if(stat("file", &fielstat) < 0 )
}
