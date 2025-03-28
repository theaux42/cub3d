#include "cub3d.h"

void empty_player(t_player *player)
{
    player->pos.x = 0.0;
    player->pos.y = 0.0;
    player->angle = PI / 2;
    player->fov = 1.0;
    player->speed = PLAYER_SPEED;
    player->left = false;
    player->right = false;
    player->up = false;
    player->down = false;
    player->sprint = false;
    player->rotate_left = false;
    player->rotate_right = false;
    
    // Initialize the camera plane perpendicular to direction
    player->plane.x = 0.0;
    player->plane.y = 0.66;
}

int on_key_press(int key, t_cub3d *cub3d)
{
    if (key == LEFT)
        cub3d->player.left = true;
    else if (key == RIGHT)
        cub3d->player.right = true;
    else if (key == UP)
        cub3d->player.up = true;
    else if (key == DOWN)
        cub3d->player.down = true;
    else if (key == SHIFT)
        cub3d->player.sprint = true;
    else if (key == A)
        cub3d->player.rotate_left = true;
    else if (key == D)
        cub3d->player.rotate_right = true;
    else if (key == MINUS && cub3d->player.fov > 0.5)
        cub3d->player.fov -= 0.1;
    else if (key == PLUS && cub3d->player.fov < 2.0)
        cub3d->player.fov += 0.1;
    else if (key == ESCAPE)
    {
        free_cub3d(cub3d);
        exit(0);
    }
    return (0);
}

int on_key_release(int key, t_player *player)
{
    if (key == LEFT)
        player->left = false;
    else if (key == RIGHT)
        player->right = false;
    else if (key == UP)
        player->up = false;
    else if (key == DOWN)
        player->down = false;
    else if (key == SHIFT)
        player->sprint = false;
    else if (key == A)
        player->rotate_left = false;
    else if (key == D)
        player->rotate_right = false;
    return (0);
}

bool try_move(float new_x, float new_y, char **map)
{
    // Add a buffer zone around walls for smooth movement
    const float collision_buffer = 0.2;
    
    // Check collision at new position plus buffer in each direction
    if (is_touching_wall(new_x + collision_buffer, new_y, map) ||
        is_touching_wall(new_x - collision_buffer, new_y, map) ||
        is_touching_wall(new_x, new_y + collision_buffer, map) ||
        is_touching_wall(new_x, new_y - collision_buffer, map))
        return false;
        
    return true;
}

void move_player(float cos_dir, float sin_dir, float speed, t_player *player, char **map)
{
    float new_x;
    float new_y;
    
    // Forward movement
    if (player->up)
    {
        new_x = player->pos.x + cos_dir * speed;
        new_y = player->pos.y + sin_dir * speed;
        if (try_move(new_x, new_y, map))
        {
            player->pos.x = new_x;
            player->pos.y = new_y;
        }
    }
    
    // Backward movement
    if (player->down)
    {
        new_x = player->pos.x - cos_dir * speed;
        new_y = player->pos.y - sin_dir * speed;
        if (try_move(new_x, new_y, map))
        {
            player->pos.x = new_x;
            player->pos.y = new_y;
        }
    }
    
    // Strafe right
    if (player->right)
    {
        new_x = player->pos.x - sin_dir * speed;
        new_y = player->pos.y + cos_dir * speed;
        if (try_move(new_x, new_y, map))
        {
            player->pos.x = new_x;
            player->pos.y = new_y;
        }
    }
    
    // Strafe left
    if (player->left)
    {
        new_x = player->pos.x + sin_dir * speed;
        new_y = player->pos.y - cos_dir * speed;
        if (try_move(new_x, new_y, map))
        {
            player->pos.x = new_x;
            player->pos.y = new_y;
        }
    }
}

void update_camera_plane(t_player *player)
{
    // Update the camera plane to be perpendicular to the player direction
    player->plane.x = sin(player->angle) * player->fov;
    player->plane.y = -cos(player->angle) * player->fov;
}

void player_key_handler(t_player *player, char **map)
{
    // Handle rotation
    if (player->rotate_left)
        player->angle -= CAMERA_SPEED;
    if (player->rotate_right)
        player->angle += CAMERA_SPEED;
    
    // Keep angle between 0 and 2*PI
    player->angle = fmod(player->angle, 2 * PI);
    if (player->angle < 0)
        player->angle += 2 * PI;
    
    // Adjust speed based on sprint state
    float current_speed = player->speed;
    if (player->sprint)
        current_speed *= 1.5;
    else
        current_speed = PLAYER_SPEED / 2;
    
    // Update camera plane
    update_camera_plane(player);
    
    // Move player
    move_player(cos(player->angle), sin(player->angle), current_speed, player, map);
}