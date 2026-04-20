/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:08:15 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/17 02:08:15 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_gc	*env_gc_init(void)
{
	t_env_gc	*gc;

	gc = malloc(sizeof(t_env_gc));
	if (!gc)
		return (reset(1, 1), NULL);
	gc->head = NULL;
	gc->d_head = NULL;
	return (gc);
}

void	*env_malloc(t_env_gc *gc, size_t size)
{
	void		*ptr;
	t_free_env	*node;

	ptr = malloc(size);
	if (!ptr)
		return (reset(1, 1), NULL);
	node = malloc(sizeof(t_free_env));
	if (!node)
		return (reset(1, 1), free(ptr), NULL);
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	**denv_malloc(t_env_gc *gc, size_t size)
{
	void			**d_ptr;
	t_d_free_env	*node;

	d_ptr = malloc(size);
	if (!d_ptr)
		return (reset(1, 1), NULL);
	node = malloc(sizeof(t_d_free_env));
	if (!node)
		return (reset(1, 1), free(d_ptr), NULL);
	node->d_ptr = d_ptr;
	node->next = gc->d_head;
	gc->d_head = node;
	return (d_ptr);
}

void	env_free_d(t_env_gc *gc)
{
	t_d_free_env	*tmp;
	t_d_free_env	*node;

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

void	env_free_all(t_env_gc *gc)
{
	t_free_env	*tmp;
	t_free_env	*node;

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
	env_free_d(gc);
	free(gc);
}
