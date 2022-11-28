/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:31:53 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/07 16:21:09 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_map(char *str, t_cub *cub)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	if (ft_strstr(str, "\n\n"))
	{
		ft_putstr_fd("Error\nMap is invalid!\n", 2);
		return ;
	}
	cub->map = ft_split(str, '\n');
	free(str);
	while ((cub->map)[i])
	{
		j = 0;
		while ((cub->map)[i][j])
		{
			if (!map_pos_is_valid(i, j, &flag, cub))
			{
				ft_putstr_fd("Error\nMap is invalid!\n", 2);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	map_pos_is_valid(int i, int j, int *flag, t_cub *cub)
{
	char	**map;

	map = cub->map;
	if (map[i][j] == ' ' && ((i && ((int)ft_strlen(map[i - 1]) > j) && !ft_strchr("1 ", map[i - 1][j])) \
		|| (map[i][j + 1] && !ft_strchr(" 1", map[i][j + 1])) \
		|| (map[i + 1] && ((int)ft_strlen(map[i + 1]) > j) && !ft_strchr(" 1", map[i + 1][j])) \
		|| (j && map[i][j - 1] && !ft_strchr(" 1", map[i][j - 1]))))
		return (0);
	else if (map[i][j] == '0' && (!i || !((int)ft_strlen(map[i - 1]) > j) || !j || !map[i + 1] || !((int)ft_strlen(map[i + 1]) > j)|| !map[i][j + 1] \
		|| !ft_strchr("01NESW", map[i - 1][j]) || !ft_strchr("01NESW", map[i][j + 1]) \
		|| !ft_strchr("01NESW", map[i + 1][j]) || !ft_strchr("01NESW", map[i][j - 1])))
		return (0);
	else if (ft_strchr("NESW", map[i][j]) && (*flag || !i || !((int)ft_strlen(map[i - 1]) > j) || !j || !map[i + 1] || !((int)ft_strlen(map[i + 1]) > j)|| !map[i][j + 1] \
		|| !ft_strchr("01NESW", map[i - 1][j]) || !ft_strchr("01NESW", map[i][j + 1]) \
		|| !ft_strchr("01NESW", map[i + 1][j]) || !ft_strchr("01NESW", map[i][j - 1])))
		return (0);
	else if (!ft_strchr("01 NESW", map[i][j]))
		return (0);
	if (ft_strchr("NESW", map[i][j]))
	{
		update_initial_pos(i, j, map[i][j], cub);
		map[i][j] = '0';
		*flag = 1;
	}
	return (1);
}
