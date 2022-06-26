/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:51:18 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/16 15:31:09 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_strs(char **arr)
{
	int	length;

	length = 0;
	if (!arr)
		return (length);
	while (arr[length])
		length++;
	return (length);
}

char	**ft_free(char **result)
{
	int	i;

	i = -1;
	if (!result)
		return (0);
	while (result[++i])
		free(result[i]);
	free(result);
	return (0);
}

char	**append_str(char **origin, char *append)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (count_strs(origin) + 2));
	i = 0;
	if (origin)
	{
		while (origin && origin[i])
		{
			ret[i] = ft_strdup(origin[i]);
			i++;
		}
		ft_free(origin);
	}
	ret[i] = ft_strdup(append);
	ret[++i] = NULL;
	return (ret);
}
