/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:19:52 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/16 18:30:18 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && ft_strncmp(line, "\n", 5) == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	load_north_tex(t_ray *ray)
{
	int	oldw;
	int	oldh;

	ray->texs.wn.img = mlx_xpm_file_to_image(ray->mlx, \
	ray->map->no_texture_path, &ray->texs.width, &ray->texs.height);
	if (!ray->texs.wn.img)
		ft_exit(ERRTEX);
	ray->texs.wn.addr = mlx_get_data_addr(ray->texs.wn.img, \
	&ray->texs.wn.bits_per_pixel, &ray->texs.wn.line_length, \
	&ray->texs.wn.endian);
	oldw = ray->texs.width;
	oldh = ray->texs.height;
	ray->texs.door.img = mlx_xpm_file_to_image(ray->mlx, \
	DOOR, &ray->texs.width, &ray->texs.height);
	if (!ray->texs.door.img)
		ft_exit(ERRTEX);
	ray->texs.door.addr = mlx_get_data_addr(ray->texs.door.img, \
	&ray->texs.door.bits_per_pixel, &ray->texs.door.line_length, \
	&ray->texs.door.endian);
	if (oldw != ray->texs.width || oldh != ray->texs.height)
		ft_exit(ERRTEX);
}

void	load_east_tex(t_ray *ray)
{
	int	oldw;
	int	oldh;

	oldw = ray->texs.width;
	oldh = ray->texs.height;
	ray->texs.we.img = mlx_xpm_file_to_image(ray->mlx, \
	ray->map->ea_texture_path, &ray->texs.width, &ray->texs.height);
	if (!ray->texs.we.img)
		ft_exit(ERRTEX);
	ray->texs.we.addr = mlx_get_data_addr(ray->texs.we.img, \
	&ray->texs.we.bits_per_pixel, &ray->texs.we.line_length, \
	&ray->texs.we.endian);
	if (oldw != ray->texs.width || oldh != ray->texs.height)
		ft_exit(ERRTEX);
}

void	load_south_tex(t_ray *ray)
{
	int	oldw;
	int	oldh;

	oldw = ray->texs.width;
	oldh = ray->texs.height;
	ray->texs.ws.img = mlx_xpm_file_to_image(ray->mlx, \
	ray->map->so_texture_path, &ray->texs.width, &ray->texs.height);
	if (!ray->texs.ws.img)
		ft_exit(ERRTEX);
	ray->texs.ws.addr = mlx_get_data_addr(ray->texs.ws.img, \
	&ray->texs.ws.bits_per_pixel, &ray->texs.ws.line_length, \
	&ray->texs.ws.endian);
	if (oldw != ray->texs.width || oldh != ray->texs.height)
		ft_exit(ERRTEX);
}

void	load_west_tex(t_ray *ray)
{
	int	oldw;
	int	oldh;

	oldw = ray->texs.width;
	oldh = ray->texs.height;
	ray->texs.ww.img = mlx_xpm_file_to_image(ray->mlx, \
	ray->map->we_texture_path, &ray->texs.width, &ray->texs.height);
	if (!ray->texs.ww.img)
		ft_exit(ERRTEX);
	ray->texs.ww.addr = mlx_get_data_addr(ray->texs.ww.img, \
	&ray->texs.ww.bits_per_pixel, &ray->texs.ww.line_length, \
	&ray->texs.ww.endian);
	if (oldw != ray->texs.width || oldh != ray->texs.height)
		ft_exit(ERRTEX);
}
