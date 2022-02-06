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

static void write_filenames(t_list *args_list, DIR *dir, int fil_num)
{
	struct dirent *cont;
	int 	i;
	char 	*tmp;

	i = 0;
	while (i < fil_num)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (match(cont->d_name, args_list->content))
		{
			write_word(&args_list, cont->d_name);
			args_list = args_list->next;
			i++;
		}
	}
	if (!i)
	{
		tmp = quote_removal(args_list->content);
		write_word(&args_list, tmp);
		free(tmp);
	}
}

void filename_expansion(t_list *args_list, int exp_num)
{
	DIR *dir;
	int	i;
	int fil_num;
	char *pwd;
	t_list	*next;

	i = 0;
	pwd = get_value(g_data.env, "PWD");
	while (i <= exp_num)
	{
		fil_num = get_size(pwd, args_list->content);
		dir = opendir(pwd);
		next = args_list->next;
		ft_lstins_few_empty(args_list, fil_num - 1);
		write_filenames(args_list, dir, fil_num);
		args_list = next;
		closedir(dir);
		i++;
	}
	free(pwd);
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
