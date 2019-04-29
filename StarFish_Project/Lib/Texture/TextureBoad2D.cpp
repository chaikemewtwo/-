#include"../D3D/D3D9.h"
#include"../Texture/TextureBoad2D.h"
#include"./Texture.h"
#include"../UV/UV.h"


struct CUSTOM_VERTEX
{
	// 頂点座標
	float x;
	float y;
	float z;
	// 除算数
	float rhw;
	// テクスチャ座標
	float tu;
	float tv;
};


// Draw2Dの使い方

/*
引数1 ファイル名
引数2,3 位置 
引数4,5 大きさ
引数6 角度
引数7,8 オフセット位置x,y(どこから描画を始めるか)
引数9 分割総数
引数10 分割する数、横 
引数11 分割する数、縦
引数12 分割した現在の画像(アニメーションをするならここを動かす)
*/

/*
アニメーションするならまず分割画像を分割する

例
16枚の統合画像を分割するとする
横4縦2で分割するとする

引数9で16の整数を入れる
引数10で4を入れる
引数11で2を入れる
引数12は整数型で現在の画像を指定する

引数12(graph_num)の仕組み(アニメーションする場合は通常見なくて大丈夫です)
横に走査して描画していく。
横の最大数まで来たら一段下に下がる。
*/


namespace Texture {

	void Draw2D(const char*file_name,float x,float y, float scale_w,float scale_h,float angle,float cx,float cy,bool uv_cut,int u_axis,int v_axis,int graph_num) {
		
		TEXTURE_DATA *tex_d = &tex_list[file_name];

		const float x1 = -cx;
		const float x2 = 1.f - cx;
		const float y1 = -cy;
		const float y2 = 1.f - cy;

		// UVの分割
		UV uv(u_axis, v_axis);

		// uvカットがオンならば
		if (uv_cut == true) {
			uv.ToTheRightDivGraph(graph_num);
		}
		
		// 頂点バッファを参照で受け取り
		D3DXVECTOR2 *up_left = &uv.GetUvUpLeftBuffer();
		D3DXVECTOR2 *up_right = &uv.GetUvUpRightBuffer();
		D3DXVECTOR2 *down_left = &uv.GetUvDownLeftBuffer();
		D3DXVECTOR2 *down_right = &uv.GetUvDownRightBuffer();
		
		// VERTEX3Dの初期化
		CUSTOM_VERTEX cv[] =
		{
		{ x1,y1,0.0f,1.0f,up_left->x,up_left->y },       // 左上
		{ x2,y1,0.0f,1.0f,up_right->x,up_right->y },     // 右上
		{ x2,y2,0.0f,1.0f,down_right->x,down_right->y }, // 右下
		{ x1,y2,0.0f,1.0f,down_left->x,down_left->y },   // 左下
		};

		// ワールド座標変換系
		D3DXMATRIX mat_world, mat_trans, mat_scale;
		// ワールド変換回転。
		D3DXMATRIX mat_rotz;

		D3DXMatrixIdentity(&mat_world);
		D3DXMatrixIdentity(&mat_rotz);
		D3DXMatrixIdentity(&mat_trans);
		D3DXMatrixIdentity(&mat_scale);

		D3DXMatrixTranslation(&mat_trans, x, y, 0.f);
		D3DXMatrixScaling(&mat_scale, tex_d->Width * scale_w, tex_d->Height * scale_h, 0.0f);
		D3DXMatrixRotationZ(&mat_rotz, D3DXToRadian(angle));

		// 拡縮 * 回転 * 移動
		mat_world = mat_scale * mat_rotz * mat_trans;

		D3DXVec3TransformCoordArray((D3DXVECTOR3*)cv, sizeof(CUSTOM_VERTEX), (D3DXVECTOR3*)cv, sizeof(CUSTOM_VERTEX), &mat_world, std::size(cv));

		// VERTEX3Dの構造情報をDirectXへ通知。										  
		dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		// デバイスにそのまま渡すことができる。
		dev->SetTexture(0, tex_list[file_name]);// これはテクスチャの指定、ポインタを渡して確認する。
												// 元はtex_list[file_name]	// 0はテクスチャステージ番号
		
		dev->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			cv,// cv カスタムバーテックスのポインタ
			sizeof(CUSTOM_VERTEX)
		);
	}

	// 描画関係
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
