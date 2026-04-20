/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:28:01 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/26 01:15:28 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst == NULL)
		return ;
	last = ft_lstlast(*lst);
	if (last == NULL)
	{
		*lst = new;
	}
	else
		last -> next = new;
}

static void	flaging(t_token *element, t_parser *parser)
{
	if (parser->needs_expansion == true)
		element->need_expans = true;
	else
		element->need_expans = false;
	if (parser->dollar_before)
		element->expanded = true;
	else
		element->expanded = false;
	element->was_quoted = false;
	if (parser->empty_after_expand && parser->in_quotes)
		element->was_quoted = true;
	if (parser->quoted)
		element->deli_quoted = true;
	else
		element->deli_quoted = false;
	if (parser->quoted)
		element->dont_split_quoted = true;
	else
		element->dont_split_quoted = false;
}

t_token	*ft_lstnew(void *value, t_token_type type, t_parser *parser)
{
	t_token	*element;

	element = (t_token *) gc_malloc(parser->gc, sizeof(t_token));
	if (element == NULL)
		return (reset(1, 1), NULL);
	flaging(element, parser);
	element -> value = ft_strdup(value, parser->gc);
	element -> type = type;
	element -> next = NULL;
	parser->dollar_before = false;
	return (element);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}
