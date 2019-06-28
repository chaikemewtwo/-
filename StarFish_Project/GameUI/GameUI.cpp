﻿#include "GameUI.h"
#include "../Player/Player.h"
#include "../Lib/Sound/DirectSound.h"


const float GameUI::GAGE_MAX_POS_Y = 380.f;
const float GameUI::GAGE_UNDER_POS_Y = 1000.f;
const float GameUI::ALL_GAGE = GAGE_UNDER_POS_Y - GAGE_MAX_POS_Y;
const float GameUI::RIGHT_GAGE_POS_X = Window::WIDTH - 132.f;
const float GameUI::RIGHT_ROCK_POS_X = Window::WIDTH - 196.f;
const float GameUI::DANGER_LINE_PARCENTAGE = 0.3f;


GameUI::GameUI(Player* p_1, Player* p_2) {
	m_p1 = p_1;
	m_p2 = p_2;

	m_sort_object_type = SortObjectType::GAME_UI;

	m_1p_gage_texture = "Resource/Texture/UI/ui_ora.png";
	m_2p_gage_texture = "Resource/Texture/UI/ui_vio.png";
};


void GameUI::Update(){
	GageColorChange();

	// 片方死んだら片方も死ぬ
	// HACK:PlayerManagerを作成しそこで行う 19/06/14
	if (m_p1->IsActive() == false|| m_p2->IsActive() == false) {
	    m_p1->EnableDead();
		m_p2->EnableDead();
	}
}


void GameUI::Draw() {
	// 左右黒バー
	// スタミナゲージの奥に背景が描画されるのを防止するため
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", 0.f, GAGE_MAX_POS_Y);
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", RIGHT_GAGE_POS_X, GAGE_MAX_POS_Y);

	// スタミナゲージ
	// 自機が死ぬとスタミナゲージの描画をしない
	if (m_p1->IsActive() == true && m_p2->IsActive() == true) {
		// 自機1スタミナゲージ
		Texture::Draw2D(m_1p_gage_texture.c_str(), 0.f, GagePosYCalc(m_p1->StaminaParcentage()));

		// 自機2スタミナゲージ
		Texture::Draw2D(m_2p_gage_texture.c_str(), RIGHT_GAGE_POS_X, GagePosYCalc(m_p2->StaminaParcentage()));
	}

	// 左右ゲージ枠の岩
	Texture::Draw2DUVShift("Resource/Texture/UI/ui_lef.png", 0.f, 0.f,0.f,0.f);
	Texture::Draw2D("Resource/Texture/UI/ui_rig.png", RIGHT_ROCK_POS_X, 0.f);
}


void GameUI::GageColorChange() {
	// 自機1
	if (m_p1->StaminaParcentage() <= DANGER_LINE_PARCENTAGE) {
		m_1p_gage_texture = "Resource/Texture/UI/ui_red.png";
	}
	else {
		m_1p_gage_texture = "Resource/Texture/UI/ui_ora.png";
	}

	// 自機2
	if (m_p2->StaminaParcentage() <= DANGER_LINE_PARCENTAGE) {
		m_2p_gage_texture = "Resource/Texture/UI/ui_red.png";
	}
	else {
		m_2p_gage_texture = "Resource/Texture/UI/ui_vio.png";
	}
}


float GameUI::GagePosYCalc(float stamina_parcent) {
	return GAGE_UNDER_POS_Y - (ALL_GAGE * stamina_parcent);
}
