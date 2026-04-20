/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:54:18 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/05 04:11:04 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	char_vs_char(char a, char b)
{
	if (a != b)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching ",
			2);
		ft_putstr_fd(" `", 2);
		write(2, &b, 1);
		ft_putstr_fd("\n", 2);
		exit_code(1, 258);
		reset(1, 1);
		syntax_error(1, 1);
	}
}

char	*jointree(const char *s1, const char *s2, const char *s3, t_garbage *gc)
{
	char	*result;
	int		len1;
	int		len2;
	int		len3;

	len1 = 0;
	len2 = 0;
	len3 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (s3)
		len3 = ft_strlen(s3);
	result = gc_malloc(gc, (len1 + len2 + len3 + 1));
	if (!result)
		return (NULL);
	if (s1)
		ft_strcpy(result, s1);
	if (s2)
		ft_strcpy(result + len1, s2);
	if (s3)
		ft_strcpy(result + len1 + len2, s3);
	result[len1 + len2 + len3] = '\0';
	return (result);
}

char	*insert_char_edges(char c, const char *str, t_parser *parser)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)gc_malloc(parser->gc, sizeof(char) * (len + 3));
	if (!new_str)
		return (NULL);
	new_str[0] = c;
	i = 0;
	while (i < len)
	{
		new_str[i + 1] = str[i];
		i++;
	}
	new_str[i + 1] = c;
	new_str[i + 2] = '\0';
	return (new_str);
}

int	starts_and_ends_with(char c, char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	if (len == 0)
		return (0);
	if (str[0] == c && str[len - 1] == c)
		return (1);
	return (0);
}

char	*remove_edge_chars(char c, char *str, t_parser *parser)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == c && str[len - 1] == c)
	{
		new_str = (char *)gc_malloc(parser->gc, sizeof(char) * (len - 1));
		if (!new_str)
			return (NULL);
		i = 1;
		while (i < len - 1)
		{
			new_str[i - 1] = str[i];
			i++;
		}
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (ft_strdup(str, parser->gc));
}
