/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:22:37 by theaux            #+#    #+#             */
/*   Updated: 2025/03/25 20:55:50 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray    is_touching_wall(float origin_x, float origin_y, char **map)
{
    t_ray ray;

    float offset = BLOCK * 1.5;
    ray.x = (int)((origin_x - offset) / BLOCK);
    ray.y = (int)((origin_y - offset) / BLOCK);
    ray.orientation = 'N';
    
    if (ray.x < 0 || ray.y < 0)
    {
        return ((ray.is_hit = true), ray);
    }
    
    if (map[ray.y][ray.x] == '1')
    {
        return ((ray.is_hit = true), ray);
    }
    return ((ray.is_hit = false), ray);  
}

t_ray is_touching_wall_temp(float origin_x, float origin_y, t_cub3d *cub3d, float ray_angle)
{
    t_ray ray;
    float offset = BLOCK * 1.5;
    int grid_x = (int)((origin_x - offset) / BLOCK);
    int grid_y = (int)((origin_y - offset) / BLOCK);

    // If we're out of bounds, consider it a hit.
    if (grid_x < 0 || grid_y < 0)
    {
        ray.orientation = get_wall_orientation(cub3d, origin_x, origin_y, ray_angle);
        return ((ray.is_hit = true), ray);
    }
    // If the grid cell is a wall, determine its orientation.
    if (cub3d->map.map[grid_y][grid_x] == '1')
    {
        ray.orientation = get_wall_orientation(cub3d, origin_x, origin_y, ray_angle);
        return ((ray.is_hit = true), ray);
    }
    return ((ray.is_hit = false), ray);  
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

int get_wall_color(t_ray ray_data)
{
    if (ray_data.orientation == 'N')
        return 0x00FF00; // vert
    if (ray_data.orientation == 'S')
        return 0x0000FF; // bleu
    if (ray_data.orientation == 'W')
        return 0xFF0000; // rouge
    if (ray_data.orientation == 'E')
        return 0xFFFF00; // jaune
    return 0xFFFFFF;
}

void	draw_walls(t_cub3d *cub3d, int col, t_ray ray_data, float ray_x, float ray_y)
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
            put_pixel(col, y, get_wall_color(ray_data), cub3d);  // mur (vert)
        else
            put_pixel(col, y, cub3d->map.colors[FLOOR], cub3d);  // sol (gris foncé)
        y++;
    }
}

void single_raycast(t_cub3d *cub3d, int col, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    float ray_x = cub3d->player.x;
    float ray_y = cub3d->player.y;
    t_ray ray_data;

    // Pass the ray angle to the wall-check function.
    ray_data = is_touching_wall_temp(ray_x, ray_y, cub3d, angle);
    while (!ray_data.is_hit)
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
        ray_data = is_touching_wall_temp(ray_x, ray_y, cub3d, angle);
    }
    draw_walls(cub3d, col, ray_data, ray_x, ray_y);
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
