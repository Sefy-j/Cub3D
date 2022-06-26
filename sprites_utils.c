/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:12:09 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:16:38 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprites(t_sprite *sprite)
{
	while (sprite)
	{
		printf("x: %f\n", sprite->x);
		printf("y: %f\n", sprite->y);
		printf("path: %s\n", sprite->path);
		sprite = sprite->next;
	}
}

t_sprite	*set_values(t_sprite *sprites)
{
	sprites->rel_x = 0;
	sprites->rel_y = 0;
	sprites->sp_x = 0;
	sprites->sp_z = 0;
	return (sprites);
}

t_sprite	*init_sprites(char **map)
{
	t_sprite	*sprites;
	int			i;
	int			j;

	i = -1;
	sprites = NULL;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'R' || map[i][j] == 'F')
			{
				if (!sprites)
					sprites = new_sprite(j, i, map[i][j]);
				else
					add_sprite_back(&sprites, new_sprite(j, i, map[i][j]));
			}
		}
	}
	if (!sprites)
		return (NULL);
	sprites = set_values(sprites);
	return (sprites);
}

t_sprite	*new_sprite(int x, int y, char mode)
{
	t_sprite	*sprites;

	sprites = ft_calloc(sizeof(t_sprite), 1);
	if (!sprites)
		return (NULL);
	sprites->x = (double)x + 0.5;
	sprites->y = (double)y + 0.5;
	if (mode == 'R')
	{
		sprites->path = ft_strdup(STATSPR);
		sprites->path2 = ft_strdup(STATSPR);
	}
	else if (mode == 'F')
	{
		sprites->path = ft_strdup(ANIMSPR1);
		sprites->path2 = ft_strdup(ANIMSPR2);
	}
	sprites->next = NULL;
	return (sprites);
}

void	add_sprite_back(t_sprite **sprites, t_sprite *new)
{
	t_sprite	*temp;

	temp = *sprites;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
