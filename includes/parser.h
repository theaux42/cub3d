/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:01:28 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/07 23:01:28 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "structs.h"

t_cub3d *empty_cub3d(void);

bool    init_cub3d(t_cub3d *cub3d, char *path);
bool    init_parsing(t_cub3d *cub3d);

bool parse_settings(t_cub3d *cub3d);
bool    parse_map(t_cub3d *cub3d);

bool is_finished(t_cub3d *cub3d);

#endif