/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:37:30 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 18:37:32 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

int		print_err(char *filename, char *cmd_name);
int		open_for_read(char *filename, int fd_in);
int		open_for_write(char *filename, int fd_out, int append, int err);
void	ft_redirect(int *pdes, int in_out);
int		ft_openfiles(t_redir *red);
int		read_here_doc(const char *lim, int fd_in, int *h_doc);
void	save_restore_stdin_stdount(void);

#endif
