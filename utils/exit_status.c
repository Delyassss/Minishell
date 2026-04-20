/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:08:59 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/17 02:08:59 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	exit_code(int set, int value)
{
	static int	status;

	if (set)
		status = value;
	return (status);
}

int	reset(int set, int value)
{
	static int	reset;

	if (set)
		reset = value;
	return (reset);
}

int	syntax_error(int set, int value)
{
	static int	reset;

	if (set)
		reset = value;
	return (reset);
}
