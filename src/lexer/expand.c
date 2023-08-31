/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 01:44:30 by asabri            #+#    #+#             */
/*   Updated: 2023/08/31 03:37:43 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *check_none_expand(char *str, int *index)
{
    int i;
    char *ptr;
    
    i = *index;
    while (str[i] && str[i] != '$')
		i++;
    ptr = ft_substr(str, *index , i - *index);
    *index = i - 1;
    return (ptr);
}

char *check_expand(char *str,t_env *env, int *i)
{
    int index;
    char *var;
    (void)env;
    index = *i + 1;
    if(str[index] && (str[index] == '_' || ft_isalpha(str[index])))
        index++;
    while(str[index] && (str[index] == '_' || ft_isalnum(str[index])))
        index++;
    var = ft_substr(str, *i + 1, index - *i - 1);
    *i = index - 1;
    while(env)
    {
        if(!ft_strcmp(env->var, var))
            return(ft_strdup(env->val));
        env = env->next;
    }
    return (NULL);
}
char *ft_expand(char *str,t_env *env)
{
    char *ptr;
    char *cmd;
    
    cmd = NULL;
    ptr = NULL;
    int i = -1;
    while(str[++i])
    {
        if (str[i] == '$')
            ptr = check_expand(str,env, &i);
        else
            ptr = check_none_expand(str, &i);
        cmd = ft_strjoin(cmd,ptr);
    }
    return (cmd);
}

// char *ft_expand(char *str,t_env *env) {
//     (void)env;
//     char *output = malloc(strlen(str) * 2);  // Allocate memory for the expanded string
//     if (output == NULL) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }

//     char *out_ptr = output;
//     const char *in_ptr = str;

//     while (*in_ptr != '\0') {
//         if (*in_ptr == '$') {
//             in_ptr++;  // Move past the '$'

//             // Extract the variable name
//             char var_name[50];  // Assuming a maximum variable name length of 49 characters
//             int i = 0;
//             while (*in_ptr != '\0' && i < 50 - 1 && (*in_ptr == '_' || (*in_ptr >= 'a' && *in_ptr <= 'z') || (*in_ptr >= 'A' && *in_ptr <= 'Z'))) {
//                 var_name[i++] = *in_ptr++;
//             }
//             var_name[i] = '\0';

//             // Get the value of the variable
//             char *var_value = getenv(var_name);
//             if (var_value != NULL) {
//                 strcpy(out_ptr, var_value);
//                 out_ptr += strlen(var_value);
//             }
//         } else {
//             *out_ptr++ = *in_ptr++;
//         }
//     }

//     *out_ptr = '\0';  // Null-terminate the output string
//     return output;
// }