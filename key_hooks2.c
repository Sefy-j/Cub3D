/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:36:39 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:39:52 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*open_close_doors(t_ray *ray)
{
	if (ray->map->map[(int)ray->play_y - 1][(int)(ray->play_x)] == 'D')
		ray->map->map[(int)ray->play_y - 1][(int)(ray->play_x)] = 'O';
	else if (ray->map->map[(int)ray->play_y - 1][(int)(ray->play_x)] == 'O')
		ray->map->map[(int)ray->play_y - 1][(int)(ray->play_x)] = 'D';
	if (ray->map->map[(int)ray->play_y + 1][(int)(ray->play_x)] == 'D')
		ray->map->map[(int)ray->play_y + 1][(int)(ray->play_x)] = 'O';
	else if (ray->map->map[(int)ray->play_y + 1][(int)(ray->play_x)] == 'O')
		ray->map->map[(int)ray->play_y + 1][(int)(ray->play_x)] = 'D';
	if (ray->map->map[(int)ray->play_y][(int)(ray->play_x) - 1] == 'D')
		ray->map->map[(int)ray->play_y][(int)(ray->play_x) - 1] = 'O';
	else if (ray->map->map[(int)ray->play_y][(int)(ray->play_x) - 1] == 'O')
		ray->map->map[(int)ray->play_y][(int)(ray->play_x) - 1] = 'D';
	if (ray->map->map[(int)ray->play_y][(int)(ray->play_x) + 1] == 'D')
		ray->map->map[(int)ray->play_y][(int)(ray->play_x) + 1] = 'O';
	else if (ray->map->map[(int)ray->play_y][(int)(ray->play_x) + 1] == 'O')
		ray->map->map[(int)ray->play_y][(int)(ray->play_x) + 1] = 'D';
	return (ray);
}
