/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:52:28 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/26 01:55:11 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	malloc_fail(char *src)
{
	if (!src)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		reset(1, 1);
		return (1);
	}
	return (0);
}

int	malloc_double_fail(char **src)
{
	if (!src)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		reset(1, 1);
		return (1);
	}
	return (0);
}
