#include<stdio.h>
#include <unistd.h>

int main(int ac, char **av, char **env){

    if(ac == 2){

        if (-1 == execve(av[1], NULL, env)){
            
        }
    }
}