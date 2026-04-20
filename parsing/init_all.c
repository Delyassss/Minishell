/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:16:54 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 20:57:47 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parser_flags(t_parser *parser)
{
	parser->in_quotes = false;
	parser->empty_after_expand = false;
	parser->no_buffer_needed = false;
	parser->heredocers = NULL;
	parser->dollar = false;
	parser->track_split = 0;
	parser->in_expand = false;
	parser->delimiter = false;
	parser->dont_expand_delimiter = false;
	parser->belong_to_export = false;
	parser->cmd_export = false;
	parser->herdoc_loop = false;
	parser->dont_split = false;
	parser->quotes = false;
	parser->closed_quotes = false;
	parser->c_fd = 0;
	parser->redir_out = false;
	parser->redir_in = false;
	parser->save_k = 0;
	parser->track_ambiguous = 0;
	parser->stdin_backup = dup(STDIN_FILENO);
	parser->stdout_backup = dup(STDOUT_FILENO);
	parser->index = 0;
	parser->shell_pgid = getpid();
}

t_parser	*init_parser(char **env)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (reset(1, 1), NULL);
	parser->gc = gc_init();
	parser->env_gc = env_gc_init();
	parser->env = ft_env(env, parser);
	parser->fds = (int *) d_gc_malloc(parser->gc, sizeof(int) * 100000);
	parser->buffers = (char **)d_gc_malloc(parser->gc, sizeof(char *) * 10000);
	if (!parser->buffers || !parser->fds)
		return (NULL);
	parser->my_strenv = string_env(parser->env, parser->env_gc);
	parser_flags(parser);
	parser->split_later = (char **)
		d_gc_malloc(parser->gc, sizeof(char *) * 10000);
	if (!parser->split_later)
		return (reset(1, 1), NULL);
	ft_memset(parser->split_later, 0, 10000);
	return (parser);
}

t_info	*init_info(t_parser *parser)
{
	t_info	*info;

	info = gc_malloc(parser->gc, sizeof(t_info));
	if (!info)
	{
		reset(1, 1);
		return (NULL);
	}
	info->parser = parser;
	info->dont_open_herdoc = false;
	info->track_process = 0;
	info->process = gc_malloc(parser->gc, sizeof(pid_t) * MAX_PROCESS);
	if (!info->process)
		return (reset(1, 1), NULL);
	info->dup = 0;
	info->nbr_heroc = 0;
	return (info);
}

void	restore_std_fds(t_parser *parser)
{
	if (parser->stdin_backup >= 0)
	{
		if (dup2(parser->stdin_backup, STDIN_FILENO) == -1)
		{
			exit_code(1, 1);
			perror("minishell: restore stdin");
		}
	}
	if (parser->stdout_backup >= 0)
	{
		if (dup2(parser->stdout_backup, STDOUT_FILENO) == -1)
		{
			exit_code(1, 1);
			perror("minishell: restore stdout");
		}
	}
	close(parser->stdin_backup);
	close(parser->stdout_backup);
	parser->stdin_backup = dup(STDIN_FILENO);
	parser->stdout_backup = dup(STDOUT_FILENO);
}
