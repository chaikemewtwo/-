﻿#include"GameScene.h"


GameMain::GameMain() {

	m_scene_step = SceneStep::INIT;	
	
	// サウンドの登録
	m_p_main_bgm = m_paudio.getBuffer("Resource/Sound/BGM/main_bgm.wav");
	m_p_gameover_jingle = m_paudio.getBuffer("Resource/Sound/Failed/game_over.wav");
}
//―――――――――――――――――――

void GameMain::Init() {

	m_scene_id = SceneId::GAME_MAIN;
	m_scene_step = SceneStep::UPDATE;

	m_p_obj_mng = new ObjectManager;

	m_gameover_ui_pos = { (Window::WIDTH / 2), 0 };
	m_gameover_ui_speed = 3.f;
	m_gameover_ui_posy_max = 300;
	m_scene_change_count_timer = 0;
	m_gameover_scene_change_time = 360;

	m_p_main_bgm->SetCurrentPosition(0);
	m_p_gameover_jingle->SetCurrentPosition(0);

	if (m_p_main_bgm != nullptr) {
		m_p_main_bgm->Play(0, 0, DSBPLAY_LOOPING);
	}
}
//―――――――――――――――――――

void GameMain::Update() {

	m_p_obj_mng->Update();	

	// ゲームオーバージングルの再生
	if (m_p_obj_mng->IsGameOver() == true) {

		m_p_main_bgm->Stop();
		if (m_p_gameover_jingle != nullptr) {
			m_p_gameover_jingle->Play(0, 0, 0);
		}
	}

	// Scene遷移処理
	if (m_p_obj_mng->IsClear() == true) {
	
		m_p_main_bgm->Stop();
		m_scene_step = SceneStep::END;
		m_new_scene_id = SceneId::CLEAR;
	}
	else if (m_p_obj_mng->IsGameOver() == true && CheckChangeScene() == true) {

		m_p_gameover_jingle->Stop();
		m_scene_step = SceneStep::END;
		m_new_scene_id = SceneId::TITLE;
	}

	// デバック用
	if (m_pkey_bord.press(VK_F1)) {

		m_p_main_bgm->Stop();
		m_scene_step = SceneStep::END;
		m_new_scene_id = SceneId::CLEAR;
	}
	else if (m_pkey_bord.press(VK_F2)) {

		m_p_main_bgm->Stop();
		m_scene_step = SceneStep::END;
		m_new_scene_id = SceneId::TITLE;
	}
}
//―――――――――――――――――――

void GameMain::Draw() {

	m_p_obj_mng->Draw();

	if (m_p_obj_mng->IsGameOver() == true) {

		Texture::Draw2D(
			m_gameover_ui.c_str(),
			m_gameover_ui_pos.x, m_gameover_ui_pos.y,
			1, 1, 0, 0.5, 0.5
		);
	}
}
//―――――――――――――――――――

// ゲームオーバー処理が終了後にtrueを返す
bool GameMain::CheckChangeScene() {

	if (m_gameover_ui_pos.y <= m_gameover_ui_posy_max) {
		m_gameover_ui_pos.y += m_gameover_ui_speed;
	}
	else if (m_gameover_ui_pos.y >= m_gameover_ui_posy_max) {

		m_scene_change_count_timer++;
		if (m_gameover_scene_change_time <= m_scene_change_count_timer) {
			return true;
		}
	}
	return false;
}
//―――――――――――――――――――
