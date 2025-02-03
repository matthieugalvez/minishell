/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:26 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/03 11:22:15 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_child(void)
{
	struct sigaction	sigquit_sigaction;
	struct sigaction	sigint_sigaction;

	ft_bzero(&sigquit_sigaction, sizeof(sigquit_sigaction));
	ft_bzero(&sigint_sigaction, sizeof(sigint_sigaction));
	sigquit_sigaction.sa_handler = SIG_DFL;
	sigint_sigaction.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sigquit_sigaction, NULL);
	sigaction(SIGINT, &sigint_sigaction, NULL);
}

static void	in_child_sig_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_printf("Quit (core dumped)");
	ft_printf("\n");
}

void	signal_handler_inchild(void)
{
	struct sigaction	inchild_sigaction;

	ft_bzero(&inchild_sigaction, sizeof(inchild_sigaction));
	inchild_sigaction.sa_handler = &in_child_sig_handler;
	sigaction(SIGQUIT, &inchild_sigaction, NULL);
	sigaction(SIGINT, &inchild_sigaction, NULL);
}

static void	sig_handler(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
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
