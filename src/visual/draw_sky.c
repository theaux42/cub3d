/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:55:02 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 20:41:39 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sky(t_cub3d *cub3d, t_sky_data *sky_data)
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

void	vert_sky_cal(t_sky_data *sky_data, int x)
{
	sky_data->ang = sky_data->start_ang + ((double)x / (WIDTH - 1))
		* sky_data->H_FOV;
	sky_data->ang = fmod(sky_data->ang, 2.0 * PI);
	if (sky_data->ang < 0)
		sky_data->ang += 2.0 * PI;
	sky_data->tex_pos.x = (int)((sky_data->ang / (2.0 * PI))
			* sky_data->sky.width);
	sky_data->tex_pos.x = (sky_data->tex_pos.x % sky_data->sky.width
			+ sky_data->sky.width) % sky_data->sky.width;
}

void	horiz_sky_cal(t_cub3d *cub3d, t_sky_data *sky_data, int x, int y)
{
	sky_data->tex_pos.y = (y * sky_data->sky.height) / sky_data->half_h;
	if (sky_data->tex_pos.y < 0)
		sky_data->tex_pos.y = 0;
	if (sky_data->tex_pos.y >= sky_data->sky.height)
		sky_data->tex_pos.y = sky_data->sky.height - 1;
	sky_data->color = get_pixel_from_tex((t_vec2){sky_data->tex_pos.x,
			sky_data->tex_pos.y}, sky_data->sky, (t_hit){0});
	put_pixel((t_vec2){x, y}, sky_data->color, cub3d);
}
