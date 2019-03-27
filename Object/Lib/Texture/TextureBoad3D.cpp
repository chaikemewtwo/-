#include"../Texture/TextureBoad3D.h"
#include"../Texture/Texture.h"
#include"../D3D/D3D9.h"
#include"../UV/UV.h"


// �|���S���p�x���t�ɂȂ��Ă��邩��(�|���S���`�悩�I�t�Z�b�g��)
// �����������ꍇ�͍\���̂ɂ������������B
namespace Texture {

	struct Vtx {
		D3DXVECTOR3 pos;
		DWORD color;
		D3DXVECTOR2 uv;
	};

	void Draw3D(const char*file_name, const D3DXMATRIX &mat_world,const float &cx,const float &cy,const bool &cull_none,bool uv_cut,int u_axis,int v_axis,int graph_num) {

		// true�Ȃ�w�ʃJ�����O���[�h����
		dev->SetRenderState(D3DRS_CULLMODE, cull_none ? D3DCULL_NONE : D3DCULL_CCW);

		// ���C�g
		dev->SetRenderState(D3DRS_LIGHTING, NULL);

		// 0.5f�Œ��S�ɂ���B
		float x1 = cx;
		float x2 = cx - 1.f;
		float y1 = cy;
		float y2 = cy - 1.f;

		// UV�؂���

		UV uv(u_axis, v_axis);

		if (uv_cut == true) {
			uv.ToTheRightDivGraph(graph_num);
		}

		D3DXVECTOR2 *up_left = &uv.GetUvUpLeftBuffer();
		D3DXVECTOR2 *up_right = &uv.GetUvUpRightBuffer();
		D3DXVECTOR2 *down_left = &uv.GetUvDownLeftBuffer();
		D3DXVECTOR2 *down_right = &uv.GetUvDownRightBuffer();

		// �g���C�A���O�����X�g
		Vtx sf[6] =
		{
		{ { x1,y1,0 },D3DXCOLOR(255,255,255,1),{ up_left->x,up_left->y } }, 
		{ { x2,y1,0 },D3DXCOLOR(255,255,255,1),{ up_right->x,up_right->y } },
		{ { x1,y2,0 },D3DXCOLOR(255,255,255,1),{ down_left->x,down_left->y } },
		{ { x2,y1,0 },D3DXCOLOR(255,255,255,1),{ up_right->x,up_right->y } },
		{ { x2,y2,0 },D3DXCOLOR(255,255,255,1),{ down_right->x,down_right->y } },
		{ { x1,y2,0 },D3DXCOLOR(255,255,255,1),{ down_left->x,down_left->y } },
		};

		D3DMATERIAL9 mat = {
		{ 0,0,0,(0xff00 >> 24) / 255.f, },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		0xffff0,
		0
		};
		// ���_�ɍs����̈ړ���g�k�Ȃǂ�z��ɑ������B
		//D3DXVec3TransformCoordArray

		// �e�N�X�`�����J���[�̐F�œ��ߏ�������
		dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		dev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		dev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		dev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// �}�e���A��
		dev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		dev->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
		dev->SetMaterial(&mat);


		dev->SetTransform(D3DTS_WORLD, &mat_world);
		dev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE);

		if (file_name!=NULL) {
			dev->SetTexture(0, tex_list[file_name].Texture);
		}
		dev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, sf, sizeof(Vtx));
	}


	// Transform�̃f�t�H�R���X�g���N�^
	Texture::Transform::Transform() {
		move_x = 0.f;
		move_y = 0.f;
		move_z = 0.f;
		angle_x = 0.f;
		angle_y = 0.f;
		angle_z = 0.f;
		scale_x = 0.f;
		scale_y = 0.f;
		scale_z = 0.f;
	}

	Texture::Transform::Transform(float move_x, float move_y, float move_z,
		float angle_x, float angle_y, float angle_z,
		float scale_x, float scale_y, float scale_z) {

		this->move_x = move_x;
		this->move_y = move_y;
		this->move_z = move_z;
		this->angle_x = angle_x;
		this->angle_y = angle_y;
		this->angle_z = angle_z;
		this->scale_x = scale_x;
		this->scale_y = scale_y;
		this->scale_z = scale_z;
	}


	// �|���S���ƃs�[�X�̃}�g���b�N�X�v�Z
	D3DXMATRIX Make3DMatrix(Texture::Transform &ts) {

		// ���[���h���W�ϊ��n
		D3DXMATRIX mat_world, mat_rot, mat_trans, mat_scale;

		// ���[���h�ϊ���]�B
		D3DXMATRIX mat_rotx, mat_roty, mat_rotz;

		// ������
		D3DXMatrixIdentity(&mat_world);
		D3DXMatrixIdentity(&mat_rot);
		D3DXMatrixIdentity(&mat_trans);
		D3DXMatrixIdentity(&mat_scale);

		// �}�g���b�N�X�v�Z
		{
			// �ړ�
			D3DXMatrixTranslation(&mat_trans, ts.move_x, ts.move_y, ts.move_z);

			// ��]���v�Z
			D3DXMatrixRotationX(&mat_rotx, D3DXToRadian(ts.angle_x));
			D3DXMatrixRotationY(&mat_roty, D3DXToRadian(ts.angle_y));
			D3DXMatrixRotationZ(&mat_rotz, D3DXToRadian(ts.angle_z));

			// ��]�̊|���Z�B
			D3DXMatrixMultiply(&mat_rot, &mat_rot, &mat_rotx);
			D3DXMatrixMultiply(&mat_rot, &mat_rot, &mat_roty);
			D3DXMatrixMultiply(&mat_rot, &mat_rot, &mat_rotz);

			// �g��
			D3DXMatrixScaling(&mat_scale, ts.scale_x, ts.scale_y, ts.scale_z);

			// �g�k * ��] * �ړ�
			mat_world = mat_scale * mat_rot * mat_trans;
		}

		return mat_world;
	}

	// ����
	Texture::Transform DirRotationTransform(Dir dir, Texture::Transform&ts) {

		
		switch (dir) {

		case NORTH:
			ts.angle_x = 180.f;
			ts.angle_z = 180.f;
			break;

		case SOUTH:
			break;

		case EAST:
			ts.angle_x = 180;
			ts.angle_y = 90;
			ts.angle_z = 180;
			break;

		case WEST:
			ts.angle_x = -180;
			ts.angle_y = -90;
			ts.angle_z = -180;
			break;

		default:
			ts.angle_x = -90;
			break;
		}

		return ts;
	}
		/*
		switch (dir) {

		case NORTH:
			break;

		case SOUTH:
			ts.angle_y = 180.f;
			break;

		case EAST:
			ts.angle_y = -90;
			break;

		case WEST:
			ts.angle_y = 90;
			break;

		default:
			ts.angle_x = 90;
			break;
		}

		return ts;
	}*/
};


/*

void Draw3DFan(const char*file_name, const D3DXMATRIX &mat_world, float cx, float cy)
{
// �����猩����B
dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
// ���C�g
dev->SetRenderState(D3DRS_LIGHTING, NULL);

struct Vtx {
D3DXVECTOR3 pos;
DWORD color;
D3DXVECTOR2 uv;
};

// 0.5f�Œ��S�ɂ���B

float x1 = cx;
float x2 = cx - 1.f;
float y1 = cy;
float y2 = cy - 1.f;

Vtx sf[4] =
{
{ { x1,y1,0 },D3DXCOLOR(255,255,255,255),{ 0,0 } },
{ { x2,y1,0 },D3DXCOLOR(255,255,255,255),{ 1,0 } },
{ { x2,y2,0 },D3DXCOLOR(255,255,255,255),{ 1,1 } },
{ { x1,y2,0 },D3DXCOLOR(255,255,255,255),{ 0,1 } }
};

D3DMATERIAL9 mat = {
{ 0,0,0,(0xff00 >> 24) / 255.f, },
{ 0,0,0,0 },
{ 0,0,0,0 },
0xffff0,
0
};
// ���_�ɍs����̈ړ���g�k�Ȃǂ�z��ɑ������B
//D3DXVec3TransformCoordArray


dev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
dev->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
dev->SetMaterial(&mat);

dev->SetTransform(D3DTS_WORLD, &mat_world);
dev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE);
dev->SetTexture(0, tex_list[file_name].Texture);
dev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, sf, sizeof(Vtx));
}
*/

// Make3DMatrix�ȂǂŊO���̊֐��ōs��v�Z���āA�l���A�点��B
// Draw3DFan("�t�@�C����",D3DXMatrix*piece_mtx);// D3DXMatrix�͂��łɍs��v�Z���Ă�����́B
// piece_mtx����]������}�g���b�N�X




/*
 D3DXMatrix�̓|���S���̉�]�s��
 piece_mtx�̓s�[�X�̉�]�s��
 �܂�O���Ōv�Z
 uv�̃N���X�͏��������������B(D3DXVECTOR2)
 uv��13����1�Ɏ��߂�B
 1,1,2.5,2.5,1,1,1,1,1,1,1,1,1
 uv��4���_
 uv�N���X�̃R���X�g���N�^�ŉς�uv��ς�����悤�ɂ���B2.5�ȂǁB
*/





/*
class UV{

public:
D3DXVECTOR2 rt,rb;

uv() : rt{// uv�̃f�t�H���g�R���X�g���N�^

}


*/

// D3DXMatirx�̔z���10����Ēu���B
// �����������Ă�����

