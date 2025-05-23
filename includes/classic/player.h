/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:03:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/05/01 19:09:40 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

void	empty_player(t_player *player);
bool	init_player(char **map, t_player *player);

int		on_key_press(int key, t_cub3d *cub3d);
int		on_key_release(int key, t_player *player);
void	player_key_handler(t_player *player, char **map);

void	move_player(double angle, float speed, t_player *player, char **map);
bool	try_move(float new_x, float new_y, char **map);

bool	is_touching_wall(float origin_x, float origin_y, char **map);
void	raycast(t_cub3d *cub3d);

#endif