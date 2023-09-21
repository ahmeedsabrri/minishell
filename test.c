// #include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <signal.h> 
// # include <readline/readline.h>

// // int main(int ac, char **av,char **env)
// // {
// //     char *ls[] = {"/bin/ls",NULL}; 
// //     char *cat[] = {"/bin/cat",NULL}; 

    
// //     return 0;
// // }

// #include <unistd.h>
// int main (int ac, char *av[],char **env)
// {   
//     char *ls[]={"ls","-la",NULL};
//     char *cat[]={"cat","-e", NULL};
//     // execve("/bin/ls",argv,env);
//     int pidp[2],status;
//     int cpid;

//     pipe(pidp);

//     cpid = fork();
//     if (cpid == 0)
//     {
//         dup2(pidp[1],STDOUT_FILENO);
//         execve("/bin/ls",ls,env);
//     }
//     cpid = fork();
//     if (cpid == 0)
//     {
//         close(pidp[1]);
//         dup2(pidp[0],STDIN_FILENO);
//         execve("/bin/cat",cat,env);
//     }
//     close(pidp[1]);
//     close(pidp[0]);

//     waitpid(-1,&status,0);
//     waitpid(-1,&status,0);
//     kill(cpid,SIGKILL);
// return 0;
// } 

//////////////////////////////////////////////////

// void vsSEE(t_tree *tree)
// {
//     if(!tree)
//         return ;
//     if(tree->type == PIPE)
//     {
//         t_pipeline *pipe = (t_pipeline *)tree;
//         vsSEE(pipe->left);
//         // printf("l_%d\n",pipe->left->type);
//         printf("|");
//         vsSEE(pipe->right);
        
//     }
//     else if (tree->type == REDIRECTION)
//     {
//          while (((t_redircmd *)tree)->redir_list)
//         {
//             printf("%s\n", ((t_redircmd *)tree)->redir_list->open_file);
//             ((t_redircmd *)tree)->redir_list = ((t_redircmd *)tree)->redir_list->next;
//         }
//     }
//     else if (tree->type == WORD)
//     {
        
//         while (((t_simplecmd *)tree)->simplecmd && tree->type != PIPE)
//         {
//             printf("%s\n", ((t_simplecmd *)tree)->simplecmd->value);
//             ((t_simplecmd *)tree)->simplecmd = ((t_simplecmd *)tree)->simplecmd->next;
//         } 
//     }
    
// }

 // while (token)
        // {
        //     printf("%s\n",token->value);
        //     token = token->next;
        // }


# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>

int main(int argc, char const *argv[])
{
       DIR *dir;

       dir = opendir("/Users/asabri/Desktop/minishell");

       struct dirent *entity;
       entity = readdir(dir);
       if (!entity)
              return (0);
       while(entity)
       {
              if (!start_with(entity->d_name))
                     printf("%s\n",entity->d_name);
              entity = readdir(dir);
       }
       return 0;
}
