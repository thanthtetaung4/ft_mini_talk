/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 02:40:40 by taung             #+#    #+#             */
/*   Updated: 2024/10/17 15:05:58 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_received_bits = 0;

void	handle_ack(int sig)
{
	(void)sig;
	g_received_bits++;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		i++;
	}
}

void	print_ack(int sent_bits)
{
	ft_putstr_fd("Total sent bits:", 1);
	ft_putnbr_fd(sent_bits, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Total received bits:", 1);
	ft_putnbr_fd(g_received_bits, 1);
	ft_putstr_fd("\n", 1);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: <server_pid> <message>\n", 1);
		return (1);
	}
	server_pid = atoi(argv[1]);
	message = argv[2];
	signal(SIGUSR1, handle_ack);
	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	i++;
	usleep(500);
	print_ack(i);
	return (0);
}
