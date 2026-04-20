/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:09:09 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/17 02:09:44 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	checkthis(const char *str, char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	trimit_a(const char *s1, const char *set, size_t *start)
{
	size_t	i;

	i = 0;
	*start = 0;
	while (s1[i])
	{
		if (checkthis(set, s1[i], ft_strlen(set)) == 0)
		{
			*start = i;
			break ;
		}
		i++;
	}
}

static void	trimit_b(const char *s1, const char *set, size_t *end, size_t len)
{
	*end = 0;
	while (len-- > 0)
	{
		if (checkthis(set, s1[len], ft_strlen(set)) == 0)
		{
			*end = len + 1;
			break ;
		}
	}
}

char	*ft_strtrim(const char *s1, const char *set, t_garbage *gc)
{
	size_t	i;
	size_t	end;
	size_t	start;
	size_t	len;
	char	*fix;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	if (len == 0)
		return (ft_strdup("", gc));
	trimit_a(s1, set, &start);
	trimit_b(s1, set, &end, len);
	len = (end - start);
	fix = (char *) gc_malloc(gc, sizeof(char) * (len + 1));
	if (fix == NULL)
		return (NULL);
	while (i < len)
	{
		fix[i] = s1[start + i];
		i++;
	}
	fix[i] = '\0';
	return (fix);
}
