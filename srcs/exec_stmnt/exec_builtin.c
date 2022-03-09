#include "exec_stmnt.h"
#include "syntax.h"
#include "biltins.h"

int ft_is_bilt(t_list *orgs)
{
    if (ft_strncmp(orgs->content, "echo\0", 5) == 0)
        return (1);
    else if (ft_strncmp(orgs->content, "cd\0", 3) == 0)
        return (1);
    else if (ft_strncmp(orgs->content, "pwd\0", 4) == 0)
        return (1);
    else if (ft_strncmp(orgs->content, "export\0", 7) == 0)
        return (1);
    else if (ft_strncmp(orgs->content, "unset\0", 6) == 0)
        return (1);
    else if (ft_strncmp(orgs->content, "env\0", 4) == 0)
        return (1);
    else if (ft_strncmp(orgs->content, "exit\0", 5) == 0)
        return (1);
    else
        return (0);
}

int	ft_bilt_start(t_list *orgs, t_data *data)
{
    int	ret;

    ret = 127;
    if (ft_strncmp(orgs->content, "echo\0", 5) == 0)
        ret = ft_echo(orgs, data);
    if (ft_strncmp(orgs->content, "cd\0", 3) == 0)
        ret = ft_cd(orgs, data);
    if (ft_strncmp(orgs->content, "pwd\0", 4) == 0)
        ret = ft_pwd(orgs, data);
    if (ft_strncmp(orgs->content, "export\0", 7) == 0)
        ret = ft_export(orgs, data);
    if (ft_strncmp(orgs->content, "unset\0", 6) == 0)
        ret = ft_unset(orgs, data);
    if (ft_strncmp(orgs->content, "env\0", 4) == 0)
        ret = ft_env(orgs, data);
    if (ft_strncmp(orgs->content, "exit\0", 5) == 0)
        ret = ft_exit(orgs, data);
    return (ret);
}
