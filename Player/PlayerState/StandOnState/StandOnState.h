#pragma once
#include "../PlayerStateBase.h"


// ������ԁi�I�u�W�F�N�g��Ȃǁj
class StandOnState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;

};
