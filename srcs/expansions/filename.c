#include "../../includes/minishell.h"
#include <dirent.h>

static int test_pattern(char *next, char *token)
{
	int		i;

	i = 0;
	while (token[i] != '*')
	{
		if (token[i] != next[i])
			return (0);
		else if (!token[i])
			return (i);
		i++;
	}
	return (i);
}

static int match(char *d_name, char *token)
{
	static int	ret;

	if (*token != '*')
	{
		ret = test_pattern(d_name, token);
		if (!ret)
			return (0);
		token += ret;
		d_name += ret;
	}
	while (*token == '*')
		token++;
	if (!*token)
		return (1);
	d_name = ft_strchr(d_name, *token);
	if (!d_name)
		return (0);
	ret = 0;
	while (d_name && *d_name && !ret)
	{
		ret = ret | match(d_name, token);
		d_name = ft_strchr(d_name + 1, *token);
	}
	return (ret);
}

static int get_size(char *pwd, char *token)
{
	DIR *dir;
	struct dirent *cont;
	int i;

	dir = opendir(pwd);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break;
		if (cont->d_name[0] == '.')
			continue ;
		if (!match(cont->d_name, token))
			continue;
		i++;
	}
	closedir(dir);
	return (i);

}

static void	write_filenames(char ***filenames_ptr, int size, char *token, DIR *dir)
{
	int		i;
	struct dirent *cont;
	char	**filenames;

	i = 0;
	filenames = *filenames_ptr;
	while (i < size)
	{
		cont = readdir(dir);
		if (!cont)
			break;
		if (cont->d_name[0] == '.')
			continue;
		if (match(cont->d_name, token))
		{
			filenames[i] = ft_strdup(cont->d_name);
			if (!filenames[i])
			{
				clean_split(filenames, i);
				filenames_ptr = NULL;
				break;
			}
			i++;
		}
	}
}

 char **filename_expansion(char *pwd, char *token, int *empty)
{
	DIR *dir;
	int	num;
	char **filenames;

	num = get_size(pwd, token);
	if (!num)
	{
		*empty = 1;
		return (NULL);
	}
	filenames = (char **)malloc(sizeof(char *) * (num + 1));
	if (!filenames)
		return (NULL);
	filenames[num] = NULL;
	dir = opendir(pwd);
	write_filenames(&filenames, num, token, dir);
	closedir(dir);
	return (filenames);
}

int main(int argc, char *argv[], char *env[])
{
	char **files;
	int empty;

	empty = 0;
	files = filename_expansion("/Users/", "*s*s*", &empty);
	if (!empty && !files)
		return (malloc_err);
	while (*files)
	{
		printf("%s\n", *files);
		files++;
	}
	return (0);
}
//
//int main(int argc, char *argv[])
//{
//	printf("%s %s %d\n", argv[1], argv[2], match(argv[1], argv[2]));
//}