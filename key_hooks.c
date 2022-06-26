/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 02:32:48 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:37:56 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	stop_automove(t_ray *ray)
{
	ray->vel = 0;
	ray->velgiro = 0;
	ray->velgiro = 0;
	return (0);
}

void	rotate_vector(double *x, double *y, double angle)
{
	double	oldx;

	oldx = *x;
	*x = (*x) * cos(angle) - (*y) * sin(angle);
	*y = oldx * sin(angle) + *y * cos(angle);
}

int	key_release(int keycode, t_ray *ray)
{
	if (keycode == 123)
		ray->velgiro = 0;
	if (keycode == 124)
		ray->velgiro = 0;
	if (keycode == 13)
		ray->vel = 0;
	if (keycode == 1)
		ray->vel = 0;
	if (keycode == 0)
		ray->velstraf = 0;
	if (keycode == 2)
		ray->velstraf = 0;
	return (0);
}

int	key_hooks(int keycode, t_ray *ray)
{
	if (keycode == 53)
		ft_destroywindow(ray);
	if (keycode == 46)
	{
		ray->mouse *= -1;
		if (ray->mouse == 1)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	if (keycode == 49)
		ray = open_close_doors(ray);
	if (keycode == 123)
		ray->velgiro = -0.1;
	if (keycode == 124)
		ray->velgiro = 0.1;
	if (keycode == 13)
		ray->vel = 0.15;
	if (keycode == 1)
		ray->vel = -0.15;
	if (keycode == 0)
		ray->velstraf = -0.15;
	if (keycode == 2)
		ray->velstraf = 0.15;
	return (0);
}

void	get_mouse_pos(t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (ray->mouse == -1)
		return ;
	mlx_mouse_get_pos(ray->mlx_win, &x, &y);
	if (x > WIDTH / 2 + 5)
	{
		rotate_vector(&ray->dir_x, &ray->dir_y, abs(x - WIDTH / 2) * 0.001);
		mlx_mouse_move(ray->mlx_win, WIDTH / 2, HEIGHT / 2);
	}
	else if (x < WIDTH / 2 - 5)
	{
		rotate_vector(&ray->dir_x, &ray->dir_y, abs(x - WIDTH / 2) * (-0.001));
		mlx_mouse_move(ray->mlx_win, WIDTH / 2, HEIGHT / 2);
	}
}
