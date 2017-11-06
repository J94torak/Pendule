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
    int buffer;      /* Character buffer */ //transmormer en int seulement
    char bufferout[100];// Transformer en char[3000]
    char * input;
    char * output;
    int i,j,size_;
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
do{
    ret_in = read (input_fd, &buffer, 4);// BUF_SIZE=4 taille int //Ecrire do while // faire test sur int
    
    //printf("buffer=%d\n",buffer);
	if(buffer==-1){
		strcpy (bufferout," ");
		size_=1;
	}
	else if(buffer==-32768){
		strcpy (bufferout,"\n");
		size_=1;
	}
	else{
		size_=sprintf(bufferout,"%d",buffer);//atoi?
		//printf ("String=%s\n",bufferout);
	}

    
    ret_out = write (output_fd, bufferout, size_);// taille écrire 4     
            /*if(ret_out != ret_in){
                /* Write error 
                perror("write\n");
                return 4;
            }*/
            
    }while((ret_in ) > 0);
 
    /* Close file descriptors */
    printf("Closing file\n");
    close (input_fd);
    close (output_fd);
    waitpid(-1, NULL, 0);
    return (EXIT_SUCCESS);
}
