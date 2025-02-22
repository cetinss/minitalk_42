/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sencetin <sencetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:47:41 by sencetin          #+#    #+#             */
/*   Updated: 2025/02/22 14:27:52 by sencetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "stdlib.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	ft_send_signal(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit > -1)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	if (argc != 3)
	{
		write(2, "Error: Argument number is incorrect!\n", 38);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 0)
	{
		write(2, "Error: Invalid PID\n", 20);
		return (1);
	}
	i = 0;
	while (argv[2][i])
	{
		if (argv[2][i] >= 0 && argv[2][i] <= 127)
			ft_send_signal(pid, argv[2][i]);
		i++;
	}
	ft_send_signal(pid, '\0');
	return (0);
}
