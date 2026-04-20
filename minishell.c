/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:38:05 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/15 21:27:21 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_project(t_parser *parser)
{
	close(parser->stdin_backup);
	close(parser->stdout_backup);
	env_free_all(parser->env_gc);
	clean_fd(MAX_FD, parser);
	free(parser->input);
	gc_free_all(parser->gc);
	free(parser);
	exit(2);
}

char	*get_input(t_parser *parser)
{
	char	*input;

	if (!isatty(STDIN_FILENO))
		exit(0);
	input = readline("minishell$ ");
	if (!input || !ft_strcmp(input, "exit"))
	{
		write(1, "exit\n", 5);
		close(parser->stdin_backup);
		close(parser->stdout_backup);
		env_free_all(parser->env_gc);
		clean_fd(MAX_FD, parser);
		rl_clear_history();
		free(input);
		gc_free_all(parser->gc);
		free(parser);
		exit(0);
	}
	if (input && *input)
	{
		add_history(input);
	}
	return (input);
}

void	clear_fd(void)
{
	int	i;

	i = 3;
	while (i < MAX_FD)
	{
		close(i);
		i++;
	}
}

static int	is_there_error(t_parser *parser, char *input)
{
	if (check_syntax_errors(parser->token_head)
		|| syntax_error(0, 0) || reset(0, 0))
	{
		in_syntax(parser, input);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_parser		*parser;
	t_info			*info;
	char			*input;
	int				a;

	(void)argc;
	(void)argv;
	info = NULL;
	parser = init_parser(env);
	if (!parser || reset(0, 0))
		return (0);
	a = 0;
	while (1)
	{
		init_part_one(parser, &a);
		input = get_input(parser);
		parser->input = input;
		tokenizer_loop(input, parser);
		if (is_there_error(parser, input))
			continue ;
		execution(info, parser);
	}
}
