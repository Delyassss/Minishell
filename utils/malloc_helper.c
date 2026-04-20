/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:09:15 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/17 02:09:15 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_already_tracked(t_garbage *gc, void *ptr)
{
	t_gc_node	*node;

	if (!gc || !ptr)
		return (0);
	node = gc->head;
	if (ptr)
	{
		while (node)
		{
			if (node->ptr == ptr)
				return (1);
			node = node->next;
		}
	}
	return (0);
}

int	is_d_ptr_tracked(t_garbage *gc, void **d_ptr)
{
	t_gc_double	*node;

	if (!gc || !d_ptr)
		return (0);
	node = gc->d_head;
	while (node)
	{
		if (node->d_ptr == d_ptr)
			return (1);
		node = node->next;
	}
	return (0);
}

int	env_ptracked(t_env_gc *gc, void *ptr)
{
	t_free_env	*node;

	if (!gc || !ptr)
		return (0);
	node = gc->head;
	if (ptr)
	{
		while (node)
		{
			if (node->ptr == ptr)
				return (1);
			node = node->next;
		}
	}
	return (0);
}

int	env_dtracked(t_env_gc *gc, void **d_ptr)
{
	t_d_free_env	*node;

	if (!gc || !d_ptr)
		return (0);
	node = gc->d_head;
	while (node)
	{
		if (node->d_ptr == d_ptr)
			return (1);
		node = node->next;
	}
	return (0);
}
