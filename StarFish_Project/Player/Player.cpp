﻿#include "Player.h"
#include "PlayerState/PlayerWaitState/PlayerWaitState.h"
#include "PlayerState/PlayerSwimState/PlayerSwimState.h"
#include "PlayerState/PlayerStandingWaitState/PlayerStandingWaitState.h"
#include <cmath>
#include <time.h>


Player::Player(ID id) :m_state(PlayerWaitState::GetInstance()) {
	Keybord& kb = Keybord::getInterface();

	// 移動速度
	m_speed = 2.f;

	// 傾き
	m_character_angle = 0.f;

	// アニメーション番号
	m_animation_num = 0;

	// 移動量
	m_move.x = 0.f;
	m_move.y = 0.f;

	// 待機状態初期化
	m_state->Init(this);

	// スタミナ
	m_stamina = MAX_STAMINA;

	// 描画フラグ
	m_draw_enable = true;


	// 自機1（ヒくん、オレンジの方）
	if (id == STAR_1) {
		// 位置
		m_pos.x = WINDOW_W / 2 - 200.f;
		m_pos.y = WINDOW_H / 2;

		// 操作
		imput_button_name[LEFT_KEY][256] = 'A';
		imput_button_name[RIGHT_KEY][256] = 'D';
		imput_button_name[SWIM_KEY][256] = 'W';
		imput_button_name[PULL_ROPE_KEY][256] = 'Q';
	
		// 画像
		star_texture_name[WAIT_TEXTURE][256] = "Resource/Texture/Player/de_wait.png";
		star_texture_name[STANDING_WAIT_TEXTURE][256] = "Resource/Texture/Player/de_standing_wait.png";
		star_texture_name[SWIM_TEXTURE][256] = "Resource/Texture/Player/de_swim.png";
		//star_texture_name[GRAB_TEXTURE][256] = "Resource/de_swim.png";
		//star_texture_name[PULL_ROPE_TEXTURE][256] = "Resource/de_swim.png";
		//star_texture_name[DEATH_TEXTURE][256] = "Resource/de_swim.png";
	}

	// 自機2（デちゃん、ピンクの方）
	else if (id == STAR_2) {
		// 位置
		m_pos.x = WINDOW_W / 2 + 200.f;
		m_pos.y = WINDOW_H / 2;

		// 操作
		imput_button_name[LEFT_KEY][256] = VK_LEFT;
		imput_button_name[RIGHT_KEY][256] = VK_RIGHT;
		imput_button_name[SWIM_KEY][256] = VK_UP;
		imput_button_name[PULL_ROPE_KEY][256] = 'M';

		// 画像
		star_texture_name[WAIT_TEXTURE][256] = "Resource/Texture/Player/hi_wait.png";
		star_texture_name[STANDING_WAIT_TEXTURE][256] = "Resource/Texture/Player/hi_standing_wait.png";
		star_texture_name[SWIM_TEXTURE][256] = "Resource/Texture/Player/hi_swim.png";
		//star_texture_name[GRAB_TEXTURE][256] = "Resource/de_swim.png";
		//star_texture_name[PULL_ROPE_TEXTURE][256] = "Resource/de_swim.png";
		//star_texture_name[DEATH_TEXTURE][256] = "Resource/de_swim.png";
	}
}


void Player::Update() {
	// ステート更新
	// 内部の処理は各ステート内で管理しています
	m_state->Update(this);

	// 移動を加算
	m_pos += m_move;

	// 移動量を初期化（マップの当たり判定で必要）
	m_move.x = 0.f;
	m_move.y = 0.f;

	// スタミナ自動回復
	if (m_stamina < MAX_STAMINA) {
		++m_stamina;
	}
	else {
		m_stamina = MAX_STAMINA;
	}
}


void Player::Draw() {
	// 自機2にも自機1のものを使用中
	// 第7、8引数が0.5fずつで中心座標から描画	
	// 被弾状態は描画する、しないを切り替えて表現する
	if (m_draw_enable == true) {
		Texture::Draw2D(
			m_player_texture.c_str(),
			m_pos.x,
			m_pos.y,
			TEXTURE_SIZE_X,
			TEXTURE_SIZE_Y,
			m_character_angle,
			0.5f,
			0.5f,
			true,
			TEXTURE_PARTITION_X_NUMBER,
			TEXTURE_PARTITION_Y_NUMBER,
			m_animation_num
		);
	}
}


void Player::AddGravity() {
	// 常時下方向へ負荷がかかる
	m_move.y -= GRAVITY;
}


void Player::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (m_character_angle <= MAX_ANGLE && m_character_angle >= -MAX_ANGLE) {
		m_character_angle += is_move_right ? ANGLE_ADD : -ANGLE_ADD;
	}
	// 角度変更範囲設定
	// 左
	else if (m_character_angle >= MAX_ANGLE) {
		m_character_angle = MAX_ANGLE;
	}
	// 右
	else if (m_character_angle <= MAX_ANGLE) {
		m_character_angle = -MAX_ANGLE;
	}
}


void Player::SwimUp() {
	// 上方向への移動量(ベクトルの長さ)を割り出す
	m_move.x += sin(m_character_angle * PI / (float)180.f) * m_speed;
	m_move.y -= cos(m_character_angle * PI / (float)180.f) * m_speed;
}


// 自機と敵との当たり判定後の処理(点滅処理へ移行)
void  Player::HitAction(Type type) {
	if (type == ENEMY) {
		
	}
}
