#include "libft.h"

/* char **ft_dsplit(char *s, char c1, char c2) 		*/
/* splits with 2 symbols				*/
/* split s with first symbol				*/
/* split with second symbol 				*/
/* only for even parts of first split			*/
/* e.g ("./cmd arg1 arg2 'arg3 arg31' arg4, '\'', ' ') 	*/
/* returns "./cmd" "arg1" "arg2" "arg3 arg31" "arg4"	*/

size_t	count_ds(char **fs, char c2)
{
	size_t	i;
	size_t	count;

	/*returns number of ds split elems */
	i = 0;
	count = 0;
	while (fs[i])
	{
		if (i % 2 == 0)
			count += get_number_words(fs[i], c2);
		else
			count++;
		i++;
	}
	return (count);
}

size_t ft_dsplit_fill(char **ds, size_t j, char *fsi, char c2)
{
	size_t	j_n;

	j_n = j;
	while (*fsi && *(get_next_word_beg(fsi, c2)))
	{
		ds[j_n] = get_next_word(&fsi, c2);
		j_n++;
	}
	return (j_n);
}

char **ft_dsplit(const char *s, char c1, char c2)
{
	char	**fs;
	char	**ds;
	size_t	ds_len;
	size_t	j;
	size_t	i;

	fs = ft_split(s, c1);
	ds_len = count_ds(fs, c2);
	ds = (char **)malloc(sizeof(char *) * (ds_len + 1));
	if (!ds)
		return (NULL);
	ds[ds_len] = NULL;
	i = 0;
	j = 0;
	while (fs[i])
	{
		if (i % 2 == 1)
		{
			ds[j] = ft_strdup(fs[i]);
			j++;
		}
		else
			j = ft_dsplit_fill(ds, j, fs[i], c2);
		i++;
	}
	free(fs);
	return (ds);
}

/*
#include <stdio.h>

static void	print_split(char **split)
{
	printf("%p\n", split);
	while (*split)
	{
		printf("%s\n", *split);
		split++;
	}
}
int main()
{
	char **ds = ft_dsplit("asgei  tseytr 'hthryjh eryety' ystryuruy", '\'', ' ');
	print_split(ds);
	return (0);

}*/
