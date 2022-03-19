/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cmd.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sdalton <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/03/19 13:37:58 by sdalton		   #+#	#+#			 */
/*   Updated: 2022/03/19 13:37:59 by sdalton		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parser.h"

static int	check_args(char **tokens, char **lim_token)
{
	while (*tokens)
	{
		if (accept(lg, &tokens))
			ft_redir(NULL, &tokens);
		else if (accept(wrd, &tokens))
			continue ;
		else
			break ;
	}
	if (tokens <= lim_token)
		return (-syntax_error(syntax_err, *tokens, "minishell"));
	return (0);
}

int	write_word(t_list **cur, char *token)
{
	if (!*cur)
	{
		*cur = ft_lstnew(token);
		if (!*cur)
			exit(malloc_err);
	}
	else
	{
		if ((*cur)->content)
			free((*cur)->content);
		(*cur)->content = token;
	}
	return (0);
}

static int	ft_init_cmd(t_cmd **cmd, char **tokens, char **lim_token)
{
	int		ret;

	ret = check_args(tokens, lim_token);
	if (ret == -syntax_err)
		return (syntax_err);
	*cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!*cmd)
		exit (malloc_err);
	(*cmd)->args = NULL;
	(*cmd)->redir = NULL;
	return (0);
}

static int	ft_write_cmd(t_list **cmd_args, t_redir **cmd_red, char **tokens)
{
	int		ret;
	t_list	**cur;
	char	*tmp;

	ret = 0;
	cur = cmd_args;
	while (!ret && *tokens)
	{
		if (accept(lg, &tokens))
			ret = ft_redir(cmd_red, &tokens);
		else if (cmd_args && accept(wrd, &tokens))
		{
			tmp = ft_strdup(tokens[-1]);
			if (!tmp)
				exit(malloc_err);
			ret = write_word(cur, tmp);
			cur = &(*cur)->next;
		}
		else if (accept(wrd, &tokens))
			continue ;
		else
			break ;
	}
	return (ret);
}

int	ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	t_cmd	**cmd;
	int		ret;

	if (accept(lb, &tokens))
	{
		if (stmnt)
		{
			(*stmnt)->type = op_sbsh;
			return (ft_parenthesis((t_stmnt **) &(*stmnt)->oper1, \
				&(*stmnt)->redir, tokens));
		}
		return (ft_parenthesis(NULL, NULL, tokens));
	}
	if (!stmnt)
		return (ft_write_cmd(NULL, NULL, tokens));
	(*stmnt)->type = op_smpl;
	cmd = (t_cmd **)&(*stmnt)->oper1;
	ret = ft_init_cmd(cmd, tokens, lim_token);
	if (ret)
		return (ret);
	return (ft_write_cmd(&(*cmd)->args, &(*cmd)->redir, tokens));
}
