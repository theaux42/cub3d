/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:59:07 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 21:33:43 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_cub3d *cub3d, t_hit hit, t_texture_struct tex,
		t_vec2 pcoord, t_sky_data *sky_data, t_floor_data *floor_data)
{
	t_vec2		texcoord;
	long long	wall_height;
	int			start_y;
	int			end;

	wall_height = (HEIGHT / hit.dist);
	// Apply pitch offset to wall rendering
	start_y = HEIGHT / 2 - wall_height / 2 + (int)cub3d->player.pitch;
	end = start_y + wall_height;
	texcoord.x = hit.x_wall * tex.width;
	if (hit.facing == SOUTH || hit.facing == WEST)
		texcoord.x = (tex.width - 1) - texcoord.x;
	if (pcoord.y >= start_y && pcoord.y < end)
	{
		texcoord.y = ((double)(pcoord.y - start_y) / wall_height) * tex.height;
		put_pixel(pcoord, get_pixel_from_tex(texcoord, tex, hit), cub3d);
	}
	if (pcoord.y < start_y)
		horiz_sky_cal(cub3d, sky_data, pcoord.x, pcoord.y);
	if (pcoord.y >= end)
	{
		floor_data->tex_pos.y = pcoord.y;
		floor_data->tex_pos.x = pcoord.x;
		init_floor(cub3d, floor_data);
	}
}

void	draw_walls(t_cub3d *cub3d, int x, t_hit hit, t_sky_data *sky_data,
		t_floor_data *floor_data)
{
	t_texture_struct	tex;
	t_vec2				pixelcoord;

	pixelcoord = (t_vec2){.x = x, .y = 0};
	tex = cub3d->map.texture[hit.facing];
	if (hit.is_door)
		tex = cub3d->map.texture[DOOR_TEXTURE];
	while (pixelcoord.y < HEIGHT)
	{
		draw_line(cub3d, hit, tex, pixelcoord, sky_data, floor_data);
		pixelcoord.y++;
	}
}

void	raycast(t_cub3d *cub3d)
{
	int				x;
	t_ray			ray;
	t_sky_data		sky_data;
	t_floor_data	floor_data;

	x = 0;
	init_sky(cub3d, &sky_data);
	perform_dda(cub3d, &floor_data.first, 0, false);
	perform_dda(cub3d, &floor_data.last, WIDTH - 1, false);
	floor_data.pos_z = HEIGHT / 2;
	while (x < WIDTH)
	{
		ray = (t_ray){0};
		perform_dda(cub3d, &ray, x, false);
		vert_sky_cal(&sky_data, x);
		draw_walls(cub3d, x, ray.hit, &sky_data, &floor_data);
		if (x == WIDTH / 2)
			player_crosshair(cub3d);
		x++;
	}
}
