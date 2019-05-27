﻿#pragma once

#include<string>
#include<d3dx9.h>
#include"../SceneBase.h"


class Clear :public SceneBase {
public:
	Clear();
	~Clear() {}

private:
	enum BackGroundTex {
		SEA_TEXTURE,
		SKY_TEXTURE,
		MOON_TEXTURE,
		BG_TEXTURE_MAX
	};

	enum PlayerClearTex {
		FLIGHT_TEXTURE,
		CLEAR_POSE_TEXTURE,
		CLEAR_TEXTURE_MAX
	};


	void Init()override;
	void Update()override;
	void Draw()override;

	// プレイヤーのアニメーション処理
	void PlayerAnimation();
	// エフェクトのアニメーション処理
	void EffectAnimation();


private:
	//　プレイヤー　//
	D3DXVECTOR2 m_player1_pos;			// 位置１
	D3DXVECTOR2 m_player2_pos;			// 位置２
	float m_player_move_speed;			// 移動速度

	int m_player_animation_timer;		// アニメーション時間カウント用
	int m_player_animation_change_time;	// アニメーションの遷移時間
	int m_player_animation_num;			// アニメーション番号
	int m_player_animation_max;			// アニメーション数
	bool m_player_animation_finish;		// アニメーション完了フラグ

	// 画像用変数と画像リスト
	std::string m_player1_texture;
	std::string m_player2_texture;
	std::string m_player1_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_player2_texture_list[CLEAR_TEXTURE_MAX];

	const int PLAYER_TEXTURE_PARTITION_NUM = 4;		// プレイヤーの画像分割数


	//　背景　//
	D3DXVECTOR2 m_background1_pos;		// 位置１
	D3DXVECTOR2 m_background2_pos;		// 位置２
	float m_background_move_speed;		// 移動速度
	bool m_is_background_move;			// 背景を動かすフラグ

	// 画像用変数と画像リスト
	std::string m_background_texture1;
	std::string m_background_texture2;
	std::string m_background_texture_list[BG_TEXTURE_MAX];

	const float BACKGROUND_TEXTURE_SIZE_Y = 1180;	// 背景画像のｙ軸のサイズ


	//　エフェクト用　//
	int m_effect_animation_num;			// アニメーション番号
	int m_effect_animation_max;			// アニメション数
	float m_effect_animation_timer;		// アニメーションの時間カウント用
	float m_effect_animation_change_time;// アニメーションの遷移時間
	float m_effect_lag_time;			// アニメーションのラグタイム
	float m_effect_lag_count;			// アニメーションのラグカウント用

	// エフェクトの登録
	const std::string m_clear_effect = "Resource/Texture/Effect/crear_eff.png";
};
