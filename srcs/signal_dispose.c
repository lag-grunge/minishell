#include "minishell.h"
#include "environment.h"

static void	signal_handler(int signum, siginfo_t *info, void *args)
{
	(void) info;
	(void) args;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_data.last_stat = 1;
	}
}

void	switch_echoctl(char on)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (on)
		ts.c_lflag |= ECHOCTL;
	else
		ts.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

static void	main_shell_dispose(void)
{
	struct sigaction	act;

	rl_catch_signals = 0;
	switch_echoctl(0);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_sigaction = signal_handler;
	sigaction(SIGINT, &act, NULL);
	signal(SIGHUP, SIG_DFL);
}

void	signal_dispose(int child)
{
	if (child == main_shell)
		main_shell_dispose();
	else if (child == readln)
	{
		rl_catch_signals = 1;
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
		rl_catch_signals = 1;
		switch_echoctl(1);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGHUP, SIG_DFL);
	}
}
