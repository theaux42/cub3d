/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 02:10:46 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 18:35:51 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_floor_line(t_floor_data *f, t_cub3d *cub3d, t_ray *first,
		t_ray *last)
{
	f->p = f->tex_pos.y - HEIGHT / 2.0;
	f->row_dist = f->pos_z / f->p;
	f->step_x = f->row_dist * (last->dir.x - first->dir.x) / WIDTH;
	f->step_y = f->row_dist * (last->dir.y - first->dir.y) / WIDTH;
	f->x0 = cub3d->player.pos.x + f->row_dist * first->dir.x;
	f->y0 = cub3d->player.pos.y + f->row_dist * first->dir.y;
}


void	draw_floor_line2(t_floor_data *f, t_cub3d *cub3d)
{
	double	flo_x;
	double	flo_y;

	flo_x = f->x0 + f->step_x * f->tex_pos.x;
	flo_y = f->y0 + f->step_y * f->tex_pos.x;
	f->cell_x = (int)flo_x;
	f->cell_y = (int)flo_y;
	f->tex_x = ((int)(cub3d->map.texture[FLOOR_TEXTURE].width * (flo_x
					- f->cell_x))) & (cub3d->map.texture[FLOOR_TEXTURE].width
			- 1);
	f->tex_y = ((int)(cub3d->map.texture[FLOOR_TEXTURE].height * (flo_y
					- f->cell_y))) & (cub3d->map.texture[FLOOR_TEXTURE].height
			- 1);
	f->color = get_pixel_from_tex((t_vec2){f->tex_x, f->tex_y},
			cub3d->map.texture[FLOOR_TEXTURE], (t_hit){0});
	put_pixel((t_vec2){f->tex_pos.x, f->tex_pos.y}, f->color, cub3d);
}

void	init_floor(t_cub3d *cub3d, t_floor_data *f)
{
	init_floor_line(f, cub3d, &f->first, &f->last);
	draw_floor_line2(f, cub3d);
}