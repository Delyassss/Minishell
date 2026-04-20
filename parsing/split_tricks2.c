/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tricks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 00:37:01 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/28 01:32:54 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	my_own_quote_check(char **new_elem, t_parser *parser)
{
	int		i;
	int		s_count;
	char	*str;

	i = 0;
	s_count = 0;
	str = *new_elem;
	if (starts_and_ends_with('\x01', str))
	{
		*new_elem = remove_edge_chars('\x01', str, parser);
		return (1);
	}
	while (str[i])
	{
		if (ft_strchr(" \t\n\v\f\r", str[i]))
			s_count++;
		else
			s_count = 0;
		if (s_count > 1)
			return (1);
		i++;
	}
	return (0);
}

char	**equals(t_parser *parser, char *new_elem)
{
	int		i;
	int		h;
	int		start;
	char	**equal;

	i = 0;
	h = 0;
	equal = (char **) d_gc_malloc(parser->gc, sizeof(char *) * 1000000);
	if (!equal)
		return (NULL);
	if (new_elem[0] != '=')
		equal[h++] = ft_strdup("", parser->gc);
	while (new_elem[i])
	{
		if (new_elem[i] == '=')
		{
			start = i;
			while (new_elem[i] == '=')
				i++;
			equal[h++] = ft_substr(new_elem, start, i - start, parser->gc);
			continue ;
		}
		i++;
	}
	return (equal[h] = NULL, equal);
}

char	*join_equal(char **equal, char *split_equal, int i, t_parser *parser)
{
	char	*res;
	int		h;

	h = parser->save_h;
	if (!i && equal[h] && equal[h + 1])
	{
		res = jointree(equal[h], split_equal, equal[h + 1], parser->gc);
		parser->save_h += 2;
	}
	else if (equal[h] && i > 0)
	{
		res = ft_strjoin(split_equal, equal[h], parser->gc);
		(parser->save_h)++;
	}
	else
	{
		res = ft_strdup(split_equal, parser->gc);
	}
	return (res);
}

static void	help_we_split(char *new_elem, int *track,
	t_command *cmd, t_parser *parser)
{
	int		i;
	char	**equal;
	char	**split_equal;

	i = 0;
	parser->save_h = 0;
	equal = equals(parser, new_elem);
	split_equal = ft_split(new_elem, "=", parser->gc);
	if (!split_equal || !equal)
		return ;
	while (split_equal && split_equal[i])
	{
		if (!my_own_quote_check(&split_equal[i], parser))
		{
			split_equal[i] = join_equal(equal, split_equal[i], i, parser);
			fill_quote_split(parser, cmd, split_equal[i], track);
		}
		else
		{
			split_equal[i] = join_equal(equal, split_equal[i], i, parser);
			cmd->quote_split[(*track)++] = ft_strdup
				(split_equal[i], parser->gc);
		}
		i++;
	}
}

void	should_we_split(t_parser *parser, t_command *cmd, char *new_elem)
{
	int		i;
	int		track;
	int		h;

	i = 0;
	track = 0;
	h = 0;
	if (new_elem && ft_strchr(new_elem, '='))
	{
		help_we_split(new_elem, &track, cmd, parser);
		cmd->quote_split[(track)] = NULL;
	}
}
