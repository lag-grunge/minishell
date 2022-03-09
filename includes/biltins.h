#ifndef BILTINS_H
# define BILTINS_H
#include "minishell.h"
#include "environment.h"
int	ft_exit (t_list *orgs, t_data *data);
int	ft_env(t_list *orgs, t_data *data);
int	ft_unset(t_list *orgs, t_data *data);
int	ft_export(t_list *orgs, t_data *data);
int	ft_pwd(t_list *orgs, t_data *data);
int	ft_cd(t_list *orgs, t_data *data);
int	ft_echo(t_list *orgs, t_data *data);
int	ft_bilt_start(t_list *orgs, t_data *data);

#endif
