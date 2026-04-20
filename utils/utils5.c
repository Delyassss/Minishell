/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:14:01 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 20:54:13 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	atoi_helper(long save, long result, long sign, t_info *info)
{
	if (save != (result / 10) && sign == 1)
	{
		info->over_large_nbr = true;
		return (-1);
	}
	if (save != (result / 10) && sign == -1)
	{
		info->over_large_nbr = true;
		return (0);
	}
	info->over_large_nbr = false;
	return (1);
}

int	ft_atoi(const char *str, t_info *info)
{
	long	sign;
	long	result;
	long	save;
	int		f;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		save = result;
		result = result * 10 + (*str - '0');
		f = atoi_helper(save, result, sign, info);
		if (f == 0 || f == -1)
			return (f);
		str++;
	}
	return ((int)(result * sign));
}

void	advanced_p_error(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int	ft_alpha(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;

	ch = (unsigned char *) b;
	while (len--)
	{
		*ch++ = (unsigned char) c;
	}
	return (b);
}
