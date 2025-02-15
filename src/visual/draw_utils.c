/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:16:43 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 15:36:49 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(int x, int y, int color, t_cub3d *cub3d)
{
    unsigned int *img;
    
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    img = (unsigned int *)cub3d->data;
    img[y * WIDTH + x] = color;
}

void draw_square(int x, int y, int size, int color, t_cub3d *cub3d)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, cub3d);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, cub3d);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, cub3d);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, cub3d);
}

void ft_mlx_clear_image(t_cub3d *cub3d)
{
    ft_memset(cub3d->data, 0, cub3d->size_line * HEIGHT);
}

void draw_map(t_cub3d *game)
{
    char **map = game->map.map;
    int color = 0x0000FF;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                draw_square(x * BLOCK + 30, y * BLOCK+ 30, BLOCK, color, game);
}
