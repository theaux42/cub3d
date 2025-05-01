/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:28:11 by tbabou            #+#    #+#             */
/*   Updated: 2025/05/01 17:59:57 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_fps_data(t_fps *fps_data)
{
	fps_data->last_time.tv_sec = 0;
	fps_data->last_time.tv_usec = 0;
	fps_data->frame_count = 0;
	fps_data->fps = 0.0;
}

void	init_sky_data(t_sky_data *sky)
{
	sky->sky = (t_texture_struct){0};
	sky->horizon = 0;
	sky->half_h = 0;
	sky->h_fov = 0;
	sky->ang = 0;
	sky->tex_pos = (t_vec2){0, 0};
	sky->start_ang = 0;
	sky->x = 0;
}

void	init_floor_data(t_floor_data *floor)
{
	floor->p = 0;
	floor->pos_z = 0;
	floor->row_dist = 0;
	floor->dir = (t_dvec2){0, 0};
	floor->step = (t_dvec2){0, 0};
	floor->cell = (t_vec2){0, 0};
	floor->tex_pixel = (t_vec2){0, 0};
	floor->color = 0;
	floor->tex_pos = (t_vec2){0, 0};
	floor->first = (t_ray){0};
	floor->last = (t_ray){0};
}
