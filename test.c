#include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h> 
# include <readline/readline.h>

// int main(int ac, char **av,char **env)
// {
//     char *ls[] = {"/bin/ls",NULL}; 
//     char *cat[] = {"/bin/cat",NULL}; 

    
//     return 0;
// }

#include <unistd.h>
int main (int ac, char *av[],char **env)
{   
    char *ls[]={"ls","-la",NULL};
    char *cat[]={"cat","-e", NULL};
    // execve("/bin/ls",argv,env);
    int pidp[2],status;
    int cpid;

    pipe(pidp);

    cpid = fork();
    if (cpid == 0)
    {
        dup2(pidp[1],STDOUT_FILENO);
        execve("/bin/ls",ls,env);
    }
    cpid = fork();
    if (cpid == 0)
    {
        close(pidp[1]);
        dup2(pidp[0],STDIN_FILENO);
        execve("/bin/cat",cat,env);
    }
    close(pidp[1]);
    close(pidp[0]);

    waitpid(-1,&status,0);
    waitpid(-1,&status,0);
    kill(cpid,SIGKILL);
return 0;
} 