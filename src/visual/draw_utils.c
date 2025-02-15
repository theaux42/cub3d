/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:16:43 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/16 00:10:08 by theaux           ###   ########.fr       */
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
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            put_pixel(x + i, y + j, color, cub3d);
            j++;
        }
        i++;
    }
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
                draw_square(x * MINIMAP_SCALE + 30, y * MINIMAP_SCALE+ 30, MINIMAP_SCALE, color, game);
}
