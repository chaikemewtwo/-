#pragma once
#include"./BackGround/BackGround.h"
#include"./Lib/Window/Window.h"




class Map {
public:

	static constexpr int CHIP_SIZE = 128;                                   // �摜�A�S�ẴZ���̑傫��
	static constexpr float CHIP_SIZE_F = (float)CHIP_SIZE;                  // float��
	static constexpr int INTERVAL_HEIGHT = 60;                              // �Ԋu�������đJ�ڂȂǂ�����
	static constexpr int MAP_NUM_X = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // ��ʃ}�b�v�`�b�v�̑傫��
	static constexpr int MAP_NUM_Y = BackGround::GRAPH_SCALE_H / CHIP_SIZE;	// ��ʃ}�b�v�`�b�v�̑傫��
	static constexpr int MAP_SAET_NUM = 5;                                  // �}�b�v�V�[�g�̐�

	Map();
	Map(D3DXVECTOR2 init_pos);

	// �S�̂̓����蔻��
	void MapColider();
	// �����蔻��1
	void Colision(float &pos_x,float &pos_y, float *move_x, float *move_y);
	// �����蔻��2
	void MapHitCheck(float x, float y, float *move_x, float *move_y);

	void MapDraw();

	template<typename T>
	int GetChipPosCast(const T&pos);
	int GetChipParam(const float &pos_x, const float&pos_y, const int&map_number=0);
	void SetChipParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number=0);

	void Update();
	void Draw();
	void MapInit();

	// ���͂���ōs�����A������C���^�[�t�F�[�X������
	void AddPos(D3DXVECTOR2&pos) {

		m_move_pos.x += pos.x;
		m_move_pos.y += pos.y;
		// �Q�Ɛ��������
		pos.x = pos.y = 0.f;

	}

	void SetMovePos(D3DXVECTOR2 pos) {
		m_move_pos = pos;
	}
	// ���@�̍��̈ʒu����u���b�N�̍��W�𒲂ׂ�
	void SetPos(D3DXVECTOR2 pos) {
		m_player_pos = pos;
	}

	D3DXVECTOR2 GetPos() {
		return m_player_pos;
	}
	D3DXVECTOR2 GetMovePos() {
		return m_move_pos;
	}
	
private:

	D3DXVECTOR2 m_player_pos;// ���@�̈ʒu
	D3DXVECTOR2 m_chip_pos;  // �`�b�v�̈ʒu 
	D3DXVECTOR2 m_move_pos;  // ���@�̈ړ��x�N�g��


	// �`��p�}�b�v�o�b�t�@
	int m_draw_map[1000][1000] = {};

	int m_draw_range_begin;
	int m_draw_range_end;
};



// MEMO
// �v���C���[�͎��ۂɂ͓����Ȃ�
// ����ɔw�i�������āA���@���������悤�Ɍ�����
//back_pos.y = p_pos.y;

// �}�b�v�I�u�W�F�N�g
// �O�ƌ��ƍ��̃}�b�v�I�u�W�F�N�g

// �`�敶�̍Œ����for������
// �`��ƍX�V�͕�����

/*
�O�V�[�g�ƍ��V�[�g�ƌ�V�[�g�ō�����ʒu��T���A
�����鎩�@�̈ʒu��T���A�`�悷��͈͂�`�悷��
*/