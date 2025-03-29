/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:47:28 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/29 15:02:23 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_line	*get_first_line(t_cub3d *cub3d)
{
	char		*line;
	t_map_line	*first_line;

	line = get_next_line(cub3d->fd);
	if (!line)
		return (NULL);
	while (line && ft_isemptystr(line))
	{
		free(line);
		line = get_next_line(cub3d->fd);
	}
	if (!line)
		return (NULL);
	first_line = ft_calloc(1, sizeof(t_map_line));
	first_line->next = NULL;
	first_line->line = ft_strdup(line);
	free(line);
	if (!first_line->line)
		return (free(first_line), NULL);
	return (first_line);
}

t_map_line	*get_full_map(t_map_line *head, t_cub3d *cub3d)
{
	t_map_line	*current;
	t_map_line	*next;

	current = ft_calloc(1, sizeof(t_map_line));
	head->next = current;
	if (!current)
		return (ft_dprintf(2, ERR_MALLOC), NULL);
	current->line = get_next_line(cub3d->fd);
	if (!current->line)
		return (ft_dprintf(2, ERR_MALLOC), NULL);
	while (current->line)
	{
		next = ft_calloc(1, sizeof(t_map_line));
		if (!next)
			return (ft_dprintf(2, ERR_MALLOC), NULL);
		current->next = next;
		next->next = NULL;
		current = next;
		current->line = get_next_line(cub3d->fd);
	}
	return (head);
}

static int	get_map_height(t_map_line *map)
{
	int			height;
	t_map_line	*current;

	height = 0;
	current = map;
	while (current)
	{
		height++;
		current = current->next;
	}
	return (height);
}

char	**convert_map(t_map_line *map, int map_height)
{
	char		**final_map;
	t_map_line	*current;
	int			current_line;

	current_line = 0;
	current = map;
	final_map = ft_calloc(1, sizeof(char *) * (map_height + 1));
	if (!final_map)
		return (ft_dprintf(2, ERR_MALLOC), NULL);
	final_map[current_line] = NULL;
	while (current)
	{
		if (current->line)
		{
			final_map[current_line] = ft_strdup(current->line);
			if (!final_map[current_line])
				return ((ft_freesplit(final_map), ft_dprintf(2, ERR_MALLOC)),
					NULL);
		}
		current_line++;
		current = current->next;
	}
	return (final_map);
}

bool	parse_map(t_cub3d *cub3d)
{
	t_map_line	*map;

	map = get_first_line(cub3d);
	if (!map)
		return (ft_dprintf(2, ERR_MALLOC), true);
	map = get_full_map(map, cub3d);
	if (!map)
		return (ft_dprintf(2, ERR_MALLOC), true);
	cub3d->map.height = get_map_height(map);
	printf("Map height : %i", cub3d->map.height);
	cub3d->map.map = convert_map(map, cub3d->map.height);
	if (!cub3d->map.map)
		return (true);
	free_map_struct(map);
	return (false);
}
