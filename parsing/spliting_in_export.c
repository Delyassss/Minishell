/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting_in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:14:19 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/28 02:03:08 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	fill_quote_split(t_parser *parser, t_command *cmd,
	char *split_equal, int *track)
{
	int		j;
	char	**res;

	j = 0;
	res = ft_split(split_equal, " \t\n\v\f\r", parser->gc);
	if (!res)
		return ;
	while (res[j])
		cmd->quote_split[(*track)++] = res[j++];
	res[j] = NULL;
	cmd->quote_split[(*track)] = NULL;
}

static void	fill_cmd(t_parser *parser, t_command *cmd)
{
	if (cmd->args && cmd->args[0])
		cmd->cmd = ft_strdup(cmd->args[0], parser->gc);
}

void	for_export(t_parser *parser, t_command *cmd)
{
	int		i;
	int		track;
	char	**new_args;

	track = 0;
	if (!parser->split_later || !parser->split_later[0] || reset(0, 0))
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!parser->split_later[track] || !parser->split_later)
			break ;
		if (!ft_strcmp(parser->split_later[track], cmd->args[i]))
		{
			parser->save_i = i;
			new_args = goofy(cmd->args, cmd->args[i], parser, cmd);
			if (!new_args)
				return ;
			cmd->args = new_args;
			track++;
			continue ;
		}
		i++;
	}
	fill_cmd(parser, cmd);
}
