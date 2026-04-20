/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:30 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/15 22:14:15 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	one_helper(t_parser *parser)
{
	parser->last_cmd = 1;
	parser->token_head = NULL;
	parser->itoa_done = false;
	parser->track_split = 0;
	parser->dollar = false;
	parser->herdoc_loop = false;
	parser->dont_split = false;
	parser->belong_to_export = false;
	parser->cmd_export = false;
	parser->quotes = false;
	parser->closed_quotes = false;
	parser->c_fd = 0;
	parser->redir_out = false;
	parser->redir_in = false;
	parser->save_k = 0;
	parser->track_ambiguous = 0;
	parser->index = 0;
	parser->stop_heredoc = false;
	parser->save_h = 0;
	parser->save_i = 0;
	parser->i_doc = 0;
	parser->i_env = 0;
}

void	init_part_one(t_parser *parser, int *a)
{
	if (*a != 0)
	{
		parser->gc = gc_init();
		parser->fds = (int *) d_gc_malloc(parser->gc, sizeof(int) * 100000);
		parser->buffers = (char **)d_gc_malloc(parser->gc,
				sizeof(char *) * 10000);
		if (!parser->buffers || !parser->fds)
			return ;
		parser->split_later = (char **)
			d_gc_malloc(parser->gc, sizeof(char *) * 10000);
		if (!parser->split_later)
			return ;
		ft_memset(parser->split_later, 0, 10000);
	}
	else
		(*a)++;
	tcgetattr(STDIN_FILENO, &parser->term);
	reset(1, 0);
	setup_signals();
	syntax_error(1, 0);
	one_helper(parser);
}

void	in_syntax(t_parser *parser, char *input)
{
	restore_std_fds(parser);
	reset(1, 0);
	if (!syntax_error(0, 0))
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	free(input);
	clean_fd(MAX_FD, parser);
	syntax_error(1, 0);
	gc_free_all(parser->gc);
	tcsetattr(STDIN_FILENO, 0, &parser->term);
}

void	end_of_while(t_parser *parser)
{
	restore_std_fds(parser);
	clean_fd(MAX_FD, parser);
	reset(1, 0);
	syntax_error(1, 0);
	free(parser->input);
	gc_free_all(parser->gc);
	tcsetattr(STDIN_FILENO, 0, &parser->term);
}

void	execution(t_info *info, t_parser *parser)
{
	parser->command = parse_tokens(parser->token_head, parser);
	if (!parser->command || reset(0, 0))
	{
		end_of_while(parser);
		return ;
	}
	info = init_info(parser);
	if (reset(0, 0))
		return ;
	if (is_built_in(info->parser->command->cmd, parser->command)
		&& must_run_in_parent(info->parser->command->cmd,
			info->parser->last_cmd))
		builtin_exec(info, &parser->env);
	else
		pipex_b(info, &parser->env);
	end_of_while(parser);
}
