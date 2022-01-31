#include "minishell.h"

void signal_handler(int signum, siginfo_t *info, void *args)
{
	(void) info;
	(void) args;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void signal_handler_readln(int signum, siginfo_t *info, void *args)
{
	(void) args;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		kill(info->si_pid, SIGHUP);
	}
}

void signal_dispose(int child)
{
	struct sigaction act;

	if (child == new_shell)
	{
		rl_catch_signals = 0;
		signal(SIGQUIT, SIG_IGN);
		ft_memset(&act, 0, sizeof(struct sigaction));
		act.sa_sigaction = signal_handler;
		sigaction(SIGINT, &act, NULL);
		signal(SIGHUP, SIG_DFL);
	}
	else if (child == readln)
	{
		rl_catch_signals = 1;
//		signal(SIGQUIT, SIG_IGN);
//		ft_memset(&act, 0, sizeof(struct sigaction));
//		act.sa_sigaction = signal_handler_readln;
//		act.sa_flags = SA_SIGINFO;
//		sigaction(SIGINT, &act, NULL);
		signal(SIGHUP, SIG_DFL);
	}
	else if (child == parent_fork)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
	}
	else if (child == child_fork)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGHUP, SIG_DFL);
	}
}