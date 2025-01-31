/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:26 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/31 12:38:09 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

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
