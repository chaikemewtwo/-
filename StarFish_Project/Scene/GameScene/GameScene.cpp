﻿#include"GameScene.h"


void GameMain::Init() {
	m_scene_id = GAME_MAIN;
	m_scene_step = UPDATE;
	m_pobj_mng = new ObjectManager;// object管理者
}

void GameMain::Update() {
	// 更新
	m_pobj_mng->Update();
	if (m_pkey_bord.on(VK_SPACE)) {
		m_scene_step = END;
		m_scene_id = CLEAR;
	}
}

void GameMain::Draw() {
	// 描画
	m_pobj_mng->Draw();
}
