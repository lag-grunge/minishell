#include "../../includes/minishell.h"
#include "parser.h"
#include "expansions.h"

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

static int write_filenames(char **filenames, char *token, DIR *dir)
{
	struct dirent *cont;
	int 	i;
	char 	*tmp;

	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (match(cont->d_name, token))
			write_word(filenames + i++, cont->d_name);
	}
	if (!i)
	{
		tmp = quote_removal(token);
		write_word(filenames, tmp);
		free(tmp);
		i = 1;
	}
	return (i);
}

int count_filename_expansion(char *pwd, char **spl_token)
{
	int	ret;
	int	i;

	i = 0;
	if (!spl_token)
		exit (malloc_err);
	while (*spl_token)
	{
		ret = get_size(pwd, *spl_token);
		if (!ret)
			ret = 1;
		i += ret;
		spl_token++;
	}
	return (i);
}

int filename_expansion(char **filenames, char *pwd, char **spl_token)
{
	DIR *dir;
	int i;

	if (!spl_token)
		exit (malloc_err);
	i = 0;
	while (*spl_token)
	{
		dir = opendir(pwd);
		i += write_filenames(filenames + i, *spl_token, dir);
		closedir(dir);
		spl_token++;
	}
	return (i);
}

//int exec_test(char *token)
//{
//	char **files;
//	int empty;
//
//	empty = 0;
//	files = filename_expansion("../", token, &empty);
//	if (!empty && !files)
//		return (malloc_err);
//	while (files && *files)
//	{
//		printf("%s\n", *files);
//		files++;
//	}
//	return (0);
//}
//

//int main(int argc, char *argv[], char *env[])
//{
//	printf("%s\n", "\'*\'");
//	exec_test("\'*\'");
//	printf("%s\n", "\"*.c\"");
//	exec_test("\"*.c\"");
//	printf("%s\n", "\"*\'.c\"");
//	exec_test("\"*\'.c\"");
//
//	printf("%s\n", "*.c\"*\"");
//	exec_test("*.c\"*\"");
//	printf("%s\n", "\"*\"*.c");
//	exec_test("\"*\"*.c");
//	printf("%s\n", "*\"*\".c");
//	exec_test("*\"*\".c");
//	printf("%s\n", "*.c");
//	exec_test("*.c");
//
//	return (0);
//}
//
