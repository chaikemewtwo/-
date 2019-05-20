#include"SetRenderStateFile.h"



void SetRenderStateConfig() {
	
	// �V�F�[�h���[�h:�O���f�[�V����
	dev->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	// �J�����O���[�h����
	dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	// Z�o�b�t�@�I�t
	dev->SetRenderState(D3DRS_ZENABLE, FALSE);
	dev->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	dev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	// ���C�goff
	dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �X�؂������I��
	dev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	// �A���t�@�`�����l���I��
	dev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// �ʏ�u�����f�B���O
	dev->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//dev->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	// �A���t�@�e�X�g
	dev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	dev->SetRenderState(D3DRS_ALPHAREF, 0x0000000);
	dev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//// �e�N�X�`�����u�����h
	//dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//dev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//dev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// tu tv�������Ă��邩������Ȃ�
	// ���[�v���N�����v�ɕς���
}