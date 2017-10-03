#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#define BUF_SIZE 8192


int main(int argc, char* argv[]) {

    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
    char buffer[30];      /* Character buffer */
    char * input;
    char * output;
    int i;
    pid_t pid;
    i=0;
    pid=fork();   
    
    if(pid==0){
     pid=fork();
        if(pid!=0){
            i=2;
         }
    }
    else{i=1;}
    
    
    if(i==0){
    input="/dev/rtf0"; 
    output="angle.txt"; 
    
    }
    else if(i==1){
    input="/dev/rtf1"; 
    output="position.txt"; 
    
    
    }
    else{
    input="/dev/rtf2"; 
    output="commande.txt"; 
    
    }
    
     
    /* Create input file descriptor */
    input_fd = open (input, O_RDONLY);
    if (input_fd == -1) {
            printf("Input of Processus %d didn't work\n",i);
            perror ("open");
            return 2;
    }
 
    /* Create output file descriptor */
    output_fd = open(output, O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1){
        printf("Output of Processus %d didn't work\n",i);
        perror("open");
        return 3;
    }
 
    /* Copy process */
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
            ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
            if(ret_out != ret_in){
                /* Write error */
                perror("write");
                return 4;
            }
    }
 
    /* Close file descriptors */
    close (input_fd);
    close (output_fd);
    waitpid(-1, NULL, 0);
    return (EXIT_SUCCESS);
}
