/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:40:48 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:15:52 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		while (*str && *str != '.')
			str++;
		if (ft_strncmp(str, ".cub", 5) == 0)
			return (0);
		if (*str)
			str++;
	}
	return (-1);
}

void	load_sprite_textures(t_ray *ray)
{
	t_sprite	*temp;

	temp = ray->sprites;
	while (temp)
	{
		temp->tex.img = mlx_xpm_file_to_image(ray->mlx, \
		temp->path, &temp->w, &temp->h);
		if (!temp->tex.img)
			ft_exit(ERRTEX);
		temp->tex.addr = mlx_get_data_addr(temp->tex.img, \
		&temp->tex.bits_per_pixel, &temp->tex.line_length, &temp->tex.endian);
		if (ft_strncmp(temp->path, temp->path2, UINT_MAX) != 0)
		{
			temp->tex2.img = mlx_xpm_file_to_image(ray->mlx, \
			temp->path2, &temp->w2, &temp->h2);
			if (!temp->tex2.img)
				ft_exit(ERRTEX);
			temp->tex2.addr = mlx_get_data_addr(temp->tex2.img, \
			&temp->tex2.bits_per_pixel, &temp->tex2.line_length, \
			&temp->tex2.endian);
		}
		else
			temp->tex2 = temp->tex;
		temp = temp->next;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_pixel_get(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + (y
			* data->line_length + x * (data->bits_per_pixel / 8))));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
