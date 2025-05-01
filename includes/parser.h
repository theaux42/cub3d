/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/02/07 23:01:28 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/07 23:01:28 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_cub3d	*empty_cub3d(void);

bool	init_cub3d(t_cub3d *cub3d, char *path);
bool	init_parsing(t_cub3d *cub3d);
bool	init_textures(t_cub3d *cub3d);

bool	parse_settings(t_cub3d *cub3d);
bool	parse_map(t_cub3d *cub3d);

bool	check_player_amount(t_map map);

bool	check_map_unkn_char(t_map map);

bool	check_map_chars(t_map map);

bool	is_map_closed(t_cub3d *cub3d);

bool	is_map_valid(t_cub3d *cub3d);

bool	settings_checker(t_cub3d *cub3d);

void	destroy_mlx(t_cub3d *cub3d);

bool	is_finished(t_cub3d *cub3d);

#endif