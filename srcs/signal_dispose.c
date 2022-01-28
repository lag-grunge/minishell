#include "minishell.h"

void signal_handler(int signum, siginfo_t *info, void *args)
{
	/* */
	(void) info;
	(void) args;
	(void) signum;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGHUP)
	{
	}
}

void signal_dispose(int child)
{
	struct sigaction act;

	if (!child)
	{
		rl_catch_signals = 0;
		signal(SIGQUIT, SIG_IGN);
		ft_memset(&act, 0, sizeof(act));
		act.sa_sigaction = signal_handler;
		sigaction(SIGINT, &act, NULL);
		ft_memset(&act, 0, sizeof(act));
		act.sa_sigaction = signal_handler;
		sigaction(SIGHUP, &act, NULL);

	}
	else if (child)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
	}

}