#include "cub3d.h"

bool    is_touching_wall(float origin_x, float origin_y, char **map)
{
    // float offset = 1.5;
    // int x = (int)((origin_x - offset));
    // int y = (int)((origin_y - offset));
    
	int x = (int) origin_x;
	int y = (int) origin_y;
    // Vérification des limites de la carte
    if (x < 0 || y < 0)
        return (true);
    
    if (map[y][x] == '1')
        return (true);
    return (false);  
}

void    perform_dda(t_cub3d *cub3d, t_ray *ray)
{
	while (!ray->is_hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->flag = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->flag = 1;
		}
		if (is_touching_wall(ray->map_pos.x, ray->map_pos.y, cub3d->map.map))
			ray->is_hit = true;
	}
	if (ray->flag == 0)
	{
		if(ray->dir.x > 0)
			ray->hit.facing = EAST;
		else
			ray->hit.facing = WEST;
		ray->perpWallDist = ray->side_dist.x - ray->delta_dist.x;
		ray->hit.x_wall = ray->map_pos.y + ray->perpWallDist * ray->dir.y;
	}
	else 
	{
		if(ray->dir.y > 0)
			ray->hit.facing = SOUTH;
		else
			ray->hit.facing = NORTH;
		ray->perpWallDist = ray->side_dist.y - ray->delta_dist.y;
		ray->hit.x_wall = ray->map_pos.x + ray->perpWallDist * ray->dir.y;
	}
	ray->hit.dist = ray->perpWallDist;
}

int wall_color(t_hit hit)
{
	if (hit.facing == NORTH)
		return (0x00FF00);
	if (hit.facing == SOUTH)
		return (0xFF0000);
	if (hit.facing == EAST)
		return (0x0000FF);
	if (hit.facing == WEST)
		return (0xFFFF00);
	return (0);
}

void	draw_walls(t_cub3d *cub3d, int x, t_hit hit)
{
    long long		wall_height;
    int		start_y;
    int		end;
    int		y;

    wall_height = (HEIGHT / hit.dist);
    // wall_height = (BLOCK / hit.dist) * (HEIGHT * cub3d->player.fov);
    start_y = HEIGHT / 2 - wall_height / 2;
    end = start_y + wall_height;
    y = 0;
	while (y < HEIGHT)
    {
        if (y < start_y)
            put_pixel(x, y, cub3d->map.colors[CEILING], cub3d);  // plafond (gris)
        else if (y >= start_y && y < end)
		{
			t_texture_struct tex = cub3d->map.texture[1];
			t_vec2 texcoord;
			unsigned int col;

			texcoord.x = hit.x_wall * tex.width;
			texcoord.y = ((y - start_y) / wall_height) * tex.height;
			// col = 0x0000FF;
			col = get_pixel_from_tex(texcoord.x, texcoord.y, tex);
            put_pixel(x, y, col, cub3d);  // mur (vert)
		}
        else
            put_pixel(x, y, cub3d->map.colors[FLOOR], cub3d);  // sol (gris foncé)
        y++;
    }
}

void    perform_initial_step(t_cub3d *cub3d, t_ray *ray)
{
    if (ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = (cub3d->player.pos.x - ray->map_pos.x) * 
			ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side_dist.x = (ray->map_pos.x + 1.0 - cub3d->player.pos.x) *
			ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (cub3d->player.pos.y - ray->map_pos.y) * 
			ray->delta_dist.y;
    }
    else
    {
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - cub3d->player.pos.y) *
			ray->delta_dist.y;
    }
}

void    perform_calculation(t_cub3d *cub3d, t_ray *ray, int x)
{
	ray->cameraX = 1 - 2 * x / (double)WIDTH;
	ray->dir.x = cos(cub3d->player.angle) + 
		cub3d->player.plane.x * ray->cameraX;
	ray->dir.y = sin(cub3d->player.angle) +
		cub3d->player.plane.y * ray->cameraX;
	ray->map_pos.x = (int)cub3d->player.pos.x;
	ray->map_pos.y = (int)cub3d->player.pos.y;
	ray->delta_dist = (t_dvec2) {1e30, 1e30};
	if (ray->dir.x != 0)
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y != 0)
		ray->delta_dist.y = fabs(1 / ray->dir.y);
    perform_initial_step(cub3d, ray);
	
}

void	raycast(t_cub3d *cub3d)
{
	int     x;
	t_ray   ray;
	
	printf("player pos: x %f y %f\n", cub3d->player.pos.x, cub3d->player.pos.y);

	x = 0;
	while (x < WIDTH)
	{
		ray = (t_ray) {0};
		perform_calculation(cub3d, &ray, x);
		perform_dda(cub3d, &ray);
		draw_walls(cub3d, x, ray.hit);
		x++;
	}
}
