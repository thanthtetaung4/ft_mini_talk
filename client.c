/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 02:40:40 by taung             #+#    #+#             */
/*   Updated: 2024/10/27 01:29:00 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
