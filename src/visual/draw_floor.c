/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 02:10:46 by theaux            #+#    #+#             */
/*   Updated: 2025/04/30 10:31:25 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_floor_line(t_floor_data *f, t_cub3d *cub3d, t_ray *first,
		t_ray *last)
{
	f->p = f->tex_pos.y - HEIGHT / 2.0 - cub3d->player.pitch;
	f->row_dist = f->pos_z / f->p;
	f->step.x = f->row_dist * (last->dir.x - first->dir.x) / WIDTH;
	f->step.y = f->row_dist * (last->dir.y - first->dir.y) / WIDTH;
	f->dir.x = cub3d->player.pos.x + f->row_dist * first->dir.x;
	f->dir.y = cub3d->player.pos.y + f->row_dist * first->dir.y;
}

void	draw_floor_line2(t_floor_data *f, t_cub3d *cub3d)
{
	t_dvec2	floor_pos;

	floor_pos.x = f->dir.x + f->step.x * f->tex_pos.x;
	floor_pos.y = f->dir.y + f->step.y * f->tex_pos.x;
	f->cell.x = (int)floor_pos.x;
	f->cell.y = (int)floor_pos.y;
	f->tex_pixel.x = ((int)(cub3d->map.texture[5].width * (floor_pos.x
					- f->cell.x))) & (cub3d->map.texture[5].width - 1);
	f->tex_pixel.y = ((int)(cub3d->map.texture[5].height * (floor_pos.y
					- f->cell.y))) & (cub3d->map.texture[5].height - 1);
	f->color = get_pixel_from_tex((t_vec2){f->tex_pixel.x, f->tex_pixel.y},
			cub3d->map.texture[FLOOR_TEXTURE], (t_hit){0});
	put_pixel((t_vec2){f->tex_pos.x, f->tex_pos.y}, f->color, cub3d);
}

void	init_floor(t_cub3d *cub3d, t_floor_data *f)
{
	init_floor_line(f, cub3d, &f->first, &f->last);
	draw_floor_line2(f, cub3d);
}
