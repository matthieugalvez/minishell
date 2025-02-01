/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:26 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/01 14:20:27 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_sig_handler(int signal)
{
	(void)signal;
	ft_printf_fd(2, "Quit (core dumped)\n");
}

void	signal_handler_child(void)
{
	struct sigaction	sigquit_sigaction;

	ft_bzero(&sigquit_sigaction, sizeof(sigquit_sigaction));
	sigquit_sigaction.sa_handler = &child_sig_handler;
	sigaction(SIGQUIT, &sigquit_sigaction, NULL);
}

static void	sig_handler(int signal)
{
	(void)signal;
	rl_replace_line("\n", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_init(void)
{
	struct sigaction	sigquit_sigaction;
	struct sigaction	sigint_sigaction;

	ft_bzero(&sigquit_sigaction, sizeof(sigquit_sigaction));
	ft_bzero(&sigint_sigaction, sizeof(sigint_sigaction));
	sigquit_sigaction.sa_handler = SIG_IGN;
	sigint_sigaction.sa_handler = &sig_handler;
	sigaction(SIGQUIT, &sigquit_sigaction, NULL);
	sigaction(SIGINT, &sigint_sigaction, NULL);
}
