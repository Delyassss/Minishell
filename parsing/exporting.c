/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:50:00 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/02 03:25:58 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_first_char(char c, char *args)
{
	if (!ft_is_az(c) && c != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		exit_code(1, 1);
		reset(1, 1);
		return (1);
	}
	return (0);
}

static int	check_key_char(char c, char *args)
{
	if (!ft_isalnum(c) && c != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		exit_code(1, 1);
		reset(1, 1);
		return (1);
	}
	return (0);
}

static int	check_append(char **args, int i, t_command *cmd)
{
	int		j;
	int		key_len;
	char	*plus;

	j = 0;
	if (!args || !args[0])
		return (1);
	plus = ft_strnstr(args[i], "+=", ft_strlen(args[i]));
	if (plus)
	{
		cmd->export_append_case = true;
		key_len = (int)(plus - args[i]);
		if (key_len == 0)
			return (check_key_char(args[i][key_len], args[i]));
		if (check_first_char(args[i][0], args[i]))
			return (1);
		while (++j < key_len)
		{
			if (check_key_char(args[i][j], args[i]))
				return (1);
		}
	}
	return (0);
}

static	int	normal_case(char **args, int i)
{
	int	j;

	j = 0;
	check_first_char(args[i][j], args[i]);
	j = 1;
	while (args[i][j] && args[i][j] != '=')
	{
		if (check_key_char(args[i][j], args[i]))
			return (1);
		j++;
	}
	return (0);
}

void	valid_ident(char **args, t_command *cmd)
{
	int	i;

	i = 0;
	if (reset(0, 0))
		return ;
	while (args[i])
	{
		if (ft_strnstr(args[i], "+=", ft_strlen(args[i])))
		{
			check_append(args, i, cmd);
		}
		else
			normal_case(args, i);
		i++;
	}
}
