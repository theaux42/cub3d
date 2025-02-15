/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:03:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 15:36:28 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLAYER_H
# define PLAYER_H

#include "structs.h"

void    empty_player(t_player *player);
bool    init_player(t_cub3d *cub3d);



int     on_key_press(int key, t_cub3d *cub3d);
int     on_key_release(int key, t_cub3d *cub3d);
void    move_player(t_player *player);

#endif