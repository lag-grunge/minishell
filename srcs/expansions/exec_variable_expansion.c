/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:59:19 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 13:59:48 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static char	*get_params_for_subs(char **end_var_ptr, char *dollar)
{
	char	*tmp;
	char	*start_var;
	char	*value;

	start_var = dollar + 1;
	if (*start_var == '?')
		*end_var_ptr = start_var + 1;
	else if (ft_isdigit(*start_var))
		*end_var_ptr = ft_number(start_var);
	else
		*end_var_ptr = ft_name(start_var);
	if (*end_var_ptr == start_var)
		return (ft_strdup("$"));
	if (*start_var == '?')
		value = ft_itoa(get_last_status());
	else
	{
		tmp = ft_substr(start_var, 0, *end_var_ptr - start_var);
		if (!tmp)
			exit (malloc_err);
		value = get_value(g_data.env, tmp);
		free(tmp);
	}
	return (value);
}

static char	*oper_dollar(char **tokens, char *dollar)
{
	char	*end_var;
	char	*ret;
	char	*value;

	value = get_params_for_subs(&end_var, dollar);
	ret = make_substitution(tokens, dollar, end_var, value);
	free(value);
	return (ret);
}

void	exec_expansion(char **token)
{
	char	*cur;
	int		db;

	db = 0;
	cur = *token;
	while (*cur)
	{
		if (*cur == '$')
			cur = oper_dollar(token, cur);
		else if (*cur == '\"')
		{
			db = !db;
			cur++;
		}
		else if (*cur == '\'' && !db)
			cur += quoting(cur);
		else
			cur++;
	}
}
