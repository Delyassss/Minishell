/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:06:49 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 16:48:29 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sigint_handler(int sig)
{
	(void) sig;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit_code(1, 1);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	herdoc_sigint_handler(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	close(0);
	exit_code(1, 1);
	reset(1, 1);
}

void	sig_herdoc(void)
{
	signal(SIGINT, herdoc_sigint_handler);
}

void	signals_in_process(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
