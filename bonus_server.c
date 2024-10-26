/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 02:40:19 by taung             #+#    #+#             */
/*   Updated: 2024/10/27 00:47:54 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	character = 0;

	(void)context;
	if (sig == SIGUSR1)
		character |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		if (character == '\0')
			write(1, "\n", 1);
		bit_count = 0;
		character = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
