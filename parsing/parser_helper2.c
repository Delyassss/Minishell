/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:41:05 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 18:39:28 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	helper(t_command *cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->env_args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->there_is_outfile = false;
	cmd->there_is_infile = false;
	cmd->there_is_heredoc = false;
	cmd->heredoc = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	cmd->should_we_expand_herdoc = false;
	cmd->dont_split_cmd = false;
	cmd->quoted_delim = false;
	cmd->i_removed_quotes = false;
	cmd->export_append_case = false;
}

t_command	*init_command(t_garbage *gc)
{
	t_command	*cmd;

	cmd = gc_malloc(gc, sizeof(t_command));
	if (!cmd)
		return (reset(1, 1), NULL);
	cmd->quote_split = (char **) d_gc_malloc(gc, sizeof(char *) * 100000);
	if (!cmd->quote_split)
		return (NULL);
	cmd->heredocers = (char **)d_gc_malloc(gc, sizeof(char *) * 100000);
	if (!cmd->heredocers)
		return (NULL);
	helper(cmd);
	return (cmd);
}

void	splitted(t_command *cmd, t_parser *parser)
{
	for_export(parser, cmd);
	if (cmd->cmd && !ft_strcmp(cmd->cmd, "export") && cmd->args[1])
	{
		valid_ident(cmd->args, cmd);
		if (reset(0, 0))
			return ;
	}
}

void	after_split_helper(t_parser *parser, char **res, char **split)
{
	int		i;
	int		f;
	int		j;
	char	*save;

	i = 0;
	f = 0;
	j = 0;
	while (split && split[i])
	{
		j = ft_strlen(split[i]) - 1;
		if (j >= 0 && split[i][j] == '=' && split[i + 1])
		{
			save = ft_strdup(split[i + 1], parser->gc);
			res[f++] = ft_strjoin(split[i], save, parser->gc);
			i++;
		}
		else
			res[f++] = ft_strdup(split[i], parser->gc);
		i++;
	}
	res[f] = NULL;
}
