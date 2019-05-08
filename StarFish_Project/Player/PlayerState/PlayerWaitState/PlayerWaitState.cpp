﻿#include "PlayerWaitState.h"
#include "../PlayerSwimState/PlayerSwimState.h"
#include "../../PlayerBase/PlayerBase.h"

// 待機状態（オブジェクト上以外、オブジェクト上での待機状態はStandingWaitStateクラス）
// 初期化
void PlayerWaitState::Init(PlayerBase* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション1枚分タイマー
	m_animation_timer = 0;

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture("Resource/de_wait.png");
}


// 更新
void PlayerWaitState::Update(PlayerBase* p) {
	Keybord& kb = Keybord::getInterface();

	// 重力付与
	p->AddGravity();

	// 左右角度変更
	// 左
	if ((kb.on('A'))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on('D'))) {
		p->AngleAdjust(true);
	}

	// 泳ぎ状態へ移行
	if (kb.press(VK_SPACE)) {
		p->ChangeState(PlayerSwimState::GetInstance());
	}

	p->AnimationDraw(4,4,ONE_ANIMATION_SPEED);
}
