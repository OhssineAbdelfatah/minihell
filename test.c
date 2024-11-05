    #include<unistd.h>

    #include<fcntl.h>
    #include<unistd.h>

    int main(){
        int fd = open("anwar.txt",O_CREAT | O_TRUNC | O_RDWR );
        if(fd == -1 )
            puts(" open fails " );
        // path 
        //  flags : O_CREATE | O_APPEND  
        // 0 ugo 0444
            //U : r 4 w 2 x 1 
            //G : r 4 w 2 x 1 
            //O : r 4 w 2 x 1 

        write(fd, "anwar\n", 6);

        // fd to write to
        // buffer void *
        // lenght size_t 

        close(fd);
    }