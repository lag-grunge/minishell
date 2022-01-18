/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:15:43 by sdalton           #+#    #+#             */
/*   Updated: 2021/11/08 01:05:19 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif
#ifndef READ_SIZE
# define READ_SIZE 64
#endif

static size_t	ft_realloc(char **buf, size_t buf_size)
{
	char	*tmp;

	tmp = *buf;
	*buf = malloc(buf_size * 2);
	if (!*buf)
	{
		free(tmp);
		return (0);
	}
	ft_memcpy(*buf, tmp, buf_size);
	free(tmp);
	return (buf_size * 2);
}

int	read_fd_to_buf(char **buf_ptr, int fd)
{
	char	*buf;
	int 	ret;
	size_t	i;
	size_t	cur_BUFFER_SIZE;

	cur_BUFFER_SIZE = BUFFER_SIZE;
	buf = malloc(cur_BUFFER_SIZE);
	if (!buf)
		return (-1);
	buf[0] = 0;
	i = 0;
	ret = 1;
	while (!ft_strchr(buf,'\n'))
	{
		if (i >= cur_BUFFER_SIZE - READ_SIZE + 1)
			cur_BUFFER_SIZE = ft_realloc(&buf, cur_BUFFER_SIZE);
		ret = read(fd, buf + i, READ_SIZE - 1);
		if (ret <= 0 || !cur_BUFFER_SIZE)
			break ;
		i += ret;
		buf[i] = 0;
	}
	if (ret == -1 || i == 0)
	{
		free(buf);
		if (i == 0)
			return (0);
		return (-1);
	}
	*buf_ptr = buf;
	return (1);
}

int	swap_lines(char **rem, char **buf)
{
	char *tmp;
	char *nl;

	if (*buf && *rem)
	{
		tmp = *buf;
		*buf = ft_strjoin(*rem, tmp);
		free(tmp);
		free(*rem);
	}
	else if (*rem)
		*buf = *rem;
	*rem = NULL;
	if (!*buf)
		return (-1);
	nl = ft_strchr(*buf, '\n');
	if (!nl)
		return (0);
	(*buf)[nl - *buf] = 0;
	if (!nl[1])
		return (0);
	*rem = ft_strdup(nl + 1);
	if (!*rem)
	{
		free(*buf);
		return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*rem;
	int 		ret;

	buf = NULL;
	if (!rem || !ft_strchr(rem, '\n'))
	{
		ret = read_fd_to_buf(&buf, fd);
		if (ret <= 0 && !rem)
			return (ret);
	}
	if (swap_lines(&rem, &buf) == -1)
		return (-1);
	*line = buf;
	return (1);
}
