/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:20:05 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/30 10:31:00 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manage_door(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->hit.type == 'D')
		cub3d->map.map[(int)ray->map_pos.y][(int)ray->map_pos.x] = 'd';
	else if (ray->hit.type == 'd')
		cub3d->map.map[(int)ray->map_pos.y][(int)ray->map_pos.x] = 'D';
}

void	player_crosshair(t_cub3d *cub3d)
{
	t_ray	ray_middle;

	ray_middle = (t_ray){0};
	perform_dda(cub3d, &ray_middle, WIDTH / 2, true);
	draw_crosshair(cub3d, &ray_middle);
	if (cub3d->player.interact && (ray_middle.hit.type == 'D'
			|| ray_middle.hit.type == 'd'))
		manage_door(cub3d, &ray_middle);
	cub3d->player.interact = false;
}
