/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:03:59 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:04:16 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	load_texture(t_game *game, t_texture *tex, const char *path)
{
	// XPM ファイルなどからテクスチャを読み込み、アドレスを取得
	tex->img = mlx_xpm_file_to_image(game->mlx, (char *)path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		fprintf(stderr, "Failed to load texture: %s\n", path);
		// エラー処理を強化: 終了する代わりにゲームの初期化失敗を返す
		// 後で呼び出し側で適切に処理
		game->mlx_error = 1; // mlx関連のエラーが発生したことを示すフラグを設定
		return ;
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length,
			&tex->endian);
}

int	init_game(t_game *game)
{
	// mlx関連のエラーが発生したかどうかを示すフラグを初期化
	game->mlx_error = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
	{
		// ウィンドウ作成失敗時のmlxのクリーンアップ処理を追加
		mlx_destroy_display(game->mlx); // displayの破棄
		free(game->mlx);                // mlxポインタの解放
		return (-1);
	}
	// メイン描画用イメージ
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)  // イメージ作成失敗時のエラー処理を追加
		return (-1); // 適切なエラー処理を追加してください
	game->addr = (int *)mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	// テクスチャ読み込み (ここでは固定パス例)
	load_texture(game, &game->tex_n, "./textures/wall_n.xpm");
	load_texture(game, &game->tex_s, "./textures/wall_s.xpm");
	load_texture(game, &game->tex_e, "./textures/wall_e.xpm");
	load_texture(game, &game->tex_w, "./textures/wall_w.xpm");
	// テクスチャのロードエラーをチェック
	if (game->mlx_error)
		return (-1);
	// プレイヤーの移動/回転スピード設定
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.05;
	return (0);
}
