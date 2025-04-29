/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:34:36 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/29 11:20:34 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_settings_type(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (NO_TEXTURE);
	if (ft_strncmp(str, "SO ", 3) == 0)
		return (SO_TEXTURE);
	if (ft_strncmp(str, "WE ", 3) == 0)
		return (WE_TEXTURE);
	if (ft_strncmp(str, "EA ", 3) == 0)
		return (EA_TEXTURE);
	if (ft_strncmp(str, "FL ", 3) == 0)
		return (FLOOR_TEXTURE);
	if (ft_strncmp(str, "CE ", 3) == 0)
		return (CEILING_TEXTURE);
	if (ft_strncmp(str, "D ", 2) == 0)
		return (DOOR_TEXTURE);
	return (-1);
}

static bool	parse_textures(t_cub3d *cub3d, char *line, int target)
{
	while (*line == '\t' || *line == ' ')
		line++;
	target = get_settings_type(line);
	if (target != -1)
	{
		line += 2;
		while (*line == '\t' || *line == ' ')
			line++;
		if (cub3d->map.texture[target].path != NULL)
			return (ft_dprintf(2, ERR_EXIST), true);
		cub3d->map.texture[target].path = ft_strtrim(line, " \t\n\r");
		if (!cub3d->map.texture[target].path)
			return (ft_dprintf(2, DBG_MALLOC), true);
		ft_printf("[%i] Texture %s\n", target, cub3d->map.texture[target].path);
	}
	return (false);
}

bool	parse_settings(t_cub3d *cub3d)
{
	char	*line;

	line = get_next_line(cub3d->fd);
	if (!line)
		return ((ft_dprintf(2, ERR_NO_LINE), close(cub3d->fd)), true);
	while (line && !is_finished(cub3d))
	{
		if (parse_textures(cub3d, line, -1))
			return (free(line), true);
		free(line);
		if (!is_finished(cub3d))
			line = get_next_line(cub3d->fd);
		cub3d->map.settings_end++;
	}
	return (false);
}
