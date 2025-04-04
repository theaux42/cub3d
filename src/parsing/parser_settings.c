/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:34:36 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/14 17:45:27 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool parse_textures(t_cub3d *cub3d, char *line, int target)
{
    while (*line == '\t' || *line == ' ')
        line++;
    if (ft_strncmp(line, "NO ", 3) == 0)
        target = NO_TEXTURE;
    if (ft_strncmp(line, "SO ", 3) == 0)
        target = SO_TEXTURE;
    if (ft_strncmp(line, "WE ", 3) == 0)
        target = WE_TEXTURE;
    if (ft_strncmp(line, "EA ", 3) == 0)
        target = EA_TEXTURE;
    if (target != -1)
    {
        line += 2;
        while (*line == '\t' || *line == ' ')
            line++;
        if (cub3d->map.textures[target] != NULL)
            return(ft_dprintf(2, ERR_EXIST), true);
        cub3d->map.textures[target] = ft_strdup(line);
        if (!cub3d->map.textures[target])
            return (ft_dprintf(2, ERR_MALLOC), true);
    }
    return (false);
}

static bool parse_colors(t_cub3d *cub3d, char *line, int target)
{
    char **split;

    while (*line == '\t' || *line == ' ')
        line++;
    if (ft_strncmp(line, "F ", 2) == 0)
        target = FLOOR;
    if (ft_strncmp(line, "C ", 2) == 0)
        target = CEILING;
    if (target != -1)
    {
        line++;
        while (*line == '\t' || *line == ' ')
            line++;
        split = ft_split(line, ',');
        if (!split)
            return (ft_dprintf(2, ERR_MALLOC), true);
        if (ft_split_len(split) != 3)
            return (ft_dprintf(2, ERR_COLOR_FORMAT), true);
        if (cub3d->map.colors[target] != -1)
            return ((ft_freesplit(split), ft_dprintf(2, ERR_EXIST)), true);
        cub3d->map.colors[target] = get_trgb(0, ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
        ft_freesplit(split);
    }
    return (false);
}

bool parse_settings(t_cub3d *cub3d)
{
    char    *line;

    line = get_next_line(cub3d->fd);
    if (!line)
        return ((ft_dprintf(2, ERR_MALLOC), close(cub3d->fd)), true);
    while (line && !is_finished(cub3d))
    {
        if (parse_textures(cub3d, line, -1))
            return (free(line), true);
        if (parse_colors(cub3d, line, -1))
            return (free(line), true);
        free(line);
        if (!is_finished(cub3d))
            line = get_next_line(cub3d->fd);
        cub3d->map.settings_end++;
    }
    return (false);
}
