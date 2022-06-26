/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:35:01 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/20 14:38:18 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*load_textures(t_ray *ray)
{
	load_north_tex(ray);
	load_east_tex(ray);
	load_south_tex(ray);
	load_west_tex(ray);
	return (ray);
}

char	*get_texture(int fd, char *p)
{
	char	*line;
	char	*tex_path;
	int		i;

	line = get_next_line(fd);
	if (!line)
		ft_exit(ERRMAP);
	while (line && ft_strncmp(line, "\n", 5) == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line || ft_strncmp(line, p, 3) != 0)
		ft_exit(ERRMAP);
	i = 3;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		ft_exit(ERRMAP);
	tex_path = ft_substr(line, i, ft_strlen(&line[i]) - 1);
	free(line);
	return (tex_path);
}

static int	*get_rgb(char **nbrs)
{
	int	*ret;
	int	i;
	int	j;

	i = -1;
	ret = malloc(sizeof(int) * 3);
	while (nbrs[++i])
	{
		j = -1;
		if (ft_strlen(nbrs[i]) > 3)
			ft_exit(ERRMAP);
		while (nbrs[i][++j])
		{
			if (ft_isdigit(nbrs[i][j]) == 0)
				ft_exit(ERRMAP);
		}
	}
	ret[0] = ft_atoi(nbrs[0]);
	ret[1] = ft_atoi(nbrs[1]);
	ret[2] = ft_atoi(nbrs[2]);
	ft_free(nbrs);
	if (ret[0] > 255 || ret[1] > 255 || ret[2] > 255)
		ft_exit(ERRMAP);
	return (ret);
}

int	*get_color(int fd, char *p)
{
	char	*line;
	char	*s;
	char	**nbrs;
	int		*ret;
	int		i;

	line = skip_empty_lines(fd);
	if (!line || ft_strncmp(line, p, 2) != 0)
		ft_exit(ERRMAP);
	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		ft_exit(ERRMAP);
	s = ft_substr(line, i, ft_strlen(&line[i]) - 1);
	free(line);
	nbrs = ft_split(s, ',');
	free(s);
	if (count_strs(nbrs) != 3)
		ft_exit(ERRMAP);
	ret = get_rgb(nbrs);
	return (ret);
}

char	**get_map(int fd)
{
	char	*line;
	char	**map;
	char	*append;

	line = get_next_line(fd);
	if (!line)
		ft_exit(ERRMAP);
	map = NULL;
	while (line)
	{
		append = ft_substr(line, 0, ft_strlen(line) - 1);
		map = append_str(map, append);
		free(line);
		free(append);
		line = get_next_line(fd);
	}
	return (map);
}
