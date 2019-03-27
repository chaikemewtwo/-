#include"TextureBord2DEX.h"
#include"TextureBoad2D.h"


// �\���̂͏�Ԃ�����
struct TextureBord2DEX {

	TextureBord2DEX();

	// �e���v���[�g�������֐�
	void Init();

	const char*file_name;   // �t�@�C����
	D3DXVECTOR2 pos;		// �ʒu
	D3DXVECTOR2 scale;	    // �g�k
	float angle;			// ��]
	D3DXVECTOR2 ofset;	    // �Z���^�[�ʒu(�ǂ�����`�悷�邩)
	bool uv_cut;			// UV�J�b�g���邩(����=TRUE)
	int u_x;				// ����UV�Ő؂��鐔
	int u_y;				// �c��UV�Ő؂��鐔
	int animation_num;	    // �A�j���[�V�����i���o�[
};

void TextureBord2DEX::Init() {

	file_name = NULL;
	pos.x = pos.y = 0.f;
	scale.x = scale.y = 1.f;
	angle = 0.f;
	ofset.x = ofset.y = 0.f;
	uv_cut = false;
	u_x = 0;
	u_y = 0;
	animation_num = 0;
}

TextureBord2DEX::TextureBord2DEX() {
	Init();
}


namespace Texture {

	// �e�N�X�`�������������N���X
	TextureBord2DEX tb;


	// �t�@�C����
	void SetFileNameEX(const char*file_name) {
		tb.file_name = file_name;
	}
	void SetFileNameEX(std::string &file_name) {
		SetFileNameEX(file_name.c_str());
	}

	// �ʒu
	void SetPostionEX(const float&pos_x, const float&pos_y) {
		tb.pos.x = pos_x;
		tb.pos.y = pos_y;
	}

	// �g�k
	void SetScaleEX(const float&scale_x, const float&scale_y) {
		tb.scale.x = scale_x;
		tb.scale.y = scale_y;
	}

	// ��]
	void SetAngleEX(const float&angle) {
		tb.angle = angle;
	}

	// �I�t�Z�b�g�l
	void SetOfset(const float&cx, const float&cy) {
		tb.ofset.x = cx;
		tb.ofset.y = cy;
	}

	// UV�ݒ�
	void SetUV(const int&u_cut_num, const int&v_cut_num, const bool&is_uv) {
		tb.u_x = u_cut_num;
		tb.u_y = v_cut_num;
		tb.uv_cut = is_uv;
	}

	// �A�j���[�V�����i���o�[�����߂�
	void SetAnimation(const int&animation_num) {
		tb.animation_num = animation_num;
	}

	// Template�Ō��₷���ݒ肷��
	void SetDraw2DTemplate1(const char*file_name,const float&pos_x,const float&pos_y) {
		SetFileNameEX(file_name);
		SetPostionEX(pos_x, pos_y);
	}

	template<typename T>

	//void SetDraw2DTemplate2(T &obj1,T&obj2,T&obj3,T&obj4,T&obj5){
	//	
	//	T index[5] = { obj1,obj2,obj3,obj4,obj5 };
	//
	//	for (int i = 0; i < 5; i++) {
	//
	//		if (index[i] == tb.file_name) {
	//			tb.file_name = index[i];
	//		}
	//
	//	}
	//}


	// ��]�g�k�ړ���ݒ肷��֐�
	void SetTransformEX(const float&pos_x, const float&pos_y, const float&scale_x, const float&scale_y, const float&angle) {
		SetPostionEX(pos_x, pos_y);
		SetScaleEX(scale_x, scale_y);
		SetAngleEX(angle);
	}

	// �`�悵�ď�������U���������Ȃ��o�[�W����
	void Draw2DGraphEXAfterNoInit() {

		// �`��
		Draw2D(tb.file_name,
			tb.pos.x,tb.pos.y,
			tb.scale.x,tb.scale.y,
			tb.angle,
			tb.ofset.x, tb.ofset.y,
			tb.uv_cut,
			tb.u_x, tb.u_y,
			tb.animation_num);
	}

	// �`�悵�Ĉ�U����������o�[�W����
	void Draw2DGraphEX() {

		Draw2DGraphEXAfterNoInit();

		// �`�悵�����ƈ�U������
		tb.Init();
	}

	void Clear() {
		tb.Init();
	}
}





/*
// �ʏ�ݒ�
void TextureBord2DEX::SetNormalConfig(const char*file_name, const float&pos_x, const float &pos_y) {

	m_file_name = file_name;
	m_pos.x = pos_x;
	m_pos.y = pos_y;
}

// �ړ���]�g�k
void TextureBord2DEX::SetTransform(const D3DXVECTOR2&pos, const D3DXVECTOR2&scale, const float&angle) {
	m_pos = pos;
	m_scale = scale;
	m_angle = angle;
}
void TextureBord2DEX::SetTransform
   (const float & pos_x, const float & pos_y,
	const float & scale_x, const float & scale_y,
	const float & angle) {
	m_pos.x = pos_x;
	m_pos.y = pos_y;
	m_scale.x = scale_x;
	m_scale.y = scale_y;
	m_angle = angle;
}


// �t�@�C����
void TextureBord2DEX::SetFileName(const char*file_name) {
	m_file_name = file_name;
}
void TextureBord2DEX::SetFileName(const std::string &file_name) {
	m_file_name = file_name.c_str();
}

// �ʒu
void TextureBord2DEX::SetPostion(const D3DXVECTOR2&pos) {
	m_pos = pos;
}
void TextureBord2DEX::SetPostion(const float&pos_x, const float&pos_y) {
	m_pos.x = pos_x;
	m_pos.y = pos_y;
}

// �g�k
void TextureBord2DEX::SetScale(const D3DXVECTOR2&scale) {
	m_scale = scale;
}
void TextureBord2DEX::SetScale(const float&scale_x, const float&scale_y) {
	m_scale.x = scale_x;
	m_scale.y = scale_y;
}

// ��]
void TextureBord2DEX::SetAngle(const float &angle) {
	m_angle = angle;
}

void TextureBord2DEX::SetOfSetPos(const D3DXVECTOR2&ofset) {
	m_ofset = ofset;
}


void DrawUpdate() {

}*/