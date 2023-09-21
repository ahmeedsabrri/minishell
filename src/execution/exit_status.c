/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:20:14 by asabri            #+#    #+#             */
/*   Updated: 2023/09/21 05:17:54 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    sig_handler(int signum)
{
    (void)signum;
    if (waitpid(-1, NULL, WNOHANG) == 0)
        return ;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    _status(1);
}

void _status(int s)
{
    g_global_exit = s;
}

void exit_status(int status)
{
    if (WIFEXITED(status))
        _status(WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
    {
      _status(128 + WTERMSIG(status));
      if (WTERMSIG(status) == SIGQUIT)
        fd_printf(2, "Quit: %d\n", SIGQUIT);
    }
}