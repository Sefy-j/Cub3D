/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_the_parsing_is_here_part_two.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:14:50 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/20 14:41:25 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_map_textures_and_color(int fd)
{
	t_map	*map;
	char	*line;

	map = ft_calloc(sizeof(t_map), 1);
	map->no_texture_path = get_texture(fd, "NO ");
	map->so_texture_path = get_texture(fd, "SO ");
	map->we_texture_path = get_texture(fd, "WE ");
	map->ea_texture_path = get_texture(fd, "EA ");
	line = get_next_line(fd);
	if (!line || ft_strncmp(line, "\n", 1))
		ft_exit(ERRMAP);
	free(line);
	map->f_color = get_color(fd, "F ");
	map->c_color = get_color(fd, "C ");
	line = get_next_line(fd);
	if (!line || ft_strncmp(line, "\n", 1))
		ft_exit(ERRMAP);
	free(line);
	return (map);
}

void	check_close_map(char **map, int i, int j)
{
	if (map[i][j] == '1' || map[i][j] == ' ')
		return ;
	else if (i == 0 || j == 0)
		ft_exit(ERRMAP);
	else if ((j >= (int)ft_strlen(map[i - 1])) || map[i][j + 1] == ' ')
		ft_exit(ERRMAP);
	else if (map[i][j - 1] == ' ')
		ft_exit(ERRMAP);
	else if (!map[i + 1] || j >= (int)ft_strlen(map[i + 1])
		|| map[i + 1][j] == ' ')
		ft_exit(ERRMAP);
	else if (map[i - 1][j] == ' ')
		ft_exit(ERRMAP);
}

void	check_map(char **map)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(SYMBOLS, map[i][j]))
				ft_exit(ERRMAP);
			if (ft_strchr(LOOK, map[i][j]))
				player = 1;
			check_close_map(map, i, j);
		}
	}
	if (!player)
		ft_exit(ERRMAP);
}

t_map	*all_the_parsing_is_here_part_two(char **argv)
{
	int		fd;
	t_map	*map;

	if (check_extension(argv[1]) == -1)
		ft_exit(ERRMAP);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_exit(ERRMAP);
	map = get_map_textures_and_color(fd);
	map->map = get_map(fd);
	check_map(map->map);
	return (map);
}
