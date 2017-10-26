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
    int buffer[3000];      /* Character buffer */
    int bufferout[3000];
    char * input;
    char * output;
    int i,j;
    pid_t pid,pid1;
    i=0;
    pid=fork();   
    
    if(pid==0){
     pid1=fork();
        if(pid1!=0){
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
            perror ("open\n");
            return 2;
    }
 
    /* Create output file descriptor */
    output_fd = open(output, O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1){
        printf("Output of Processus %d didn't work\n",i);
        perror("open\n");
        return 3;
    }
 	printf("i=%d\n",i);
 	printf("output_fd=%d\n",output_fd);
    /* Copy process */
    ret_in = read (input_fd, buffer, BUF_SIZE);
    while((ret_in ) > 0){
    		printf("ret_in=%d\n",ret_in);
    		
    		sprintf(bufferout,"%d",buffer);//atoi?
            ret_out = write (output_fd, bufferout, (ssize_t)ret_in);
            
            if(ret_out != ret_in){
                /* Write error */
                perror("write\n");
                return 4;
            }
            ret_in = read(input_fd, buffer, BUF_SIZE);
    }
 
    /* Close file descriptors */
    printf("Closing file\n");
    close (input_fd);
    close (output_fd);
    waitpid(-1, NULL, 0);
    return (EXIT_SUCCESS);
}
