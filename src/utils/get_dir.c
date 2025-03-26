
// void    draw_column(t_cub *cub, int x, int h, t_ray ray)
// {
//     int        j;
//     t_uicol    col;
//     t_image    tex;
//     t_vec3    texcoord;

//     if (h < 0)
//         h = SH;
//     tex = get_tex(cub, ray.info.facing);
//     texcoord.x = (int)(ray.info.x_wall * tex.width);
//     if (ray.info.facing == EAST || ray.info.facing == SOUTH)
//         texcoord.x = tex.width - texcoord.x - 1;
//     texcoord.z = -1;
//     j = SH / 2 - h / 2;
//     if (j < 0)
//         j = -1;
//     while (++j < (SH / 2 + h / 2) && j <= SH)
//     {
//         if (j < 0)
//             continue ;
//         texcoord.y = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);
//         if (texcoord.y != texcoord.z)
//             col = pixel_get(tex, texcoord.x, texcoord.y);
//         texcoord.z = texcoord.y;
//         pixel_put(&cub->image, x, j, col);
//     }
// }

#include "cub3d.h"

char get_wall_orientation(t_cub3d *cub3d, float hitX, float hitY, float ray_angle)
{
    int mapX = (int)hitX;
    int mapY = (int)hitY;
    float epsilon = 0.001f;
    (void)cub3d;

    // Determine if the hit is almost exactly on a vertical or horizontal grid line.
    float offsetX = hitX - mapX;
    float offsetY = hitY - mapY;

    if (fabs(offsetX) < epsilon)  // Hit on the left edge of the cell.
        return (cos(ray_angle) > 0) ? 'W' : 'E';
    if (fabs(offsetX - 1.0f) < epsilon)  // Hit on the right edge.
        return (cos(ray_angle) > 0) ? 'W' : 'E';
    if (fabs(offsetY) < epsilon)  // Hit on the top edge.
        return (sin(ray_angle) > 0) ? 'N' : 'S';
    if (fabs(offsetY - 1.0f) < epsilon)  // Hit on the bottom edge.
        return (sin(ray_angle) > 0) ? 'N' : 'S';
    
    // Fallback if no edge is detected.
    return ' ';
}


// char get_wall_orientation(t_cub3d *cub3d, int x, int y)
// {
//     // player coords are saved at cub3d->player.x and cub3d->player.y
//     // player direction is saved at cub3d->player.dir
//     if (cub3d->map.map[y][x] != '1')
//         return ' ';
//     if (x > 0 && cub3d->map.map[y] && cub3d->map.map[y][x - 1] == '0')
//         return 'W';

//     if (x < (cub3d->map.width - 1) && cub3d->map.map[y] && cub3d->map.map[y][x + 1] == '0')
//         return 'E';
    
//     if (y > 0 && cub3d->map.map[y - 1] && cub3d->map.map[y - 1][x] == '0')
//         return 'N';
    
//     // Check South
//     if (y < (cub3d->map.height - 1) && cub3d->map.map[y + 1] && cub3d->map.map[y + 1][x] == '0')
//         return 'S';
    
//     return ' ';
// }



// void check_wall_directions(t_cub3d *cub3d)
// {
//     for (int y = 0; y < cub3d->map.height; y++)
//     {
//         for (int x = 0; x < cub3d->map.width; x++)
//         {
//             if (cub3d->map.map[y][x] == '1')
//             {
//                 char orientation = get_wall_orientation(cub3d, x, y);
//                 if (orientation != ' ')
//                 {
//                     printf("Wall at (%d, %d) is facing %c\n", x, y, orientation);
//                 }
//             }
//         }
//     }
// }