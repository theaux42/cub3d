/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:59:07 by theaux            #+#    #+#             */
/*   Updated: 2025/04/26 00:54:28 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_cub3d *cub3d, t_hit hit, t_texture_struct tex,
		t_vec2 pcoord)
{
	t_vec2		texcoord;
	long long	wall_height;
	int			start_y;
	int			end;

	wall_height = (HEIGHT / hit.dist);
	start_y = HEIGHT / 2 - wall_height / 2;
	end = start_y + wall_height;
	texcoord.x = hit.x_wall * tex.width;
	if (hit.facing == SOUTH || hit.facing == WEST)
		texcoord.x = (tex.width - 1) - texcoord.x;
	if (pcoord.y < start_y)
		put_pixel(pcoord, cub3d->map.colors[CEILING], cub3d);
	else if (pcoord.y >= start_y && pcoord.y < end)
	{
		texcoord.y = ((double)(pcoord.y - start_y) / wall_height) * tex.height;
		put_pixel(pcoord, get_pixel_from_tex(texcoord, tex, hit),
			cub3d);
	}
	else
		put_pixel(pcoord, cub3d->map.colors[FLOOR], cub3d);
}

void	draw_walls(t_cub3d *cub3d, int x, t_hit hit)
{
	t_texture_struct	tex;
	t_vec2				pixelcoord;

	pixelcoord = (t_vec2){.x = x, .y = 0};
	tex = cub3d->map.texture[hit.facing];
	if (hit.is_door)
		tex = cub3d->map.texture[DOOR_TEXTURE];
	while (pixelcoord.y < HEIGHT)
	{
		draw_line(cub3d, hit, tex, pixelcoord);
		pixelcoord.y++;
	}
}

void	perform_initial_step(t_cub3d *cub3d, t_ray *ray)
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

void	perform_calculation(t_cub3d *cub3d, t_ray *ray, int x)
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

void	raycast(t_cub3d *cub3d)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		ray = (t_ray){0};
		perform_calculation(cub3d, &ray, x);
		perform_dda(cub3d, &ray, false);
		draw_walls(cub3d, x, ray.hit);
		if (x == WIDTH / 2)
			player_crosshair(cub3d);
		x++;
	}
}
