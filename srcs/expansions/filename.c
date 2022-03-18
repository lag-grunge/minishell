#include "expansions.h"

static int	get_size(char *pwd, char *token)
{
	DIR				*dir;
	struct dirent	*cont;
	int				i;

	dir = opendir(pwd);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (!match(cont->d_name, token))
			continue ;
		i++;
	}
	closedir(dir);
	return (i);
}

static void	write_filenames(t_list *args_list, DIR *dir, int fil_num, char *pattern)
{
	struct dirent	*cont;
	int				i;
	char			*tmp;

	i = 0;
	while (i < fil_num)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (match(cont->d_name, pattern))
		{
            tmp = ft_strdup(cont->d_name);
            if (!tmp)
                exit(malloc_err);
			write_word(&args_list, tmp);
			args_list = args_list->next;
			i++;
		}
	}
	if (!i)
	{
		tmp = quote_removal(args_list->content);
		write_word(&args_list, tmp);
	}
}

void	filename_expansion(t_list *args_list)
{
	DIR		*dir;
	int		fil_num;
	char	pwd[2048];
	char	*pattern;

	getcwd(pwd, 2048);
	if (access(pwd, F_OK))
		return ;
	pattern = ft_strdup(args_list->content);
	fil_num = get_size(pwd, pattern);
	dir = opendir(pwd);
	args_list = ft_lstins_few_empty(args_list, fil_num - 1);
	write_filenames(args_list, dir, fil_num, pattern);
	closedir(dir);
	free(pattern);
}
