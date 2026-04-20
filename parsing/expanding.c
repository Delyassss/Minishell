/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:03:10 by ildaboun          #+#    #+#             */
/*   Updated: 2025/07/01 21:11:11 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**my_envp(char **envp, t_garbage *gc)
{
	int		i;
	int		j;
	char	**my_envp;

	i = 0;
	while (envp[i])
		i++;
	my_envp = (char **) d_gc_malloc(gc, sizeof(char *) * (i + 1));
	if (!my_envp)
		return (NULL);
	j = 0;
	while (j < i)
	{
		my_envp[j] = ft_strdup(envp[j], gc);
		j++;
	}
	my_envp[j] = NULL;
	return (my_envp);
}

char	*get_name_in_envp(char **my_envp, char *var, t_garbage *gc)
{
	int		i;
	char	*the_actual_var;

	i = -1;
	the_actual_var = NULL;
	while (my_envp[++i])
	{
		if (!ft_strncmp(my_envp[i], var, ft_strlen(var)))
		{
			if ((my_envp[i][ft_strlen(var)]) != '=')
				continue ;
			the_actual_var = ft_substr(my_envp[i],
					(ft_strlen(var) + 1), ft_strlen(my_envp[i]), gc);
			return (the_actual_var);
		}
	}
	return (ft_strdup("\0", gc));
}

char	*get_the_expanded_value(char *value, char **envp, t_parser *parser)
{
	int			i;
	char		*var;
	char		*path;
	int			g;

	i = 0;
	g = 0;
	while (value[i] && (ft_alpha(value[i]) || value[i] == '_'))
	{
		i++;
		g++;
	}
	if (value[0] == '?')
		return (parser->dollar_before = false, parser->itoa_done = true
			, ft_itoa(exit_code(0, 0), parser->gc));
	var = ft_substr(value, 0, g, parser->gc);
	if (!var)
		return (NULL);
	path = get_name_in_envp(envp, var, parser->gc);
	if (ft_strcmp(path, "\0"))
		parser->dollar_before = false;
	else if (parser->in_quotes && !ft_strcmp(path, "\0"))
		parser->empty_after_expand = true;
	return (path);
}
