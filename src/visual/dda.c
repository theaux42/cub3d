/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:57:53 by theaux            #+#    #+#             */
/*   Updated: 2025/04/26 00:52:18 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_touching_wall(float origin_x, float origin_y, char **map,
		bool is_crosshair)
{
	int	x;
	int	y;

	x = (int)origin_x;
	y = (int)origin_y;
	if (x < 0 || y < 0)
		return (true);
	if (is_crosshair && map[y][x] == 'd')
		return (true);
	if (map[y][x] == '1' || map[y][x] == 'D')
		return (true);
	return (false);
}

static void	run_dda_loop(t_cub3d *cub3d, t_ray *ray, bool is_crosshair)
{
	while (!ray->is_hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->flag = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->flag = 1;
		}
		if (is_touching_wall(ray->map_pos.x, ray->map_pos.y, cub3d->map.map,
				is_crosshair))
			ray->is_hit = true;
	}
}

static void	calculate_hit_details(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->flag == 0)
	{
		if (ray->dir.x > 0)
			ray->hit.facing = EAST;
		else
			ray->hit.facing = WEST;
		ray->perpWallDist = ray->side_dist.x - ray->delta_dist.x;
		ray->hit.x_wall = cub3d->player.pos.y + ray->perpWallDist * ray->dir.y;
	}
	else
	{
		if (ray->dir.y > 0)
			ray->hit.facing = SOUTH;
		else
			ray->hit.facing = NORTH;
		ray->perpWallDist = ray->side_dist.y - ray->delta_dist.y;
		ray->hit.x_wall = cub3d->player.pos.x + ray->perpWallDist * ray->dir.x;
	}
	ray->hit.pos = ray->map_pos;
	ray->hit.x_wall -= floor(ray->hit.x_wall);
	ray->hit.dist = ray->perpWallDist;
	ray->hit.type = cub3d->map.map[(int)ray->hit.pos.y][(int)ray->hit.pos.x];
	if (ray->hit.type == 'D')
		ray->hit.is_door = true;
}

void	perform_dda(t_cub3d *cub3d, t_ray *ray, bool is_crosshair)
{
	run_dda_loop(cub3d, ray, is_crosshair);
	calculate_hit_details(cub3d, ray);
}
