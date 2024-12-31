/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:33 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:00:21 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	exit_with_error(const char *msg)
{
	fprintf(stderr, "Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_with_error("Usage: ./cub3D <map.cub>");
	// 1. ゲーム構造体を 0 クリア
	memset(&game, 0, sizeof(t_game));
	// 2. .cub ファイルのパース (テクスチャパス、色、マップ読み込み)
	if (parse_config(&game, argv[1]) == -1)
		exit_with_error("Failed to parse configuration.");
	// 3. miniLibX の初期化や、プレイヤー座標/視線の初期化
	if (init_game(&game) == -1)
		exit_with_error("Failed to init game.");
	// 4. イベントフック
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 1L << 17, (int (*)())close_window, &game);
	// 5. メインループ
	// 毎フレーム描画を行いたい場合は mlx_loop_hook を使用
	mlx_loop_hook(game.mlx, (int (*)())render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}
