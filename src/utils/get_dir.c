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