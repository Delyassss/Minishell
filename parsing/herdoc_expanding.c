/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expanding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:21:03 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/27 23:49:07 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*herdoc_expansion(char *str, t_parser *parser)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	parser->buffer = gc_malloc(parser->gc, ft_strlen(str) + 5000000);
	if (malloc_fail(parser->buffer))
		return (NULL);
	ft_memset(parser->buffer, 0, ft_strlen(str) + 500000);
	while (str[k] && str[k] != '|'
		&& str[k] != '<' && str[k] != '>')
		fill_word_buffer(&k, str, &j, parser);
	parser->needs_expansion = false;
	parser->dont_expand_delimiter = false;
	return (parser->buffer);
}
