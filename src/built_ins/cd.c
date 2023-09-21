/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:33:30 by yelwadou          #+#    #+#             */
/*   Updated: 2023/09/21 05:31:21 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_home_path(t_env **env)
{
    char *str;
    t_env *ptr;

    str = NULL;
    ptr = *env;
    while (ptr)
    {
        if (ft_strcmp(ptr->var, "HOME") == 0)
        {
            str = (char *)malloc(sizeof(ptr->val));
            if (!str)
                return (NULL);
            str = ptr->val;
        }
        ptr = ptr->next;
    }
    return (str);
}

void set_env_var(t_env **env, char *key, char *value)
{
    // Check environment list for existing key

    t_env *head;
    
    head = *env;
    if (head == NULL)
        return ;   
    while (head) 
    {
        if (ft_strcmp((head)->var, key) == 0) 
        {
            // Here, free the old value and replace with new one
            
            (head)->val = NULL;
            (head)->val = ft_strdup_env(value);
            return;
        }
        head = (head)->next;
    }
}

char *get_env_var(t_env **env, char *key)
{
    if (env == NULL) return NULL;
    while (*env)
    {
        if (ft_strcmp((*env)->var, key) == 0) {
            return (*env)->val;
        }
        env = &(*env)->next;
    }
    return NULL;
}
void ft_add_to_val(t_env **env, char *key)
{
    if (env == NULL) return ;
    while (*env) {
        if (ft_strcmp((*env)->var, key) == 0) {
            (*env)->val = ft_strjoin_env((*env)->val, "/..");
            return;
        }
        env = &(*env)->next;
    }
}

void update_pwd(t_env **env, char **argv)
{
    char *old_pwd;
    char *new_pwd;
    char *n_pwd;

    old_pwd = get_env_var(env, "PWD"); 
    if (old_pwd)
        set_env_var(env, "OLDPWD", old_pwd);
    new_pwd = getcwd(NULL, 0);
    if (new_pwd)
        set_env_var(env, "PWD", new_pwd);
    else
    {
        n_pwd = get_env_var(env, "PWD");
        if (ft_strcmp(argv[1], ".") == 0)
            set_env_var(env, "PWD", ft_strjoin_env(n_pwd, "/."));
        else if (ft_strcmp(argv[1], ".."))
            set_env_var(env, "PWD", ft_strjoin_env(n_pwd, "/.."));
        ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", STDOUT_FILENO);
    }
}


void cd_command(char **argv, t_env **env)
{
    char *str;

    if (argv[1] != NULL)
    {
        if (argv[0] && argv[1])
        {
            if (access(argv[1], F_OK))
            {
                ft_putstr_fd("minishell cd: ", STDOUT_FILENO);
                ft_putstr_fd(ft_strdup_env(argv[1]), STDOUT_FILENO);
                ft_putstr_fd(" : no such file or directory: \n", STDOUT_FILENO);
                _status(1);
            }
            else if ((access(argv[1], X_OK) == 0 && access(argv[1], W_OK) == 0 && access(argv[1], R_OK) == 0))
            {
                if (chdir(argv[1]) == 0)
                {
                    update_pwd(env, argv);
                    return ;
                }
            }
            else if (access(argv[1], X_OK) != 0)
            {
                ft_putstr_fd("minishell: cd:", STDOUT_FILENO);
                ft_putstr_fd(argv[1], STDOUT_FILENO);
                ft_putstr_fd(" : Permission denied \n", STDOUT_FILENO);
                _status(1);
                return ;
            }
        }
    }
    else
    {
        str = get_home_path(env);
        if (!str)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
            _status(1);
            return;
        }
        if (!chdir(str)) 
        {
            // Update OLDPWD and PWD
            update_pwd(env,argv);
        }
        else
        {
            printf("minishell: can't change to home directory\n");
            _status(1);  
        }
    }
    return;
}


// int cd_command(char **argv, t_env **env)
// {
//     char *str;

//     if (argv[1] != NULL)
//     {
//         if (argv[0] && argv[1])
//         {
//             printf("1\n");
//             if ((access(argv[1], X_OK) == 0 && access(argv[1], W_OK) == 0 && access(argv[1], R_OK) == 0))
//             {
//                 printf("2\n");
//                 if (chdir(argv[1]) == 0)
//                 {
//                     update_pwd(env);
//                     return 0;
//                 }
//                 else
//                 {
//                     ft_putstr_fd("minishell cd: ", STDOUT_FILENO);
//                     ft_putstr_fd(argv[1], STDOUT_FILENO);
//                     ft_putstr_fd(" : no such file or directory: \n", STDOUT_FILENO);
//                     return 0;
//                 }
//             }
//             else if (((access(argv[1], X_OK) != 0 || access(argv[1], W_OK) != 0 || access(argv[1], R_OK) != 0)))
//             {
//                 ft_putstr_fd("minishell: cd:", STDOUT_FILENO);
//                 ft_putstr_fd(argv[1], STDOUT_FILENO);
//                 ft_putstr_fd(" : Permission denied \n", STDOUT_FILENO);
//                 return 0;
//             }
            
//         }
//     }
//     else
//     {
//         str = get_home_path(env);
//         if (!str)
//         {
//             ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
//             return 0;
//         }
//         if (!chdir(str)) 
//         {
//             // Update OLDPWD and PWD
//             update_pwd(env);
//             return 0;
//         }
//         else {
//             // If getcwd() returns NULL, the directory doesn't exist. 
//             char *cwd = getcwd(NULL, 0);
//             if (!cwd) {
//                 return 1;
//             }
//             // Always free a string returned by getcwd() with argument NULL
//             free(cwd);
//         }
//     }
//     return 0;
// }

// void handle_cd_command(char **argv, t_env **env)
// {
//     int cd_fail_count = 0;
//     int result = cd_command(argv, env);
//     if (result == 1) {
//         if (cd_fail_count == 0) {
//             printf("cd: ..: No such file or directory\n");
//         } else {
//             printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
//         }
//         cd_fail_count++;
//     } else {
//         cd_fail_count = 0;
//     }
// }