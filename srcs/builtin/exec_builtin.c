#include "syntax.h"
#include "biltins.h"

int ft_is_bilt(t_list *orgs)
{
    char *vs = orgs->content;
    if (ft_strncmp(vs, "echo\0", 5) == 0)
        return (1);
    else if (ft_strncmp(vs, "cd\0", 3) == 0)
        return (1);
    else if (ft_strncmp(vs, "pwd\0", 4) == 0)
        return (1);
    else if (ft_strncmp(vs, "export\0", 7) == 0)
        return (1);
    else if (ft_strncmp(vs, "unset\0", 6) == 0)
        return (1);
    else if (ft_strncmp(vs, "env\0", 4) == 0)
        return (1);
    else if (ft_strncmp(vs, "exit\0", 5) == 0)
        return (1);
    else
        return (0);
}

int ft_bilt_start(t_list *orgs)
{
    int	ret;
	t_env	*local_env;

	local_env = g_data.env;
    ret = 127;
    if (ft_strncmp(orgs->content, "echo\0", 5) == 0)
        ret = ft_echo(orgs);
    if (ft_strncmp(orgs->content, "cd\0", 3) == 0)
        ret = ft_cd(orgs, local_env);
    if (ft_strncmp(orgs->content, "pwd\0", 4) == 0)
        ret = ft_pwd(orgs, local_env);
    if (ft_strncmp(orgs->content, "export\0", 7) == 0)
        ret = ft_export(orgs, local_env);
    if (ft_strncmp(orgs->content, "unset\0", 6) == 0)
        ret = ft_unset(orgs, local_env);
    if (ft_strncmp(orgs->content, "env\0", 4) == 0)
        ret = ft_env(orgs, local_env);
    if (ft_strncmp(orgs->content, "exit\0", 5) == 0)
	{
		orgs = orgs->next;
        ret = ft_exit(orgs);
	}
    return (ret);
}
