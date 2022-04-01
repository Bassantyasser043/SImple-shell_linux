#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <linux/limits.h>
#include <stdbool.h>

//array of pointers that have built in functions
char *command[1000];
char entered[1000];
bool lag;
char enjoy[PATH_MAX];
char path[PATH_MAX];
FILE *termiFile;
int findpos(char string[1000],char found){
   int i=0;
   while(string[i]!='\0')
    {
        if(string[i]==found)
        {
            return i;
        }
        i++;
           }
   return -1;
}
//take input of the commands and store in the history
void split(){
    if( entered[strlen(entered)-1] == '&' )
    {
        entered[strlen(entered)-1]='\0';
        lag = false;
    }
    command[0] = strtok(entered," \n");

    int i = 0;
    while(command[i]!= NULL)
    {
        i++;
        command[i]=strtok(NULL," \n");
    }
    int j=1;
    while(command[j]!=NULL){
        strcat(enjoy,command[j]);
        strcat(enjoy," ");
        j++;
    }
   }
void cdd(char *uu){
    char cwd[PATH_MAX];
        if (chdir(uu)==0) {
            printf("%s\n", getcwd(cwd, sizeof(cwd)));
        }
        else if(strcmp(command[1],"~")==0 ||strlen(command[1])==0 ){
            chdir("/home/bassant");
            printf("%s\n", getcwd(cwd, sizeof(cwd)));
        }
        else{
            perror("No such directory");
        }
}
char* removequ(char *added){
    char *removed= added;
    if(removed[0]=='\"'){
    removed[strlen(added)-1]='\0';
    removed=removed+1;
    }
    return removed;
}

void expo() {
    char *temp = strtok(enjoy, "=");
    char *hi[2];
    int i = 0;
    while (temp != NULL) {
        hi[i++] = temp;
        temp = strtok(NULL, "=");
    }
    hi[1]= removequ(hi[1]);
    hi[1]= strtok(hi[1],"\"");
    setenv(hi[0], hi[1], 1);
}
void echo(){
    char *printed=NULL;
    printed= strtok(enjoy,"\"");
    if(printed[0]!='$')
        printf("%s\n",printed);
    else{
       printed=printed+1;
       printf("%s\n",getenv(printed));
    }

}
void logTermination()
{

    termiFile = fopen("logFile.txt","a");
    fprintf(termiFile, "- Child process was terminated Successfully \n");
    fclose(termiFile);
}

//a signal handler for the terminated child processes
void signal_handler()
{

    int waitingstate;
    pid_t pid;
    pid = wait3 (&waitingstate, WNOHANG, (struct rusage *)NULL );
    logTermination();
    if (pid == 0)
        return;
    else if (pid == -1)
        return;

}
char* eval(){
    char temp[1000];
    strcpy(temp,"");
    int posdoll= findpos(enjoy,'$');
    strcpy(temp,enjoy);
    char taken[1000]="";
    int i=posdoll+1,j=0;
    char *pr= strtok(temp,"\"");
    strcpy(temp,pr);
    while(temp[i]!='\0'&&temp[i]!=' '){
        taken[j]=temp[i];
        j++;
        i++;
    }
    char *great= getenv(taken);
    printf("TEmp=%s\n",great);
    return great;
}

void excution()
{
    pid_t pid = fork();
    //pid=-1 if there is an error not child or main.
    if (pid == -1)
    {
        perror("failure in child forking\n");
    }
        //the child.
    else if (pid == 0)
    {
        //after creating the child the excution of the  command
            int excution = execvp(command[0], command);
            if( excution < 0 )
            {
                perror("-- Failed to execute command -- \n");
                exit(excution);
            }
            exit(excution);
    }
    else //parent
     {
        // f indication for waiting child termination
        int status;
        if(lag)
            waitpid(pid, &status, WUNTRACED);
    }
}
void set_env(){
    cdd(path);
}
void shell(){
    getcwd(path, sizeof(path));
    set_env();
    while(1){
        lag=true;
        printf("entering >>>>>> ");
        strcpy(enjoy,"");
        fgets(entered, 1000, stdin);
        entered[strlen(entered)-1]='\0';
        split();
        if(strcmp(command[0],"cd")==0) {
            char*printed=strtok(enjoy," ");
          //  printf("%s",printed);
            cdd(printed);
        }
        else if(strcmp(command[0],"export")==0) expo();
        else if(strcmp(command[0],"echo")==0) echo();
        else if(strcmp(command[0],"exit")==0)
        {
            fclose(termiFile);
            exit(0);
        }
        else {
            if(findpos(enjoy,'$')!=-1) {
               strcpy(enjoy , eval());
              // printf("kkk %s\n",enjoy);
               command[1]=enjoy;
            }

            //printf("hhhhhhh%s \n",command);
            excution();
        }
    }
}


int main() {
    //reset the log file
    signal (SIGCHLD, signal_handler);
    termiFile = fopen("logFile.txt","w");
    shell();
    return 0;
}
