/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:20:34 by rriddler          #+#    #+#             */
/*   Updated: 2021/10/21 21:20:37 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
		write(1, s++, 1);
	write(1, "\0", 1);
}

static void	sending(char *str, int pid)
{
	int		bit;
	int		i;
	char	*tmp;

	tmp = ft_strjoin(str, "\n");
	i = 0;
	while (tmp[i] != '\0')
	{
		bit = 128;
		while (bit != 0)
		{
			usleep(100);
			usleep(1);
			if (bit & tmp[i])
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit /= 2;
		}
		i++;
	}
	free(tmp);
	ft_putstr("Message was sent!\n");
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		sending(argv[2], pid);
	}
	else
		ft_putstr("Error\n");
	return (0);
}
