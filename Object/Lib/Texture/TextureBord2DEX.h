#pragma once
#include"D3D9.h"
#include<string>



/*

TextureBord2D�̊g���@�\

���������������̂ł��ꂼ��
�����Đݒ�ł���B

Clear�֐����g���΂��̃N���X���g���܂킹��

�f�����b�g�͎g��Ȃ��ϐ��܂Ő������Ă��܂��\��������B
*/

/* �g������

Texture::SetDraw2DTemplate("tep.png",100.f,100.f);
Texture::Draw2DGraphEX();

*/

namespace Texture {

	// �摜���֌W

	void SetFileNameEX(const char*file_name);
	void SetFileNameEX(std::string &file_name);

	// �ړ���]�g�k�֌W
	void SetPostionEX(const float&pos_x, const float&pos_y);
	void SetScaleEX(const float&scale_x, const float&scale_y);
	void SetAngleEX(const float&angle);
	void SetTransformEX(const float&pos_x, const float&pos_y, const float&scale_x, const float&scale_y, const float&angle);

	// �ʒu�ύX
	void SetOfset(const float&cx, const float&cy);

	// UV�֌W
	void SetUV(const int&u_cut_num, const int&v_cut_num, const bool&is_uv);
	void SetAnimation(const int&animation_num);

	// �`��̃Z�b�g�e���v���[�g
	void SetDraw2DTemplate1(const char*file_name, const float&pos_x, const float&pos_y);
	void SetDraw2DTemplate2(const float&scale_x, const float scale_y, const float angle);
	void SetDraw2DTemplate3();

	// �Ō�ɏ����������ɕ`�悷��
	void Draw2DGraphEXAfterNoInit();// �������̕��������A�ł������̒l�͏���������Ă��Ȃ�

	// �`�悵���Ō�ɏ���������
	void Draw2DGraphEX();// �������͏���x�����ǁA����������̂ŁA���肵�Ă���

	// �������֐�
	void Clear();
}






/*
class TextureBord2DEX
{
public:

	// �e��A�N�Z�T
	void SetNormalConfig(const char*file_name, const float&pos_x, const float &pos_y);

	void SetTransform(const D3DXVECTOR2&pos, const D3DXVECTOR2&scale, const float&angle);
	void SetTransform
	   (const float & pos_x,   const float & pos_y,
		const float & scale_x, const float & scale_y,
		const float & angle);
	
	void SetFileName(const char*file_name);
	void SetFileName(const std::string &file_name);

	void SetPostion(const D3DXVECTOR2&pos);
	void SetPostion(const float&pos_x, const float&pos_y);

	void SetScale(const D3DXVECTOR2&scale);
	void SetScale(const float&scale_x, const float&scale_y);

	void SetAngle(const float &angle);

	void SetOfSetPos(const D3DXVECTOR2&ofset);

	// string�ϊ��g���֐�
	void operator =(const std::string & file_name) {
		// c_str��string�^����const char*�^�ɕϊ�
		m_file_name = file_name.c_str();
	}

	// �S�Ă̒l����U�f�t�H���g�l�ɖ߂�
	void Clear() {}

	// �ݒ肵���l�ŕ`�悷��
	void GoDraw() {
		Texture::Draw2D(m_file_name, m_pos.x, m_pos.y, m_scale.x, m_scale.y, m_angle,
			m_ofset.x, m_ofset.
			y, m_uv_cut, m_u_x, m_u_y, m_animation_num);
	}
		 

private:
	const char*m_file_name;   // �t�@�C����
	D3DXVECTOR2 m_pos;		  // �ʒu
	D3DXVECTOR2 m_scale;	  // �g�k
	float m_angle;			  // ��]
	D3DXVECTOR2 m_ofset;	  // �Z���^�[�ʒu(�ǂ�����`�悷�邩)
	bool m_uv_cut;			  // UV�J�b�g���邩(����=TRUE)
	int m_u_x;				  // ����UV�Ő؂��鐔
	int m_u_y;				  // �c��UV�Ő؂��鐔
	int m_animation_num;	  // �A�j���[�V�����i���o�[
};
*/

/*

animation_num��
UV�������������Ԃɓ���Ă�����
�S�ẴA�j���[�V������
�s����B
�������A�A�j���[�V�������s���͈͂�
2�̗ݏ�̋󔒕������`�悵�Ă��܂��̂ŁA
����͓Ǝ��Ő�������K�v������

*/