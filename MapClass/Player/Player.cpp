#include"Player.h"
//#include"../ObjectVisitor.h"
#include"../Map/BackGround.h"



// �R���X�g���N�^
Player::Player() {

	m_pos.x = m_pos.y = 0.f;
	m_move_pos.x = m_move_pos.y = SPEED;

	m_pos.x = (BackGround::GRAPH_SCALE_W / 2) - 100;
	m_pos.y = (-BackGround::GRAPH_SCALE_H / 2) + 100;
}


// ���@����
void Player::Control() {

	Keybord&kb = Keybord::getInterface();

	// �ړ��x�N�g���𖳂��ɂ���
	m_move_pos.x = m_move_pos.y = 0;

	// ���@�̑���
	{
		if (kb.on(VK_LEFT)) {
			m_move_pos.x-=SPEED;
		}
		if (kb.on(VK_RIGHT)) {
			m_move_pos.x += SPEED;
		}
		if (kb.on(VK_UP)) {
			m_move_pos.y += SPEED;
		}
		if (kb.on(VK_DOWN)) {
			m_move_pos.y -= SPEED;
		}

		// ���Z
		m_pos += m_move_pos;

		kb.update();
	}
}

void Player::Draw() {


	// ���@(y���W�͓��������A�w�i�𓮂����āA�������Ă���悤�Ɍ���������)
	Texture::Draw2D("Texture/de_swim.png", m_pos.x,(BackGround::GRAPH_SCALE_H / 2), -384.f, -384.f);


	//OX::DebugFont::print(100, 100, 1000, "m_player_pos.x => %f", m_pos.x);
	//OX::DebugFont::draw(dev);
	//OX::DebugFont::clear();
}

// �K����󂯓���郁�\�b�h
//void Player::AcceptVisitor(ObjectVisitor*visit) {

	//visit->VisitPlayer(this);
//}
