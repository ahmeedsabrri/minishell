/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:45 by asabri            #+#    #+#             */
/*   Updated: 2023/09/28 09:35:50 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	listclear_env(t_env **head)
{
	t_env	*tmp;
	t_env	*ptr;

	if (!head)
		return ;
	tmp = *head;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->var);
		free(ptr->val);
		free(ptr);
	}
	*head = NULL;
}

void	setup_environment(t_env **envrm, int *in, int *out, char **env)
{
	*in = dup(0);
	*out = dup(1);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	*envrm = dup_env(env);
}

void	run_minishell(t_env *envrm, int in, int out)
{
	
	char	*line;
	t_token	*token;
	t_tree	*tree;

	while (1) 
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		signal(SIGINT, sig_handler);
		line = readline("minishell-$ ");
		if (!line)
			break ;
		token = ft_lexer(line, envrm);
		tree = parser(token, envrm);
		if (tree && tree->type == PIPE)
			execution(tree, &envrm);
		else if (tree && tree->type == WORD)
			exec_redir_sc(tree, &envrm);
		if (*line)
			add_history(line);
		free(line);
	}
	exit(g_global_exit);
}

int	main(int ac, char **av, char **env)
{
	t_env	*envrm;
	int		in;
	int		out;

	(void)ac;
	(void)av;
	setup_environment(&envrm, &in, &out, env);
	run_minishell(envrm, in, out);
	return (0);
}
