/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 02:10:46 by theaux            #+#    #+#             */
/*   Updated: 2025/04/27 05:21:07 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Initialise les variables de la ligne de sol pour y donné
 */
static void	init_floor_line(t_floor_data *f, t_cub3d *cub3d, t_ray *first,
		t_ray *last)
{
	f->p = f->y - HEIGHT / 2.0;
	f->pos_z = HEIGHT * 0.5;
	f->row_dist = f->pos_z / f->p;
	f->step_x = f->row_dist * (last->dir.x - first->dir.x) / WIDTH;
	f->step_y = f->row_dist * (last->dir.y - first->dir.y) / WIDTH;
	f->x0 = cub3d->player.pos.x + f->row_dist * first->dir.x;
	f->y0 = cub3d->player.pos.y + f->row_dist * first->dir.y;
}

/*
 * Parcourt la largeur pour dessiner une ligne de sol au y courant
 */
static void	draw_floor_line(t_floor_data *f, t_cub3d *cub3d)
{
	f->x = 0;
	while (f->x < WIDTH)
	{
		f->cell_x = (int)f->x0;
		f->cell_y = (int)f->y0;
		f->tex_x = ((int)(cub3d->map.texture[FLOOR_TEXTURE].width * (f->x0
						- f->cell_x))) & (cub3d->map.texture[FLOOR_TEXTURE].width
				- 1);
		f->tex_y = ((int)(cub3d->map.texture[FLOOR_TEXTURE].height * (f->y0
						- f->cell_y))) & (cub3d->map.texture[FLOOR_TEXTURE].height
				- 1);
		f->color = get_pixel_from_tex((t_vec2){f->tex_x, f->tex_y},
				cub3d->map.texture[FLOOR_TEXTURE], (t_hit){0});
		put_pixel((t_vec2){f->x, f->y}, f->color, cub3d);
		f->x0 += f->step_x;
		f->y0 += f->step_y;
		f->x++;
	}
}

void	draw_floor(t_cub3d *cub3d)
{
	t_floor_data f;
	t_ray first;
	t_ray last;

	first = (t_ray){0};
	last = (t_ray){0};
	f.y = HEIGHT / 2;
	perform_dda(cub3d, &first, 0, false);
	perform_dda(cub3d, &last, WIDTH - 1, false);
	while (f.y < HEIGHT)
	{
		init_floor_line(&f, cub3d, &first, &last);
		draw_floor_line(&f, cub3d);
		f.y++;
	}
}