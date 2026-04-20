/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:25:35 by ildaboun          #+#    #+#             */
/*   Updated: 2025/06/26 15:52:32 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	counter(long *i, int *count)
{
	long	p;

	if (*i < 0)
	{
		(*count)++;
		*i *= -1;
	}
	p = *i;
	while (p > 9)
	{
		(*count)++;
		p /= 10;
	}
	if (p <= 9)
		(*count)++;
}

char	*ft_itoa(int n, t_garbage *gc)
{
	char	*arr;
	long	i;
	int		j;
	int		count;

	count = 0;
	i = (long) n;
	counter(&i, &count);
	arr = (char *) gc_malloc(gc, sizeof(char) * (count + 1));
	if (arr == NULL)
		return (NULL);
	arr[count] = '\0';
	j = 1;
	while (j <= count)
	{
		arr[count - j] = (i % 10) + 48;
		j++;
		i /= 10;
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}

char	*ft_strjoin(const char *s1, const char *s2, t_garbage *gc)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	totale;
	char	*arr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, gc));
	if (!s2)
		return (ft_strdup(s1, gc));
	if (!*s1 && !*s2)
		return (ft_strdup("", gc));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	totale = len_s1 + len_s2;
	arr = (char *) gc_malloc(gc, sizeof(char) * (totale + 1));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s1, len_s1);
	ft_memcpy(arr + len_s1, s2, len_s2 + 1);
	return (arr);
}
