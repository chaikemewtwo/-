﻿#include"SellFish.h"


SellFish::SellFish(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2,bool no_move) {
	m_pmap = map;
	m_pplayer1 = p1;
	m_pplayer2 = p2;

	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_no_move = no_move;

	m_speed = 5;
	m_power = 15;			
	m_max_animation = 2;
	m_anim_change_time = 20;
	m_enemy_texture = m_texture_list[SELLFISH_WAIT];

	if (m_pos.x < (WINDOW_W_F / 2)) {
		m_is_left = true;
		m_angle = 180;
	}
	else if (m_pos.x > (WINDOW_W_F / 2)) {
		m_is_left = false;
		m_angle = 0;
	}
}
//―――――――――――――――――――――――

void SellFish::Update() {
	m_pstate_base->Action(this);
	m_pos.y += m_pmap->GetMovePos().y;

	OutScreenCheck();
}
//―――――――――――――――――――――――

void SellFish::Draw() {
	Texture::Draw2D(
		m_enemy_texture.c_str(),
		m_pos.x, m_pos.y,
		TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
		m_angle, m_center, m_center,
		true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
		m_animation_num
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――

StateId SellFish::StateChangeCheck() {
	if (CalcDistance().y < 200 && CalcDistance().x>0) {
		m_anim_change_time = 5;
		m_max_animation = 4;
		m_enemy_texture = m_texture_list[SELLFISH_ATTACK];

		return SIDEMOVE_ID;

	}
	else if (CalcDistance().y < 350) {
		m_anim_change_time = 10;
		m_max_animation = 2;
		m_enemy_texture = m_texture_list[SELLFISH_READY];

		return WAIT_ID;
	}

	m_anim_change_time = 20;
	m_max_animation = 2;
	m_enemy_texture = m_texture_list[SELLFISH_WAIT];

	return WAIT_ID;
}
//―――――――――――――――――――――――
