#include"SetRenderStateFile.h"



void SetRenderStateConfig() {
	
	// �V�F�[�h���[�h:�O���f�[�V����
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	// �J�����O���[�h����
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	// Z�o�b�t�@�I�t
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ZENABLE, FALSE);
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	// ���C�goff
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �X�؂������I��
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	// �A���t�@�`�����l���I��
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// �ʏ�u�����f�B���O
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	// �A���t�@�e�X�g
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHAREF, 0x0000000);
	Graphics::GetLpDirect3DDevice9()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//// �e�N�X�`�����u�����h
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//Graphics::GetLpDirect3DDevice9()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// tu tv�������Ă��邩������Ȃ�
	// ���[�v���N�����v�ɕς���
}