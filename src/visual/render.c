/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:59:07 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 18:35:56 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	horiz_sky_cal(t_cub3d *cub3d, t_sky_data *sky_data, int x, int y);

void	draw_line(t_cub3d *cub3d, t_hit hit, t_texture_struct tex,
		t_vec2 pcoord, t_sky_data *sky_data, t_floor_data *floor_data)
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

static void	init_sky(t_cub3d *cub3d, t_sky_data *sky_data)
{
	sky_data->H_FOV = PI / 2.0;
	sky_data->sky = cub3d->map.texture[CEILING_TEXTURE];
	sky_data->half_h = HEIGHT / 2;
	sky_data->horizon = sky_data->half_h - (int)cub3d->player.pitch;
	if (sky_data->horizon < 0)
		sky_data->horizon = 0;
	if (sky_data->horizon > HEIGHT)
		sky_data->horizon = HEIGHT;
	sky_data->start_ang = cub3d->player.angle - sky_data->H_FOV / 2.0;
	sky_data->x = 0;
}

static void	vert_sky_cal(t_sky_data *sky_data, int x)
{
	sky_data->ang = sky_data->start_ang + ((double)x / (WIDTH - 1))
		* sky_data->H_FOV;
	sky_data->ang = fmod(sky_data->ang, 2.0 * PI);
	if (sky_data->ang < 0)
		sky_data->ang += 2.0 * PI;
	sky_data->tex_x = (int)((sky_data->ang / (2.0 * PI)) * sky_data->sky.width);
	sky_data->tex_x = (sky_data->tex_x % sky_data->sky.width
			+ sky_data->sky.width) % sky_data->sky.width;
}

static void	horiz_sky_cal(t_cub3d *cub3d, t_sky_data *sky_data, int x, int y)
{
	sky_data->tex_y = (y * sky_data->sky.height) / sky_data->half_h;
	if (sky_data->tex_y < 0)
		sky_data->tex_y = 0;
	if (sky_data->tex_y >= sky_data->sky.height)
		sky_data->tex_y = sky_data->sky.height - 1;
	sky_data->color = get_pixel_from_tex((t_vec2){sky_data->tex_x,
			sky_data->tex_y}, sky_data->sky, (t_hit){0});
	put_pixel((t_vec2){x, y}, sky_data->color, cub3d);
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
