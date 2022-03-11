/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fphlox <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:49:50 by fphlox            #+#    #+#             */
/*   Updated: 2022/02/25 18:49:52 by fphlox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include "biltins.h"

static unsigned long long int	ft_atoi_numbers(const char *str)
{
	unsigned long long int	rezult;
	int				chek;

	chek = 0;
	rezult = 0;
	if ((*str > 47) && (*str < 58))
	{
		rezult = *str - 48;
		str++;
	}
	while ((*str > 47) && (*str < 58))
	{
		rezult = (rezult * 10 + (*str - 48));
		str++;
		chek++;
	}
	if (chek > 19)
		rezult = 12345678901234567890U;
	return (rezult);
}

static unsigned long long int	ft_ull_atoi(const char *str)
{
	unsigned long long int	rezult;

	while ((*str == 32) || ((*str > 8) && (*str < 14)))
		str++;
	if ((*str == 43) || (*str == 45))
		str++;
	rezult = ft_atoi_numbers(str);
	return (rezult);
}

static unsigned long long int	ft_pre_atoi(char *str, int c, int znak)
{
	unsigned long long int	i;

	i = 0;
	while ((str[i] == 32) || ((str[i] > 8) && (str[i] < 14)))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i] != '\0')
	{
		if (((str[i] >= '0') && (str[i] <= '9')) || (str[i] == 0))
		{
			i++;
			c++;
		}
		else
			return (12345678901234567890U);
	}
	i = ft_ull_atoi(str);
	if (((i > 9223372036854775807U) && (znak != -1)) || (i > 9223372036854775808U) || (c == 0))
		return (12345678901234567890U);
	return (i);
}

static int	ft_pre_atoi_znak(char *str)
{
	unsigned long long int	i;

	i = 0;
	while ((str[i] == 32) || ((str[i] > 8) && (str[i] < 14)))
		i++;
	if (str[i] == '-')
		return (-1);
	else
		return (1);
}

int	ft_exit (t_list *orgs) // exit не работает при наличии пайпов!
{
	unsigned long long int	num;
	int		znak;
	long long int	ret;
	int				i;
	char			*vs;

//	orgs = orgs->next;
	if (orgs == NULL)
	{
		write (2, "exit\n", 5);
		i = get_last_status();
		exit (i);
	}
	znak = ft_pre_atoi_znak(orgs->content);
	num = ft_pre_atoi(orgs->content, 0, znak);
	write (2, "exit\n", 5);
	if (num == 12345678901234567890U)
	{
		write (2, "minishell: exit: ", 17);
		i = 0;
		vs = (char*) orgs->content;
		ft_putstr_fd(vs, 2);
//		while (vs[i] != '\0')
//		{
//			write (2, &vs[i], 1);
//			i++;
//		}
		write (2, ": numeric argument required\n", 28);
		exit (255);
	}
	else if (ft_lstsize(orgs) <= 1)
	{
		ret = num * znak;
		i = (unsigned char) ret;
		exit (i);
	}
	else
	{
		write (2, "minishell: exit: too many arguments\n", 36);
		return (1); // Выхода не просиходит! Баш отрабатывает этот случай как любой другой билтин
	}
}

int	ft_env(t_list *orgs, t_env *local_env) // нужно расширение для попытки внести как аргумент путь!
{
	int	i;
	char	*vs;

	orgs = orgs->next;
	i = 0;
	if (orgs == NULL)
	{
		while (local_env != NULL)
		{
			i = 0;
			ft_putstr_fd(local_env->key, 1);
//			while (local_env->key[i] != '\0')
//			{
//				write (1, &local_env->key[i], 1);
//				i++;
//			}
			if (local_env->value != NULL)
				write (1, "=", 1);
		//	i = 0;
			if (local_env->value != NULL)
				ft_putstr_fd(local_env->value, 1);
//			{
//				while (local_env->value[i] != '\0')
//				{
//					write (1, &local_env->value[i], 1);
//					i++;
//				}
//			}
			write (1, "\n", 1);
			local_env = local_env->next;
		}
	}
	else
	{
		write (2, "env: ", 5);
		vs = (char*) orgs->content;
		ft_putstr_fd(vs, 2);
//		while (vs[i] != '\0')
//		{
//			write (2, &vs[i], 1);
//			i++;
//		}
		write (2, ": No such file or directory\n", 28);
	}
	return (0);
}

int	ft_unset(t_list *orgs, t_env *local_env)
{
	orgs = orgs->next;
	if (orgs != NULL)
		unset_value(&local_env, orgs->content);
	return (0);
}

int	ft_export(t_list *orgs, t_env *local_env) // с пайпом до или после работает только без аргументов учти кейсы формата export A=B=12 ---> export $A ---> echo $B ---> 12
{
//	int	have_pipe; При наличии пайпов экспорт не создает переменные env
	int	i;
	int	j;
	char	*s1;
	char	*s2;
	char	*vs;

	j = 0;
	orgs = orgs->next;
	if (orgs == NULL)
	{
		while (local_env != NULL)
		{
		//	i = 0;
			write (1, "declare -x ", 11);
			ft_putstr_fd(local_env->key, 1);
//			while (local_env->key[i] != '\0')
//			{
//				write (1, &local_env->key[i], 1);
//				i++;
//			}
			if (local_env->value != NULL)
			{
				write (1, "=\"", 2);
				//	i = 0;
				ft_putstr_fd(local_env->value, 1);
//				{
//					while (local_env->value[i] != '\0')
//					{
//						write (1, &local_env->value[i], 1);
//						i++;
//					}
//				}
				write (1, "\"", 1);
			}
			write (1, "\n", 1);
			local_env = local_env->next;
		}
	}
	else
	{
		vs = (char *) orgs->content;
		while ((vs[j] != '=') && (vs[j] != '\0'))
			j++;
		s1 = ft_substr(orgs->content, 0, j);
		i = ft_strlen(orgs->content);
		if (vs[j] != '\0')
			s2 = ft_substr(orgs->content, j + 1, i);
		else
			s2 = NULL;
		set_value(&local_env, s1, s2);
	}
	return (0);
}

int	ft_pwd(t_list *orgs, t_env *local_env)
{
//	int		i;
	char	pwd[4000];
	char	*str;

	orgs = orgs->next;
//	i = 0;
	if (getcwd(pwd, 4000) == NULL)
	{
		str = get_value (local_env, "PWD");
		ft_putstr_fd(str, 1);
//		while (str[i] != '\0')
//		{
//			write (1, &str[i], 1);
//			i++;
//		}
		write (1, "\n", 1);
		return (0);
	}
	ft_putstr_fd(pwd, 1);
//	while (pwd[i] != '\0')
//	{
//		write (1, &pwd[i], 1);
//		i++;
//	}
	write (1, "\n", 1);
	return (0);
}

int	ft_cd(t_list *orgs, t_env *local_env)
{
	int		ret;
//	int		i;
	char	*str;
	char	*vs;
	char	pwd[4000];

	orgs = orgs->next;
	if (orgs != NULL)
	{
		if ((getcwd(pwd, 4000) == NULL) && (ft_strncmp(orgs->content, ".\0", 2) == 0))
		{
			write (2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 108);
			str = get_value (local_env, "PWD");
			set_value(&local_env, "OLDPWD", str);
			vs = ft_strjoin(str, "/.");
			set_value(&local_env, "PWD", vs);
			return (0);
		}
		ret = chdir(orgs->content);
		if (ret != 0)
		{
			if (errno == 20)
			{
				write (2, "minishell: cd: ", 15);
				vs = (char*) orgs->content;
				ft_putstr_fd(vs, 2);
				write (2, ": Not a directory\n", 18);
			}
			else
			{
				write (2, "minishell: cd: ", 15);
				//	i = 0;
				vs = (char*) orgs->content;
				ft_putstr_fd(vs, 2);
//				while (vs[i] !='\0')
//				{
//					write (2, &vs[i], 1);
//					i++;
//				}
				write (2, ": No such file or directory\n", 28);
			}
			return (1); //Код ошибки как в Баш
		}
		str = get_value (local_env, "PWD");
		set_value(&local_env, "OLDPWD", str);
		getcwd(pwd, 4000);
		str = ft_strdup(pwd);
		set_value(&local_env, "PWD", str);
	}
	else
	{
		str = get_value(local_env, "HOME");
		ret = chdir(str);
		str = get_value (local_env, "PWD");
		set_value(&local_env, "OLDPWD", str);
		getcwd(pwd, 4000);
		str = ft_strdup(pwd);
		set_value(&local_env, "PWD", str);
	}
	return (ret);
}

int	ft_echo(t_list *orgs)
{
	int	n;
//	int	i;
	char *vs;

	n = 0;
	orgs = orgs->next;
	if (orgs != NULL)
	{
		while ((orgs != NULL) && (ft_strncmp(orgs->content, "-n\0", 3) == 0))
		{
			n = 1;
			orgs = orgs->next;
		}
		while (orgs != NULL)
		{
		//	i = 0;
			vs = (char*) orgs->content;
			ft_putstr_fd(vs, 1);
//			while (vs[i] != '\0')
//			{
//				write (1, &vs[i], 1);
//				i++;
//			}
			orgs = orgs->next;
			if (orgs != NULL)
				write (1, " ", 1);
		}
	}
	if (n == 0)
		write (1, "\n", 1);
	return (0);
}
