/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:01:07 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:02:40 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_texture_path(t_game *game, const char *line)
{
	// 例: "NO ./textures/wall_n.xpm" のような行を解析
	// 簡略例: トークン分割して先頭が NO / SO / WE / EA の場合に対応するテクスチャパスをセット
	// line から適宜パス抽出し、必要なら strdup 等で保存
	// ここでは説明用のダミー処理
	(void)game;
	(void)line;
	return (0);
}

static int	parse_color(t_color *color, const char *line)
{
	// 例: "F 220,100,0" などをパースして color->r, color->g, color->b をセット
	// ここでは説明用のダミー処理
	(void)line;
	color->r = 220;
	color->g = 100;
	color->b = 0;
	return (0);
}

int	parse_config(t_game *game, const char *cub_file)
{
	int fd;
	char *line;

	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}

	// サンプル: 行単位で読み込み、行頭で識別
	while ((line = get_next_line(fd)) != NULL)
	{
		if (/* line がテクスチャ指定行なら */ 0)
		{
			if (parse_texture_path(game, line) == -1)
				return (-1);
		}
		else if (/* line が床または天井色指定行なら */ 0)
		{
			if (parse_color(&game->floor_color, line) == -1)
				return (-1);
			// or ceiling_color
		}
		else
		{
			// マップ行とみなして、後で parse_map() 側で処理するため
			// 一時的にバッファに貯める or game->map.grid に追加など
		}
		free(line);
	}
	close(fd);

	// ここで map パースを呼び出す
	if (parse_map(game) == -1)
		return (-1);

	return (0);
}