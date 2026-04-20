/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:51:15 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 01:37:14 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_garbage	*gc_init(void)
{
	t_garbage	*gc;

	gc = malloc(sizeof(t_garbage));
	if (!gc)
		return (reset(1, 1), NULL);
	gc->head = NULL;
	gc->d_head = NULL;
	return (gc);
}

void	*gc_malloc(t_garbage *gc, size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	ptr = malloc(size);
	if (!ptr)
		return (reset(1, 1), NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
		return (reset(1, 1), free(ptr), NULL);
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	**d_gc_malloc(t_garbage *gc, size_t size)
{
	void		**d_ptr;
	t_gc_double	*node;

	d_ptr = malloc(size);
	if (!d_ptr)
		return (reset(1, 1), NULL);
	node = malloc(sizeof(t_gc_double));
	if (!node)
		return (reset(1, 1), free(d_ptr), NULL);
	node->d_ptr = d_ptr;
	node->next = gc->d_head;
	gc->d_head = node;
	return (d_ptr);
}

static void	gc_free_d(t_garbage *gc)
{
	t_gc_double	*tmp;
	t_gc_double	*node;

	if (!gc)
		return ;
	if (gc->d_head)
	{
		node = gc->d_head;
		while (node)
		{
			if (node && node->d_ptr)
				free(node->d_ptr);
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
}

void	gc_free_all(t_garbage *gc)
{
	t_gc_node	*tmp;
	t_gc_node	*node;

	if (!gc)
		return ;
	if (gc->head)
	{
		node = gc->head;
		while (node)
		{
			if (node && node->ptr)
				free(node->ptr);
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
	gc_free_d(gc);
	free(gc);
}
