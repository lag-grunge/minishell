#include "minishell.h"
#include <dirent.h>

static int get_size(char *pwd)
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
		i++;
	}
	closedir(dir);
	return (i);

}

 char **filename_expansion(char *pwd, int *empty)
{
	DIR *dir;
	struct dirent *cont;
	int	num;
	char **filenames;
	int		i;

	num = get_size(pwd);
	if (!num)
	{
		*empty = 1;
		return (NULL);
	}
	filenames = (char **)malloc(sizeof(char *) * (num + 1));
	if (!filenames)
		return (NULL);
	filenames[num] = NULL;
	i = 0;
	dir = opendir(pwd);
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (i == 0)
			filenames[i] = NULL;
		else
			filenames[i] = ft_strdup(cont->d_name);
		if (!filenames[i])
		{
			clean_split(filenames, i);
			filenames = NULL;
			break ;
		}
		i++;
	}
	closedir(dir);
	return (filenames);
}

int main(int argc, char *argv[], char *env[])
{
	char **files;
	int empty;

	empty = 0;
	files = filename_expansion("./", &empty);
	if (!empty && !files)
		return (malloc_err);
	while (*files)
	{
		printf("%s\n", *files);
		files++;
	}
	return (0);
}