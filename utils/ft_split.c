/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:44:25 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/19 01:01:18 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*arr;
	unsigned char	*err;

	if (dst == src)
		return (dst);
	if (dst == (void *) 0 && src == (void *) 0)
		return (dst);
	arr = (unsigned char *) dst;
	err = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		arr[i] = err[i];
		i++;
	}
	return (dst);
}

static char	*get_word(const char *s, char *c, t_garbage	*gc)
{
	int		i;
	char	*arr;

	i = 0;
	while (s[i] && !ft_strchr(c, s[i]))
		i++;
	arr = (char *)gc_malloc(gc, sizeof(char) * (i + 1));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s, i);
	arr[i] = '\0';
	return (arr);
}

static int	count_words(const char *str, char *c)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 1;
	while (str[i])
	{
		if (ft_strchr(c, str[i]))
		{
			check = 1;
		}
		else
		{
			if (check == 1)
			{
				count++;
				check = 0;
			}
		}
		i++;
	}
	return (count);
}

char	**ft_split(const char *s, char *c, t_garbage *gc)
{
	char	**arr;
	int		i;
	int		many_word;

	if (s == NULL)
		return (NULL);
	i = 0;
	many_word = count_words(s, c);
	arr = (char **)d_gc_malloc(gc, sizeof(char *) * (many_word + 1));
	if (arr == NULL)
		return (NULL);
	while (*s)
	{
		if (!ft_strchr(c, *s))
		{
			arr[i] = get_word(s, c, gc);
			if (arr[i++] == NULL)
				return (NULL);
			s += ft_strlen(arr[i - 1]);
		}
		else
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
