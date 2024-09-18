#include<stdio.h>
#include <stdlib.h> //for exit ()
#include <unistd.h> //for execve()
#include <string.h>
#define MAX_INPUT_LENGTH 20
int main()
{
    char input[MAX_INPUT_LENGTH];
    while(1)
    {
    printf("SimpleShell$ ");
    fgets(input,MAX_INPUT_LENGTH,stdin);
    if(input[0] == '\n'){
        continue;
        }
        input[strcspn(input,"\n")]='\0'; //put NULL that terminates the string
                                            // strcspn gets two strings 
    if(strcmp(input,"exit")==0 || strcmp(input,"quit")==0){
        printf("exiting shell");break;
        }


        char * arguments[MAX_INPUT_LENGTH];
        char *token=strtok(input," ");
        int count_args=0;

        while(token!=NULL)
        {
            arguments[count_args]=token;
            token=strtok(NULL," ");
            count_args++;
        }
        arguments[count_args]=NULL;


    pid_t child_pid=fork();
    if(child_pid<0){perror("fork failed");exit(EXIT_FAILURE);}
    else if(child_pid==0)
        {
            execvp(arguments[0],arguments);
            perror("wrong command");
            exit(EXIT_FAILURE);

        }
        else{
            int status;
            waitpid(child_pid,&status,0);
            printf("status is %d",status);
        }

    }

return 0;
}
