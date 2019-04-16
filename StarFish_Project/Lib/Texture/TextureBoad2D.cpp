#include"../D3D/D3D9.h"
#include"../Texture/TextureBoad2D.h"
#include"./Texture.h"
#include"../UV/UV.h"


struct CUSTOM_VERTEX
{
	// ���_���W
	float x;
	float y;
	float z;
	// ���Z��
	float rhw;
	// �e�N�X�`�����W
	float tu;
	float tv;
};


namespace Texture {

	void Draw2D(const char*file_name,float x,float y, float scale_w,float scale_h,float angle,float cx,float cy,bool uv_cut,int u_axis,int v_axis,int graph_num) {
		
		TEXTURE_DATA *tex_d = &tex_list[file_name];

		const float x1 = -cx;
		const float x2 = 1.f - cx;
		const float y1 = -cy;
		const float y2 = 1.f - cy;

		// UV�̕���
		UV uv(u_axis, v_axis);

		// uv�J�b�g���I���Ȃ��
		if (uv_cut == true) {
			uv.ToTheRightDivGraph(graph_num);
		}
		
		// ���_�o�b�t�@���Q�ƂŎ󂯎��
		D3DXVECTOR2 *up_left = &uv.GetUvUpLeftBuffer();
		D3DXVECTOR2 *up_right = &uv.GetUvUpRightBuffer();
		D3DXVECTOR2 *down_left = &uv.GetUvDownLeftBuffer();
		D3DXVECTOR2 *down_right = &uv.GetUvDownRightBuffer();
		
		// VERTEX3D�̏�����
		CUSTOM_VERTEX cv[] =
		{
		{ x1,y1,0.0f,1.0f,up_left->x,up_left->y },       // ����
		{ x2,y1,0.0f,1.0f,up_right->x,up_right->y },     // �E��
		{ x2,y2,0.0f,1.0f,down_right->x,down_right->y }, // �E��
		{ x1,y2,0.0f,1.0f,down_left->x,down_left->y },   // ����
		};

		// ���[���h���W�ϊ��n
		D3DXMATRIX mat_world, mat_trans, mat_scale;
		// ���[���h�ϊ���]�B
		D3DXMATRIX mat_rotz;

		D3DXMatrixIdentity(&mat_world);
		D3DXMatrixIdentity(&mat_rotz);
		D3DXMatrixIdentity(&mat_trans);
		D3DXMatrixIdentity(&mat_scale);

		D3DXMatrixTranslation(&mat_trans, x, y, 0.f);
		D3DXMatrixScaling(&mat_scale, tex_d->Width + scale_w, tex_d->Height + scale_h, 0.0f);
		D3DXMatrixRotationZ(&mat_rotz, D3DXToRadian(angle));

		// �g�k * ��] * �ړ�
		mat_world = mat_scale * mat_rotz * mat_trans;

		D3DXVec3TransformCoordArray((D3DXVECTOR3*)cv, sizeof(CUSTOM_VERTEX), (D3DXVECTOR3*)cv, sizeof(CUSTOM_VERTEX), &mat_world, std::size(cv));

		// VERTEX3D�̍\������DirectX�֒ʒm�B										  
		dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		// �f�o�C�X�ɂ��̂܂ܓn�����Ƃ��ł���B
		dev->SetTexture(0, tex_list[file_name]);// ����̓e�N�X�`���̎w��A�|�C���^��n���Ċm�F����B
												// ����tex_list[file_name]	// 0�̓e�N�X�`���X�e�[�W�ԍ�
		
		dev->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			cv,// cv �J�X�^���o�[�e�b�N�X�̃|�C���^
			sizeof(CUSTOM_VERTEX)
		);
	}

	// �`��֌W
	void Draw2DGraph(const char*file_name, const float&pos_x, const float&pos_y) {
		Draw2D(file_name, pos_x, pos_y);
	}

	void Draw2DTransGraph(const char*file_name, const float&pos_x, const float&pos_y,const float &scale_x,const float&scale_y,const float&angle) {
		Draw2D(file_name, pos_x, pos_x, pos_y, scale_x, scale_y, angle);
	}

	void Draw2DRotaGraph(const char*file_name, const float&pos_x, const float &pos_y, const float&angle) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, angle, 0.5f, 0.5f);
	}

	void Draw2DAnimationGraph(const char*file_name, const float&pos_x, const float&pos_y, const int &u_cut_num, const int&v_cut_num,const int&anim_num) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, 0.f, 0.f, 0.f, true, u_cut_num, v_cut_num, anim_num);
	}

	void Draw2DRotaAnimation(const char*file_name, const float&pos_x, const float&pos_y, const float &angle, const int &u_cut_num, const int&v_cut_num, const int&anim_num) {
		Draw2D(file_name, pos_x, pos_y, 1.f, 1.f, angle, 0.f, 0.f, true, u_cut_num, v_cut_num, anim_num);
	}
}