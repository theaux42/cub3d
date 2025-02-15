/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:22:37 by theaux            #+#    #+#             */
/*   Updated: 2025/02/16 00:14:46 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    is_touching_wall(float origin_x, float origin_y, char **map)
{
    float offset = BLOCK * 1.5;
    int x = (int)((origin_x - offset) / BLOCK);
    int y = (int)((origin_y - offset) / BLOCK);
    
    // Vérification des limites de la carte
    if (x < 0 || y < 0)
        return (true);
    
    if (map[y][x] == '1')
        return (true);
    return (false);  
}

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float delta_x, float delta_y, t_cub3d *cub3d)
{
    float angle = atan2(delta_y, delta_x) - cub3d->player.dir;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

int get_dist_color(float dist, int col)
{
    if (col == WIDTH / 2)
        return 0x00FF00;
    int min_color = 0x010000;
    int max_color = 0xFF0000;
    float max_dist = 1200.0;
    if (dist >= max_dist)
        return min_color;

    float ratio = dist / max_dist;
    int red = (int)((1 - ratio) * ((max_color >> 16) & 0xFF) + ratio * ((min_color >> 16) & 0xFF));
    return (red << 16);
}

void	draw_walls(t_cub3d *cub3d, int col, float ray_x, float ray_y)
{
    float	dist;
    int		wall_height;
    int		start_y;
    int		end;
    int		y;

    dist = fixed_dist(ray_x - cub3d->player.x, ray_y - cub3d->player.y, cub3d);
    wall_height = (BLOCK / dist) * (HEIGHT * cub3d->player.fov);
    start_y = HEIGHT / 2 - wall_height / 2;
    end = start_y + wall_height;
    y = 0;
    while (y < HEIGHT)
    {
        if (y < start_y)
            put_pixel(col, y, cub3d->map.colors[CEILING], cub3d);  // plafond (gris)
        else if (y >= start_y && y < end)
            put_pixel(col, y, get_dist_color(dist, col), cub3d);  // mur (vert)
        else
            put_pixel(col, y, cub3d->map.colors[FLOOR], cub3d);  // sol (gris foncé)
        y++;
    }
}

void	single_raycast(t_cub3d *cub3d, int col, float angle)
{
    float	cos_angle = cos(angle);
    float	sin_angle = sin(angle);
    float	ray_x = cub3d->player.x;
    float	ray_y = cub3d->player.y;

    while (!is_touching_wall(ray_x, ray_y, cub3d->map.map))
    {
        // Optionnel: dessiner la trajectoire du rayon dans le monde
        // put_pixel(ray_x, ray_y, 0xFF0000, cub3d);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    draw_walls(cub3d, col, ray_x, ray_y);
}

void	raycast(t_cub3d *cub3d)
{
    float	frac_angle;
    float	angle;
    int		col;

    frac_angle = (PI / 3) / WIDTH;
    angle = cub3d->player.dir - PI / 6;
    col = 0;
    while (col < WIDTH)
    {
        single_raycast(cub3d, col, angle);
        angle += frac_angle;
        col++;
    }
}
