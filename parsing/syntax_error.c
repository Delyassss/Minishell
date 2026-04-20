/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:18:54 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/02 20:37:22 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_errors(t_token *tokens)
{
	t_token	*prev;
	t_token	*tmp;

	tmp = tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			if (!prev || !tmp->next
				|| tmp->next->type == TOKEN_PIPE)
				return (exit_code(1, 258));
		}
		else if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
			|| tmp->type == TOKEN_REDIR_APPEND
			|| tmp->type == TOKEN_REDIR_HEREDOC)
		{
			if (!tmp->next || (tmp->next->type != TOKEN_STRING
					&& tmp->next->type != TOKEN_ENV_VAR))
				return (exit_code(1, 258));
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	clean_fd(int max_fd, t_parser *parser)
{
	int	i;

	i = 3;
	while (i < max_fd)
	{
		if (i != parser->stdin_backup && i != parser->stdout_backup)
			close(i);
		i++;
	}
}

int	parser_open_file(char *file_name, int file_flag, t_parser *parser)
{
	int	fd;

	fd = -1;
	if (!file_name)
		return (-42);
	if (parser->track_ambiguous && !ft_strcmp(file_name, parser->buffers[0]))
	{
		print_ambiguous(parser);
		return (reset(1, 1), exit_code(1, 1), -1);
	}
	if (file_flag == 0)
		fd = open(file_name, O_RDONLY);
	else if (file_flag == 1)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_flag == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		exit_code(1, 1);
		reset(1, 1);
		ft_putstr_fd("minishell: ", 2);
		perror(file_name);
		clean_fd(MAX_FD, parser);
	}
	return (fd);
}
