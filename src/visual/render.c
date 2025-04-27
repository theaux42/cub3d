/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:59:07 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 06:51:55 by theaux           ###   ########.fr       */
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
	if (pcoord.y >= start_y && pcoord.y < end)
	{
		texcoord.y = ((double)(pcoord.y - start_y) / wall_height) * tex.height;
		put_pixel(pcoord, get_pixel_from_tex(texcoord, tex, hit), cub3d);
	}
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

static void	draw_sky(t_cub3d *c)
{
	t_texture_struct	sky;
	int					half_h;
	int					horizon;
	const double		H_FOV = PI / 2.0;
	double				start_ang;
	double				ang;
	int					tex_x;
	int					tex_y;

	sky = c->map.texture[CEILING_TEXTURE];
	half_h = HEIGHT / 2;
	horizon = half_h - (int)c->player.pitch;
	if (horizon < 0)
		horizon = 0;
	if (horizon > HEIGHT)
		horizon = HEIGHT;
	start_ang = c->player.angle - H_FOV / 2.0;
	for (int x = 0; x < WIDTH; x++)
	{
		ang = start_ang + ((double)x / (WIDTH - 1)) * H_FOV;
		// Normalize angle to the range [0, 2*PI)
		ang = fmod(ang, 2.0 * PI);
		if (ang < 0)
			ang += 2.0 * PI;
		tex_x = (int)((ang / (2.0 * PI)) * sky.width);
		tex_x = (tex_x % sky.width + sky.width) % sky.width;
		for (int y = 0; y < horizon; y++)
		{
			tex_y = (y * sky.height) / half_h;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= sky.height)
				tex_y = sky.height - 1;
			int color = get_pixel_from_tex((t_vec2){tex_x, tex_y}, sky,
					(t_hit){0}); // Pass dummy hit info
			put_pixel((t_vec2){x, y}, color, c);
		}
	}
}

void	raycast(t_cub3d *cub3d)
{
	int		x;
	t_ray	ray;

	// draw skybox before floor and walls
	draw_sky(cub3d);
	draw_floor(cub3d);
	x = 0;
	while (x < WIDTH)
	{
		ray = (t_ray){0};
		perform_dda(cub3d, &ray, x, false);
		draw_walls(cub3d, x, ray.hit);
		if (x == WIDTH / 2)
			player_crosshair(cub3d);
		x++;
	}
}
