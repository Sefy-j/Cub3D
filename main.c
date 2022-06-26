/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:40:58 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/13 17:01:57 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (1);
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

void	print_map(t_map *map)
{
	printf("%s\n", map->no_texture_path);
	printf("%s\n", map->so_texture_path);
	printf("%s\n", map->we_texture_path);
	printf("%s\n", map->ea_texture_path);
	printf("%i %i % i\n", map->f_color[0], map->f_color[1], map->f_color[2]);
	printf("%i %i % i\n", map->c_color[0], map->c_color[1], map->c_color[2]);
	usleep(100);
	print_matrix(map->map);
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2)
		return (1);
	map = all_the_parsing_is_here_part_two(argv);
	cub3d(map);
	return (0);
}
