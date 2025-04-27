/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:57:53 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 03:43:42 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perform_initial_step(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (cub3d->player.pos.x - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - cub3d->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (cub3d->player.pos.y - ray->map_pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - cub3d->player.pos.y)
			* ray->delta_dist.y;
	}
}

static void	perform_calculation(t_cub3d *cub3d, t_ray *ray, int x)
{
	ray->cameraX = 1 - 2 * x / (double)WIDTH;
	ray->dir.x = cos(cub3d->player.angle) + cub3d->player.plane.x
		* ray->cameraX;
	ray->dir.y = sin(cub3d->player.angle) + cub3d->player.plane.y
		* ray->cameraX;
	ray->map_pos.x = (int)cub3d->player.pos.x;
	ray->map_pos.y = (int)cub3d->player.pos.y;
	ray->delta_dist = (t_dvec2){1e30, 1e30};
	if (ray->dir.x != 0)
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y != 0)
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	perform_initial_step(cub3d, ray);
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

void	perform_dda(t_cub3d *cub3d, t_ray *ray, int x, bool is_crosshair)
{
	perform_calculation(cub3d, ray, x);
	run_dda_loop(cub3d, ray, is_crosshair);
	calculate_hit_details(cub3d, ray);
}
