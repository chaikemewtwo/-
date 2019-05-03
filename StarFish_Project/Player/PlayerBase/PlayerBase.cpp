﻿#include "PlayerBase.h"
#include <cmath>


PlayerBase::PlayerBase() /*:m_state(new WaitState)*/{
	// 移動速度
	m_move_speed = 2.f;

	// 傾き
	m_character_angle = 0.f;

	// 泳ぎコマンドインターバル、初期化時はMAX値
	m_swim_interval_count = SWIM_INTERVAL;

	// アニメーション番号
	m_animation_number = 0;

	// 初期化時に表示する画像
	/*m_player_texture[WAIT];*/
}


void PlayerBase::Update() {
	// HACK:自機2の操作を分離する
	Keybord& kb = Keybord::getInterface();


	//-----------------------------------------------------
	// 張り付き状態、死亡状態以外共通処理
	// HACK:関数化したほうがスッキリするかも
	//重力を付与(常時)
	AddGravity();

	// 左右角度変更
	// 左
	if ((kb.on('A'))) {
		AngleAdjust(false);
	}
	// 右
	if ((kb.on('D'))) {
		AngleAdjust(true);
	}
	//-----------------------------------------------------

	// 状態推移はステートで切り替え予定
	/*m_state->Update(this);*/

	// 以下の処理は全てステートで管理する
	// 泳ぎアニメーション
	m_animation_number = m_swim_interval_count / SWIM_ANIMATION_SUPPORT_NUMBER;

	// キャラクターが向いている角度に向かって泳ぐ
	if (m_swim_interval_count >= SWIM_INTERVAL) {
		if (kb.press('V')) {
			m_swim_interval_count = 0;
		}
	}
	else {
		SwimUp();
		// 泳ぎインターバルカウントアップ
		++m_swim_interval_count;
	}
}


void PlayerBase::Draw() {
	// 自機2にも自機1のものを使用中
	// 第7、8引数が0.5fずつで中心座標から描画	
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
		m_animation_number
	);
}


void PlayerBase::AddGravity() {
	// 常時下方向へ負荷がかかる
	m_move.y = GRAVITY;
	m_pos.y += m_move.y;
}


void PlayerBase::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (m_character_angle < MAX_ANGLE && m_character_angle > -MAX_ANGLE) {
		m_character_angle += is_move_right ? ANGLE_ADD : -ANGLE_ADD;
	}
	// 角度変更範囲設定
	else if (m_character_angle > -MAX_ANGLE) {
		m_character_angle = MAX_ANGLE - 1.f;
	}
	else if (m_character_angle < MAX_ANGLE) {
		m_character_angle = -MAX_ANGLE + 1.f;
	}
}


void PlayerBase::SwimUp() {
	// ベクトルの長さ(上方向への移動)
	m_move.x = sin(m_character_angle * PI / (float)180.f) * m_move_speed;
	m_move.y = cos(m_character_angle * PI / (float)180.f) * m_move_speed;

	// 移動量インクリメント
	m_pos.x += m_move.x;
	m_pos.y -= m_move.y;
}


void PlayerBase::SetAnimationNumber(int new_animation_number) {
	// アニメーション番号上書き
	m_animation_number = new_animation_number;
}

D3DXVECTOR2 PlayerBase::GetPos() {
	return m_pos;
}

D3DXVECTOR2 PlayerBase::GetMovePos() {
	return m_move;
}


void PlayerBase::SetPos(D3DXVECTOR2 pos) {
	m_pos = pos;
}

void PlayerBase::SetMovePos(D3DXVECTOR2 move) {
	m_move = move;
}


//void PlayerBase::ChangeState(STATE* new_state) {
//	delete this->m_state;
//	this->m_state = new_state;
//}