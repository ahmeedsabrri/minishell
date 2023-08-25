// lst 
t_token	*ft_lstlst(t_token *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}
t_token	*ft_lstlst_bottom(t_token *lst)
{
	while (lst)
	{
		if (lst->bottom == NULL)
			break ;
		lst = lst->bottom;
	}
	return (lst);
}
void	add_token_back(t_token **lst, t_token *new)
{
	
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->prev = ft_lstlst(*lst);
	ft_lstlst(*lst)->next = new;
	new->next = NULL;
}

t_token *newtoken(t_flgs type,char *tok,int hdoc,int expnd)
{
    t_token *node;

    node = ft_malloc(sizeof(t_token), 1);
    node->token = tok;
    node->type = type;
    node->prev = NULL;
    node->next = NULL;
    node->bottom = NULL;
    node->hd = false;
    node->expand = false;
    if (hdoc)
        node->hd = true;
    if (expnd)
        node->expand = true;
    return (node);
}
// --------------------utils--------------------
char *get_word(char *str, int *index)
{
    int j;
    int i;
    
    i = *index;
    j = i;
    while (str[i] && !ft_strchr("\"\'<>() \t", str[i]))
        i++;
    return (*index = i - 1,ft_substr(str,j,i - j));
}

char *get_qoute(char *str,int *index,char car)
{
    int	i;
	int	j;

	i = *index;
	j = i;
	while (str[i] && str[i] != car)
		i++;
	if (!str[i])
		return (*index = i - 1, ft_substr(str, j, i - j));
	return (*index = i - 1, ft_substr(str, j, i - j));
}
int which_flag(char c ,int flg)
{
    char	*str;
	int		i;

	i = -1;
	str = "\"\'|<>()";
	while (str[++i])
		if (str[i] == c)
			break ;
	if (flg)
        i += 7;
	return (i + 1);
}
void ft_initialize(t_init *init)
{
    init->i = -1;
    init->bottom = 0;
    init->token = 0;
    init->unkown = 0;
    init->cp = 0;
    init->op = 0;
    init->double_quote = false;
    init->singl_quote = false;
    init->space = false;
}
int onlyspace(int i, char *str)
{
    while(str[i] && str[i] == ' ')
        i++;
    if (str[i])
        return (0);
    else 
        return (1);
}
//-----------------------functions that give meanig to the line---------------------------

void lexer_2(t_init *t, char *str)
{
    if(str[t->i] == '\'')
    {
        t->singl_quote = !t->singl_quote;
        if (t->singl_quote == true )
            printf("sq = true\n");
    }
    else if(str[t->i] == '\"')
        t->double_quote = !t->double_quote;
    else if(ft_strchr("<>",str[t->i]) && str[t->i] == str[t->i + 1])
        t->unkown = 1;
    else if (str[t->i] != '\"' || str[t->i] != '\'')
        t->space = true;
    else if (str[t->i] == '(')
        t->op += 1;
    else if (str[t->i] == ')')
        t->cp += 1;
    if (!onlyspace(t->i,str) && str[t->i] != '\'' && str[t->i] != '\"' 
        && str[t->i] != ' ' && str[t->i] != '\t')
        add_token_back(&t->token,newtoken(which_flag(str[t->i],t->unkown),ft_substr(str, t->i,
					t->unkown + 1), 0, 0));
    if (str[t->i] == ' ' || str[t->i] == '\t')
	{
		while ((str[t->i] == ' ' || str[t->i] == '\t') && str[t->i])
			t->i++;
		t->i--;
	}
	t->i += t->unkown;
}
void lexer_3(t_init *in, char *tok)
{
    if (in->space)
    {   
        add_token_back(&in->token,newtoken(WORD, get_word(tok, &in->i),1,1));
        in->space = false;
    }
    else if(!in->space)
    {
        in->bottom = ft_lstlst(ft_lstlst_bottom(in->token));
        in->bottom = newtoken(WORD, get_word(tok, &in->i), 1, 1);
    }
}
void lexer_1(t_init *in, char *tok)
{
    if (in->space)
    {   
        add_token_back(&in->token,newtoken(WORD, get_qoute(tok, &in->i, tok[in->i - 1]),
				(in->double_quote == true), 0));
        in->space = false;
    }
    else if(!in->space)
    {
        in->bottom = ft_lstlst(ft_lstlst_bottom(in->token));
        in->bottom = newtoken(WORD, get_qoute(tok, &in->i, tok[in->i - 1]),
				(in->double_quote == true), 0);
    }
}


// main function that use everthing 
t_token *strtoken(char *line)
{
    t_init init;

    ft_initialize(&init);
    while (line[++(init.i)])
    {
        if ((init.double_quote && line[init.i] =='\"') || (init.singl_quote && line[init.i] == '\''))
            lexer_1(&init,line);
        else if (ft_strchr("\"\'<>()\t", line[init.i]))
            lexer_2(&init,line);
        else if (!ft_strchr("\"\'<>() \t", line[init.i]) && (!init.double_quote|| !init.singl_quote))
            lexer_3(&init,line);
    }
    if ((!init.singl_quote || init.double_quote) || (init.op != init.cp))
		return (ft_putstr_fd("Syntax : Quote Unfound\n", 2), NULL);
	if (init.op != init.cp)
		return (ft_putstr_fd("Syntax : Need a parantes\n", 2), NULL);
	add_token_back(&init.token, newtoken(END, ft_strdup("newline"), 0, 0));
    return (init.token);
}
