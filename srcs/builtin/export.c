#include "builtin.h"
#include "environment.h"
#include "error.h"
#include "syntax.h"

/* if no args given prints env */
/* if given args */
/*for each argument */
/* valid args alphanumeric starts with letter not num no quest mark */
/* declaration or assignment */

enum e_exp_types {
    err,
    decl,
    asgn
};

static int validation_argument(t_list *args_list, int *type)
{
    char    *s;
    char    *end;

    s = args_list->content;
    end = ft_name(s);
    *type = err;
    if (end == s || (*end != 0 && *end != '='))
        return (not_valid_argument_error("export", s));
    else if (*end == 0)
        *type = decl;
    else
        *type = asgn;
    return (0);
}

static void assign_var(char *argv)
{
    char *key, *val;
    char *assign;

    assign = ft_strchr(argv, '=');
    key = ft_substr(argv, 0, assign - argv);
    val = ft_substr(argv, assign - argv + 1, ft_strlen(argv));
    if (!key || !val)
        exit(malloc_err);
    set_value(&g_data.env, key, val);
    free(key);
}

static void declare_var(char *argv)
{
    char *key, *val;

    key = ft_substr(argv, 0, ft_strlen(argv));
    val = get_value(g_data.env, key);
    if (!val)
        set_value(&g_data.env, key, NULL);
    else
        free(val);
    free(key);
}

int export(t_list *args_list)
{
    int  ret;
    int     type;

    if (!args_list)
    {
        print_env(g_data.env);
        return (0);
    }
    ret = 0;
    type = err;
    while (args_list)
    {
        if (validation_argument(args_list, &type))
            ret = 1;
        else if (type == asgn)
            assign_var(args_list->content);
        else if (type == decl)
            declare_var(args_list->content);
        args_list = args_list->next;
    }
    return (ret);
}
