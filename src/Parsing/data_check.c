#include "../../include/minishell.h"

int	is_reder(int var)
{
	if (var == HEREDOC || var == TRUNC || var == INPUT || var == APPEND)
		return (1);
	return (0);
}

int	check_reder_tkn(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		if (is_reder(tmp->type) && !tmp->next)
		{
			ft_putstr_fd("\033[1;31m:(\033[0m Minishell: syntax error near " \
				"unexpected token 'newline'\n", 2);
			return (1);
		}
		if (is_reder(tmp->type) && !tmp->next
			&& (is_reder(tmp->next->type) || tmp->next->type == PIPE))
		{
			ft_putstr_fd("\033[1;31m:(\033[0m Minishell: syntax error near" \
				"unexpected token '", 2);
			ft_putstr_fd(tmp->next->str, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_pipe_tkn(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	while (ptr->next != token)
	{
		if (ptr->type == PIPE)
		{
			if (!ptr->next || !ptr->prev)
			{
				ft_putstr_fd("\033[1;31m:(\033[0m Minishell: syntax error" \
					" near unexpected token '|'\n", 2);
				return (1);
			}
			else if (ptr->next && ptr->next->type == PIPE)
			{
				ft_putstr_fd("\033[1;31m:(\033[0m Minishell: syntax error" \
				" near unexpected token '||'\n", 2);
				return (1);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}

int	check_herdoc_tkn(t_token *token)
{
	int		i;
	t_token	*ptr;

	ptr = token;
	i = 0;
	while (ptr->next != token)
	{
		if (ptr->type == HEREDOC)
			i++;
		ptr = ptr->next;
	}
	if (i > 16)
	{
		ft_putstr_fd("\033[1;31m:(\033[0m Minishell: maximum here-document count"
			" exceeded\n", 2);
		return (1);
	}
	return (0);
}

int	check_pipe_red_herdoc(t_data *data)
{
	if (check_herdoc_tkn(data->token))
		return (1);
	if (check_reder_tkn(data->token))
		return (1);
	if (check_pipe_tkn(data->token))
		return (1);
	return (0);
}