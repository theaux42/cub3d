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

void move_player(double angle, float speed, t_player *player, char **map)
{
    t_vec2 movement;
    t_dvec2 new;
    double mangle;


    movement = (t_vec2) { player->right - player->left, player->up - player->down };
    mangle = angle + atan2(movement.x, movement.y);
    if (!(player->up - player->down) && !(player->right - player->left))
        return ;
    new.x = player->pos.x + cos(mangle) * speed;
    new.y = player->pos.y + sin(mangle) * speed;
    if (try_move(new.x, player->pos.y, map))
        player->pos.x = new.x;
    if (try_move(player->pos.x, new.y, map))
        player->pos.y = new.y;
}

void update_camera_plane(t_player *player)
{
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
    
    player->angle = fmod(player->angle, 2 * PI);
    if (player->angle < 0)
        player->angle += 2 * PI;
    
    float current_speed = player->speed;
    if (player->sprint)
        current_speed *= 1.5;
    else
        current_speed = PLAYER_SPEED / 2;
    
    update_camera_plane(player);
    
    move_player(player->angle, current_speed, player, map);
}