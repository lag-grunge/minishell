#ifndef REDIRECT_H
#define REDIRECT_H
int	open_for_read(char *filename);
int	open_for_write(char *filename, int append);
void	ft_redirect(int *pdes, int in_out);
int	ft_openfiles(t_redir *red);

#endif
