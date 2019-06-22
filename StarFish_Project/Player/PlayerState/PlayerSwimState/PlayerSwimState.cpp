﻿#include"PlayerSwimState.h"
#include"../PlayerWaitState/PlayerWaitState.h"
#include"../PlayerDeathState/PlayerDeathState.h"
#include"../../Player/Player.h"


const int PlayerSwimState::ONE_ANIMATION_SPEED = 6;
const int PlayerSwimState::MAX_ANIMATION_TEX_NUM = 16;
const int PlayerSwimState::CHANGE_STATE_COUNT = ONE_ANIMATION_SPEED * MAX_ANIMATION_TEX_NUM;
const float PlayerSwimState::TO_SWIM_USE_STAMINA = 200.f;


void PlayerSwimState::Init(Player* p) {
	p->ResetStateChangeTimer();

	p->ResetAnimationCount();

	p->SetPlayerTexture(p->SWIM_TEXTURE);

	p->SetSwimEnable(true);

	p->DecStamina(TO_SWIM_USE_STAMINA);

	m_p_swim_se = m_p_audio.getCloneBuffer("Resource/Sound/Player/swim1.wav");

	// 泳ぎ状態になったら1回だけSEを鳴らす
	m_p_swim_se->Play(0,0,0);
}


void PlayerSwimState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();

	p->AnimationDraw(MAX_ANIMATION_TEX_NUM-1, ONE_ANIMATION_SPEED);

	p->AddStateChangeTimer();

	p->SwimUp();

	// 左右角度変更
	// 左
	if ((kb.on(p->imput_button_list[p->LEFT_KEY]))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on(p->imput_button_list[p->RIGHT_KEY]))) {
		p->AngleAdjust(true);
	}

	// 待機状態に戻る
	if (p->GetStateChangeTimer() >= CHANGE_STATE_COUNT) {
		p->ChangeState(PlayerWaitState::GetInstance());
	}

	// 死亡状態へ移行
	if (p->IsActive() == false) {
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
