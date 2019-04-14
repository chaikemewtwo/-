#pragma once
#include"../Lib/Input/KeyBord.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../PosConnecter.h"



constexpr float SPEED = 16.f;

class Player : public PosConnector{
public:
	
	Player();

	void Control();

	void Update(){
		Control();
	}

	void Draw();

	// ���z�֐��̃|�W�V����
	D3DXVECTOR2 GetPos()override{
		return m_pos;
	}
	void SetPos(D3DXVECTOR2&vec2)override {
		m_pos = vec2;
	}

	D3DXVECTOR2 GetMovePos()override {
		return m_pos;
	}
	void SetMovePos(D3DXVECTOR2&vec2)override {
		m_pos = vec2;
	}


	// �A�N�Z�T
	D3DXVECTOR2 GetPosition(){
		return m_pos;
	}
	D3DXVECTOR2 GetMovePos() {
		return m_move_pos;
	}

	void SetPosition(const D3DXVECTOR2 &pos) {
		m_pos = pos;
	}
	void SetMovePos(const D3DXVECTOR2 &move_pos) {
		m_move_pos = move_pos;
	}


private:

	// �v���C���[�̈ʒu
	D3DXVECTOR2 m_pos;
	// �ړ��x�N�g��
	D3DXVECTOR2 m_move_pos;
};

