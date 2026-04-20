/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:35:48 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/26 15:55:57 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

char	*ft_substr(char const *s, int start, int len, t_garbage *gc)
{
	int		i;
	int		len_s;
	char	*arr;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup("", gc));
	if (len > len_s - start)
		len = len_s - start;
	arr = (char *) gc_malloc(gc, sizeof(char) * (len + 1));
	i = 0;
	if (arr == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_strdup(const char *s1, t_garbage *gc)
{
	int		len_src;
	char	*copy;
	char	*save;

	if (!s1)
		return (NULL);
	len_src = ft_strlen(s1);
	copy = (char *) gc_malloc(gc, sizeof(char) * (len_src + 1));
	if (copy == NULL)
		return (NULL);
	save = copy;
	while (*s1)
		*copy++ = *s1++;
	*copy = '\0';
	return (save);
}
