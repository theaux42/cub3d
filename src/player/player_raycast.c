/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:10:14 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/29 15:10:41 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_touching_wall(float origin_x, float origin_y, char **map)
{
	int	x;
	int	y;

	x = (int)origin_x;
	y = (int)origin_y;
	if (x < 0 || y < 0)
		return (true);
	if (map[y][x] == '1')
		return (true);
	return (false);
}

void	perform_dda(t_cub3d *cub3d, t_ray *ray)
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
		if (is_touching_wall(ray->map_pos.x, ray->map_pos.y, cub3d->map.map))
			ray->is_hit = true;
	}
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
}

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
	if (pcoord.y < start_y)
		put_pixel(pcoord.x, pcoord.y, cub3d->map.colors[CEILING], cub3d);
	else if (pcoord.y >= start_y && pcoord.y < end)
	{
		texcoord.y = ((double)(pcoord.y - start_y) / wall_height) * tex.height;
		put_pixel(pcoord.x, pcoord.y, get_pixel_from_tex(texcoord.x, texcoord.y,
				tex, hit), cub3d);
	}
	else
		put_pixel(pcoord.x, pcoord.y, cub3d->map.colors[FLOOR], cub3d);
}

void	draw_walls(t_cub3d *cub3d, int x, t_hit hit)
{
	t_texture_struct	tex;
	t_vec2				pixelcoord;

	pixelcoord = (t_vec2){.x = x, .y = 0};
	tex = cub3d->map.texture[hit.facing];
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

void	draw_crosshair(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = WIDTH / 2 - 5;
	while (i < WIDTH / 2 + 5)
	{
		j = HEIGHT / 2 - 5;
		while (j < HEIGHT / 2 + 5)
		{
			put_pixel(i, j, 0xFFFFFF, cub3d);
			j++;
		}
		i++;
	}
}

void	get_target(t_cub3d *cub3d, t_hit hit)
{
	(void)cub3d;
	ft_printf("Hit: %d %d -", hit.pos.x, hit.pos.y);
	ft_printf("Facing: %d - ", hit.facing);
	ft_printf("Dist: %d - ", (int)hit.dist);
	ft_printf("Type: %c\r", hit.type);
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
		perform_dda(cub3d, &ray);
		draw_walls(cub3d, x, ray.hit);
		draw_crosshair(cub3d);
		if (x == WIDTH / 2)
			get_target(cub3d, ray.hit);
		x++;
	}
}
