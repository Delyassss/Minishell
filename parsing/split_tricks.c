/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tricks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 00:20:20 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/28 02:04:37 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	before_equal(char **strs, t_parser *parser)
{
	int		i;
	int		to;
	char	*equal;
	char	*str;

	i = 0;
	str = *strs;
	if (!str || !*str)
		return (1);
	equal = ft_strchr(str, '=');
	if (equal)
		to = (int)(equal - str);
	else
		to = ft_strlen(str) - 1;
	while (to > 0 && str[to])
	{
		if (ft_strchr(" \t\n\v\f\r", str[to]))
			return (0);
		to--;
	}
	if (starts_and_ends_with('\x01', str))
		*strs = remove_edge_chars('\x01', str, parser);
	return (1);
}

static char	**append_after_split(t_parser *parser, t_command *cmd
	, char *new_elem, char **array)
{
	char	**split;
	char	**res;

	if (ft_strchr(new_elem, '='))
		should_we_split(parser, cmd, new_elem);
	split = cmd->quote_split;
	if (!split)
		return (array);
	res = (char **) d_gc_malloc(parser->gc, sizeof(char *) * 10000);
	after_split_helper(parser, res, split);
	return (res);
}

static char	**helper(char **array, char **split, int index, t_parser *parser)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **) d_gc_malloc(parser->gc, sizeof(char *)
			* (arr_len(array) + arr_len(split)));
	if (!new)
		return (NULL);
	while (i < index)
	{
		new[i] = ft_strdup(array[i], parser->gc);
		i++;
	}
	while (j < arr_len(split))
		new[i++] = ft_strdup(split[j++], parser->gc);
	j = index + 1;
	while (array[j])
		new[i++] = ft_strdup(array[j++], parser->gc);
	new[i] = NULL;
	return (new);
}

static void	removes_nochars(char **split, t_parser *parser)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (starts_and_ends_with('\x01', split[i]))
			split[i] = remove_edge_chars('\x01', split[i], parser);
		i++;
	}
}

char	**goofy(char **array, char *new_elem, t_parser *parser, t_command *cmd)
{
	int		size;
	char	**new;
	char	**split;

	size = arr_len(array);
	split = NULL;
	if (before_equal(&new_elem, parser) && !ft_strcmp("export", cmd->cmd))
		return (array);
	if (new_elem && ft_strchr(new_elem, '='))
		split = append_after_split(parser, cmd, new_elem, array);
	else if (new_elem && *new_elem && !starts_and_ends_with('\x01', new_elem))
		split = ft_split(new_elem, " \t\n\v\f\r", parser->gc);
	else
	{
		new_elem = remove_edge_chars('\x01', new_elem, parser);
		return (array);
	}
	removes_nochars(split, parser);
	if (!split)
		return (array);
	new = helper(array, split, parser->save_i, parser);
	return (new);
}
