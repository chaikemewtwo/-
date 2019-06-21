﻿#include"../../Lib/Window/Window.h"
#include"../EnemyState/EnemyWaitState/EnemyWaitState.h"
#include"EnemyBase.h"

// コンストラクタで共通の変数初期化
EnemyBase::EnemyBase() {
	m_posx_count = 0;

	m_angle = 0.f;
	m_center = 0.5f;

	// 当たり判定の半径
	m_radius = 64.f;
	// 当たり位置の頂点を画像の中心にずらす
	m_offset.x = 64.f;
	m_offset.y = 64.f;
	m_delete_timer = 100;
	m_max_animation = 0;

	m_p_state_base = Wait::GetInstance();

	// ソートオブジェクトに敵追加
	m_sort_object_type = SortObject::ENEMY;

	// 敵画像の登録
	m_texture_list[EnemyTexture::SEAURCHIN_MOVE] = "Resource/Texture/Enemy/uni_move.png";
	m_texture_list[EnemyTexture::SELLFISH_WAIT] = "Resource/Texture/Enemy/hora_wait.png";
	m_texture_list[EnemyTexture::SELLFISH_READY] = "Resource/Texture/Enemy/hora_ready.png";
	m_texture_list[EnemyTexture::SELLFISH_ATTACK] = "Resource/Texture/Enemy/hora_attack.png";
	m_texture_list[EnemyTexture::NAPOREONFISH_MOVE] = "Resource/Texture/Enemy/megane_move.png";
	m_texture_list[EnemyTexture::NAPOREONFISH_ATTACK] = "Resource/Texture/Enemy/megane_attack.png";
}
//―――――――――――――――――――――

// 引数で指定したStateに遷移
void EnemyBase::ChangeState(StateBase* state) {
	m_p_state_base = state;
}
//―――――――――――――――――――――

void EnemyBase::CheckEnemyActiv() {

	// 画面外に出たら、削除までの時間をカウントダウン
	if (m_pos.y > Window::HEIGHT || m_pos.x<0 || m_pos.x>Window::WIDTH) {

		if (m_delete_timer >= 0) {

			m_delete_timer--;
			if (m_delete_timer <= 0) {
				m_is_active = false;
			}
		}
	}
	// 画面内に戻ったら時間を戻す
	else if (m_pos.y < Window::HEIGHT || m_pos.x>0 || m_pos.x < Window::WIDTH) {
		m_delete_timer = 60;
	}
}
//―――――――――――――――――――――

bool EnemyBase::IsTopPos() {

	if (m_p_player[0]->GetPos().y > m_pos.y&&m_p_player[1]->GetPos().y > m_pos.y) {
		return true;
	}

	return false;
}
//―――――――――――――――――――――

// 指定されたプレイヤーの位置と自身の位置の距離を計算する
D3DXVECTOR2 EnemyBase::CalcDistanceToPlayer(const D3DXVECTOR2& target_pos) {

	D3DXVECTOR2 distance;

	// Y軸の距離を正の数で求める
	if (IsTopPos() == true) {
		distance.y = target_pos.y - m_pos.y;
	}
	else if (IsTopPos() == false) {
		distance.y = m_pos.y - target_pos.y;
	}

	// X軸の距離を正の数で求める
	if (m_is_left == true) {
		distance.x = target_pos.x - m_pos.x;
	}
	else if (m_is_left == false) {
		distance.x = m_pos.x - target_pos.x;
	}

	return distance;
}
//―――――――――――――――――――――

EnemyBase* EnemyBase::GetInstance() {
	return this;
}
//―――――――――――――――――――――

float EnemyBase::GetSpeed() {
	return m_speed;
}
//―――――――――――――――――――――

D3DXVECTOR2 EnemyBase::GetTargetPos() {
	return m_target_pos;
}
//―――――――――――――――――――――

bool EnemyBase::IsLeft() {
	return m_is_left;
}
//―――――――――――――――――――――
