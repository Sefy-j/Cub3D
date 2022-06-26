/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:32:17 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/16 15:32:33 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_destroywindow(t_ray *ray)
{
	if (!ray)
		exit (0);
	exit (0);
}

void	ft_exit(int status)
{
	ft_putstr_fd("Error\n", 2);
	if (status == ERRMAP)
		ft_putstr_fd("Invalid map\n", 2);
	else if (status == ERRTEX)
		ft_putstr_fd("Invalid texture\n", 2);
	exit(status);
}
