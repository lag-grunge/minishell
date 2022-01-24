#ifndef REDIRECT_H
#define REDIRECT_H
int		print_err(char *filename, char *cmd_name);
int open_for_read(char *filename, char *cmd_name);
int open_for_write(char *filename, int append, char *cmd_name);
void	ft_redirect(int *pdes, int in_out);
int ft_openfiles(t_redir *red, char *cmd_name);

#endif
