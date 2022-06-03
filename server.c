/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:20:21 by rriddler          #+#    #+#             */
/*   Updated: 2021/10/21 21:20:23 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
		write(1, s++, 1);
	write(1, "\0", 1);
}

void	ft_putnbr(int nbr)
{
	if (nbr >= 0 && nbr <= 9)
	{
		nbr = nbr + '0';
		write(1, &nbr, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

void	output_pid(int pid)
{
	ft_putstr("Server PID: ");
	ft_putnbr(pid);
	write(1, "\n", 1);
}

static void	output_data(int signal)
{
	static int	bit;
	static int	out_char;
	static int	bit_count;

	if (bit == 0)
		bit = 128;
	if (signal == SIGUSR1)
	{
		out_char += bit;
		bit /= 2;
		bit_count++;
	}
	if (signal == SIGUSR2)
	{
		bit /= 2;
		bit_count++;
	}
	if (bit_count == 8)
	{
		write(1, &out_char, 1);
		bit = 0;
		out_char = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	output_pid(pid);
	while (1)
	{
		signal(SIGUSR1, output_data);
		signal(SIGUSR2, output_data);
		pause();
	}
	return (0);
}
