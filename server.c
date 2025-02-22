/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sencetin <sencetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:17:50 by sencetin          #+#    #+#             */
/*   Updated: 2025/02/22 13:45:35 by sencetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	my_putnbr(int nbr)
{
	char	ch;

	if (nbr > 9)
		my_putnbr(nbr / 10);
	ch = (nbr % 10) + '0';
	write(1, &ch, 1);
}

static void	ft_signal_handler(int signal)
{
	static char	c = 0;
	static int	bit = 0;

	if (signal == SIGUSR1)
		c = c | 1;
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit = 0;
	}
	else
		c = c << 1;
}

int	main(void)
{
	int	a;

	write(1, "PID: ", 5);
	a = getpid();
	my_putnbr(a);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_signal_handler);
	signal(SIGUSR2, ft_signal_handler);
	while (1)
		pause();
	return (0);
}
