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

//echo = 1
//echo -n = 11
//cd = 2
//pwd = 3
//export = 4
//unset = 5
//env = 6
//exit = 7
//Конец командной строки = 0
/*
typedef struct s_bilt_data
{
	int		pipe_fd[2]; // по умолчанию -1
	int		com_num; // начинает с -1
	int		piped;	// начинает с 0
	int		*comands;
	char	**args;
	char	*dupl;
	char	*env[];
}	t_bilt_data;
*/

/*
typedef struct s_env {
	char *key;
	char sep;
	char *value;
	struct s_env *next;
} 			t_env;
 
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_data {
	t_env	*env;
}				t_data;

t_data	g_data;

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*next;

	i = 0;
	next = lst;
	while (next)
	{
		next = next->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*head;

	head = *lst;
	*lst = new;
	new->next = head;
}

int	ft_strncmp (const char *str1, const char *str2, unsigned long long int size)
{
	unsigned long long int	i;
	int		rezult;

	i = 0;
	rezult = 0;
	while ((str1[i] != '\0') && (str2[i] != '\0') && (i != size))
	{
		if (str1[i] != str2[i])
		{
			rezult = (unsigned char)str1[i] - (unsigned char)str2[i];
			break ;
		}
		i++;
	}
	if (((str2[i] == '\0') || (str1[i] == '\0')) && (size != i))
		rezult = ((unsigned char)str1[i] - ((unsigned char)str2[i]));
	return (rezult);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dupl;

	i = 0;
	while (str[i] != '\0')
		i++;
	i++;
	dupl = malloc(sizeof(char) * i);
	if (!dupl)
		return (NULL);
	while (i--)
		dupl[i] = str[i];
	return (dupl);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*rezult;

	if ((s1 == NULL) || (s2 == NULL))
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	rezult = malloc(sizeof(char) * (i + j + 1));
	if (rezult == NULL)
		return (0);
	while (*s1 != '\0')
		*rezult++ = *s1++;
	while (*s2 != '\0')
		*rezult++ = *s2++;
	*rezult++ = '\0';
	return (rezult - i - j - 1);
}

char	*ft_substr(char const *s, unsigned int start, unsigned long long int len)
{
	unsigned long long int	i;
	unsigned long long int	j;
	char	*rezult;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	while ((s[i] != '\0') && (i != start))
		i++;
	while ((s[i + j] != '\0') && (j != len))
		j++;
	rezult = malloc(sizeof(char) * (j + 1));
	if (rezult == NULL)
		return (0);
	s = s + i;
	i = j;
	while (j--)
		*rezult++ = *s++;
	*rezult = '\0';
	return (rezult - i);
}
*/


/*
int	ft_next(t_bilt_data *bdata, int	ret)
{
//	int	ret;
//
//	ret = 0;
	bdata->com_num++; // начинает с -1
	
//	if ((bdata->comands[bdata->com_num] == 1) || (bdata->comands[bdata->com_num] == 11))
//	//	ret = ft_echo(bdata);
//	if (bdata->comands[bdata->com_num] == 2)
//	//	ret = ft_cd(bdata);
//	if (bdata->comands[bdata->com_num] == 3)
//	//	ret = ft_pwd(bdata);
//	if (bdata->comands[bdata->com_num] == 4)
//	//	ret = ft_export(bdata);
//	if (bdata->comands[bdata->com_num] == 5)
//	//	ret = ft_unset(bdata);
//	if (bdata->comands[bdata->com_num] == 6)
//	//	ret = ft_env(bdata);
//	if (bdata->comands[bdata->com_num] == 7)
//	//	ret = ft_exit(bdata);
	 
	return (ret);
}
*/

/*
char *ft_convert(t_bilt_data *bdata, char *arg)
{
	int		i;
	int		j;
	int		size;
	char	*env_arg;
	char	*dupl;

	j = 0;
//	arg++;
	i = 1;
	env_arg = NULL;
	while (arg[i - 1] != '\0')
		i++;
	dupl = ft_strjoin(arg, "=");
	while (bdata->env[j] != NULL)
	{
		if ((ft_strncmp(bdata->env[j], dupl, i) == 0))
		{
			size = ft_strlen(bdata->env[j]) - i;
			env_arg = malloc(sizeof(char) * (size + 1));
			if (env_arg == NULL)
			{
				free (dupl);
				return (NULL);
			}
			size = 0;
			while (bdata->env[j][size + i] != '\0')
			{
				env_arg[size] = bdata->env[j][size + i];
				size++;
			}
			env_arg[size + 1] = '\0';
		}
		j++;
	}
	if (env_arg == NULL)
		env_arg = malloc(sizeof(char) * 1);
	free (dupl);
	return (env_arg);
}
*/

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

	orgs = orgs->next;
	if (orgs == NULL)
		write (1, "exit\n", 5);
	else
	{
		znak = ft_pre_atoi_znak(orgs->content);
		num = ft_pre_atoi(orgs->content, 0, znak);
		write (1, "exit\n", 5);
		if (num == 12345678901234567890U)
		{
			write (1, "minishell: exit: ", 17);
			i = 0;
			vs = (char*) orgs->content;
			while (vs[i] != '\0')
			{
				write (1, &vs[i], 1);
				i++;
			}
			write (1, ": numeric argument required\n", 28);
			return (255);
		}
		else
		{
			ret = num * znak;
			i = (unsigned char) ret;
			return (i);
		}
	}
	return (0);
}

int	ft_env(t_list *orgs) // нужно расширение для попытки внести как аргумент путь!
{
	int	i;
	char	*vs;

	orgs = orgs->next;
	i = 0;
	if (orgs == NULL)
	{
		while (g_data.env != NULL)
		{
			i = 0;
			while (g_data.env->key[i] != '\0')
			{
				write (1, &g_data.env->key[i], 1);
				i++;
			}
			if (g_data.env->value != NULL)
				write (1, "=", 1);
			i = 0;
			if (g_data.env->value != NULL)
			{
				while (g_data.env->value[i] != '\0')
				{
					write (1, &g_data.env->value[i], 1);
					i++;
				}
			}
			write (1, "\n", 1);
			g_data.env = g_data.env->next;
		}
	}
	else
	{
		write (1, "env: ", 5);
		vs = (char*) orgs->content;
		while (vs[i] != '\0')
		{
			write (1, &vs[i], 1);
			i++;
		}
		write (1, ": No such file or directory\n", 28);
	}
	return (0);
}

int	ft_unset(t_list *orgs)
{
	orgs = orgs->next;
	if (orgs != NULL)
		unset_value(&g_data.env, orgs->content);
	return (0);
}

int	ft_export(t_list *orgs) // с пайпом до или после работает только без аргументов учти кейсы формата export A=B=12 ---> export $A ---> echo $B ---> 12
{
//	int	have_pipe; При наличии пайпов экспорт не создает переменные env
	int	i;
	int	j;
	char	*s1;
	char	*s2;
	char	*vs;

//	have_pipe = 0;
	j = 0;
	orgs = orgs->next;
	if (orgs == NULL)
	{
		while (g_data.env != NULL)
		{
			i = 0;
			write (1, "declare -x ", 11);
			while (g_data.env->key[i] != '\0')
			{
				write (1, &g_data.env->key[i], 1);
				i++;
			}
			if (g_data.env->value != NULL)
				write (1, "=\"", 2);
			i = 0;
			if (g_data.env->value != NULL)
			{
				while (g_data.env->value[i] != '\0')
				{
					write (1, &g_data.env->value[i], 1);
					i++;
				}
			}
			write (1, "\"\n", 2);
			g_data.env = g_data.env->next;
		}
	}
	else // if ((have_pipe == 0) && (bdata->piped == 0))
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
		set_value(&g_data.env, s1, s2);
//		free (s1);
//		if (vs[j] != '\0')
//			free (s2);
	}
	return (0);
}

int	ft_pwd(t_list *orgs)
{
	int		i;
	char	pwd[4000];

	orgs = orgs->next;
	i = 0;
	if (getcwd(pwd, 4000) == NULL)
		return (-1);
	while (pwd[i] != '\0')
	{
		write (1, &pwd[i], 1);
		i++;
	}
	write (1, "\n", 1);
	return (0);
}

/*
int	ft_pwd_uppdate(t_bilt_data *bdata)
{
	int	i;
	int	j;
	int	size;
	char	*old_pwd;

	j = 0;
	i = ft_strncmp(bdata->env[j], "PWD=", 4);
	while (i != 0)
	{
		j++;
		i = ft_strncmp(bdata->env[j], "PWD=", 4);
	}
	size = ft_strlen(bdata->env[j]) - 4;
	old_pwd = malloc(sizeof(char) * (size + 1));
	if (old_pwd == NULL)
		return (-1);
	size = 0;
	while (bdata->env[j][size + 4] != '\0')
	{
		old_pwd[size] = bdata->env[j][size + i];
		size++;
	}
	old_pwd[size + 1] = '\0';
	j = 0;
	while (bdata->env[j] != NULL)
	{
		if ((ft_strncmp(bdata->env[j], "OLDPWD=", 7) == 0))
		{
			free (bdata->env[j]);
			bdata->env[j] = NULL;
		}
		j++;
	}
	bdata->env[j] = ft_strjoin("OLDPWD=", old_pwd);
	j = 0;
	while (bdata->env[j] != NULL)
	{
		if ((ft_strncmp(bdata->env[j], "PWD=", 4) == 0))
		{
			free (bdata->env[j]);
		//	bdata->env[j] = NULL;
			bdata->env[j] = getenv("PWD");
		}
		j++;
	}
//	bdata->env[j] = ft_strjoin ("PWD=", bdata->args[bdata->com_num]);
	return (0);
}
*/

int	ft_cd(t_list *orgs)
{
	int		ret;
	int		i;
	char	*str;
	char	*vs;

	orgs = orgs->next;
	write (1, "CD\n", 3);
	if (orgs != NULL)
	{
		ret = chdir(orgs->content);
		if (ret != 0)
		{
			write (1, "minishell: cd: ", 15);
			i = 0;
			vs = (char*) orgs->content;
			while (vs[i] !='\0')
			{
				write (1, &vs[i], 1);
				i++;
			}
			write (1, ": No such file or directory\n", 28);
			return (1); //Код ошибки как в Баш
		}
	//	ft_pwd_uppdate(bdata);
		str = get_value (g_data.env, "PWD");
		set_value(&g_data.env, "OLDPWD", str);
	//	free (str);
		str = getenv("PWD");
		set_value(&g_data.env, "PWD", str);
	//	free (str);
	}
	else
	{
		str = get_value(g_data.env, "HOME");
		ret = chdir(str);
	//	free (str);
	//	bdata->dupl = ft_convert(bdata, "HOME");
	//	ret = chdir(bdata->dupl);
	//	free (bdata->dupl);
	}
	write (1, "A", 1);
	return (ret);
}

int	ft_echo(t_list *orgs)
{
	int	n;
	int	i;
	char *vs;

	n = 0;
	orgs = orgs->next;
	if (orgs != NULL)
	{
		if (ft_strncmp(orgs->content, "-n\0", 3) == 0)
		{
			n = 1;
			orgs = orgs->next;
		}
		while (orgs != NULL)
		{
			i = 0;
			vs = (char*) orgs->content;
			while (vs[i] != '\0')
			{
				write (1, &vs[i], 1);
				i++;
			}
			orgs = orgs->next;
			if (orgs != NULL)
				write (1, " ", 1);
		}
	}
	if (n == 0)
		write (1, "\n", 1);
	return (0);
}


/*
int	main (int argc, char **argv, char *evn[])
{
	t_data	*g_data;
	int		ret;
	t_list	**spis;

	g_data = malloc (sizeof (t_data));
	spis = malloc (sizeof (t_list *) * 2000);
	orgs = ft_lstnew(argv[1]);
	ret = 2;
	while (ret != argc)
	{
		spis[ret] = ft_lstnew(argv[ret]);
		ft_lstadd_front(&orgs, spis[ret]);
		ret++;
	}
//	ret = ft_bilt_start(orgs, g_data);
	ret = ft_bilt_start(g_data);
	return (ret);
}
*/
