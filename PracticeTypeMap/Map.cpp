#include"D3D9.h"
#include"./Lib/Window/Window.h"
#include"./Lib/Texture/Texture.h"
#include"./Lib/Texture/TextureBoad2D.h"
#include"./Lib/Input/KeyBord.h"
#include"Map.h"
#include"oxdebugfont.h"



// 64�s�N�Z�� /* ��30 �c16 *//* 1088*/
// 128�s�N�Z��/* ��15 �c8 *//*1024*/

// �}�b�v�`�b�v�I�u�W�F�N�g�z�u

// �摜�ʒu�����߂�Ƃ�
// 1�V�[�g�ڂ̕K�v�ȏꏊ
// �`��ŕK�v�ȏꏊ,
// �V�[�g�̂ǂ�����for�����񂷂�
// ���[���h���W��ݒu����
// �^���I�ɓ���
// for�����񂷈ʒu�����߂�

// 2���̔w�i�ł�����
// �����蔻��͂��炵���������߂��Ă�����

int map[Map::MAP_SAET_NUM][Map::MAP_NUM_Y][Map::MAP_NUM_X] = {
{
{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,},
{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,},
{ 1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,},
{ 1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
},
{
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
},
{
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
},
{
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
},
{
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
},
};


// �R���X�g���N�^
Map::Map() {

	m_player_pos.x = ((WINDOW_W_F / 2) - 200.f);
	m_player_pos.y = (-WINDOW_H_F / 2);// �����͕\���Ƌt�̑���ɂȂ�̂ŁA-�ϊ� 

	m_move_pos.x = m_move_pos.y = 0.f;

	m_chip_pos.x = m_chip_pos.y = 0.f;

	// �`��͈͂����߂�
	m_draw_range_begin = MAP_NUM_Y;
	m_draw_range_end = 0;

	// ���I����
	//m_draw_map = new std::vector<std::vector<int>>;

	MapInit();
}

// �X�V
void Map::Update(){

	MapColider();
}


void Map::MapInit() {

	int map_up = 0;
	
	for (int z = 0; z < MAP_SAET_NUM; z++) {
	
		// �}�b�v���グ��
		map_up = MAP_NUM_Y * z;
	
		for (int y = 0; y < MAP_NUM_Y; y++) {
			for (int x = 0; x < MAP_NUM_X; x++) {
	
				// at(y + map_up).at(x)
				// �Q�Ƃɂ���\��,�ォ������B
				m_draw_map[y + map_up][x] = map[(MAP_SAET_NUM - 1)- z][y][x];
			}
		}
	}
}

// �`��
void Map::Draw(){
	
	MapDraw();
}

// �}�b�v�̕`��
void Map::MapDraw() {

	
	// �`��ʒu�̊J�n�n�_
	D3DXVECTOR2 start_pos(0,900);//y-50��̍���


	    // �O�i���邲�ƂɃ`�b�v��u��������
		m_draw_range_begin = GetChipPosCast(m_chip_pos.y) + MAP_NUM_Y;
		m_draw_range_end = GetChipPosCast(m_chip_pos.y);

		// �`��͈͂����߂�
		for (int y = m_draw_range_end; y < m_draw_range_begin; y++) {
			for (int x = 0; x < MAP_NUM_X; x++) {

				// �z��O�A�N�Z�X�͋������Ȃ�
				if (y < 0 || y>m_draw_range_begin) {
					y = 0;
				}
				 
				// ���̔z��`��
				if (m_draw_map[y][x] == 1) {
					
					Texture::Draw2D("renga.png", (float)(x * CHIP_SIZE) + start_pos.x,
						(float)(-y * CHIP_SIZE) + (INTERVAL_HEIGHT) + m_chip_pos.y + start_pos.y);	
				}
			}
		}
}



/*
�ǂ̂悤�Ȓn�`�ɑ΂���
�ǂ̂悤�ɏՓ˂�����
�ǂ��ɖ߂邩
*/

void Map::MapColider() {

	float Dummy = 0.f;

	int hsize = CHIP_SIZE / 2;

	
	// �����蔻��
	// 4�����ׂ�
	/*
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y + 1, &m_move_pos.x,&Dummy);
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y - 1, &m_move_pos.x,&Dummy);
	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y + 1, &m_move_pos.x, &Dummy);
	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y - 1, &m_move_pos.x, &Dummy);

	// �����ŉ��Z
	m_player_pos.x += m_move_pos.x;

	m_chip_pos.x += m_move_pos.x;

	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y - 1.f, &Dummy, &m_move_pos.y);
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y - 1.f, &Dummy, &m_move_pos.y);
	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y + 1.f, &Dummy, &m_move_pos.y);
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y + 1.f, &Dummy, &m_move_pos.y);
	

	// ���Z
	m_player_pos.y += m_move_pos.y;

	m_chip_pos.y += m_move_pos.y;

	// �ړ��x�N�g��������
	m_move_pos.x = m_move_pos.y = 0.f;
	*/

	
	Colision(m_player_pos.x, m_player_pos.y, &m_move_pos.x, &m_move_pos.y);

	// ���Z
	m_player_pos += m_move_pos;

	// �}�b�v����ɏグ��
	m_chip_pos.y += m_move_pos.y;

	m_move_pos.x = m_move_pos.y = 0.f;
	
}


// �ׂ����ʒu�܂œ����蔻���ݒ�ł���
void Map::MapHitCheck(float pos_x, float pos_y, float *move_x, float *move_y) {

	// �C���萔
	const int RETOUCH = 1;

	float after_x = pos_x + *move_x;
	float after_y = pos_y + *move_y;

	// �������Ă��Ȃ��Ȃ�
	if (GetChipParam(after_x, -after_y) != 1) {
		return;
	}

	// ��������͓������Ă��鎞�̏���

	// ���������Z�������W�l�ɕϊ�����


	// ���
	float up_pos = (float)((int)-after_y / CHIP_SIZE + RETOUCH) * CHIP_SIZE;
	// ����
	float down_pos = (float)((int)after_y / CHIP_SIZE) * CHIP_SIZE;
	// ����
	float left_pos = (float)((int)after_x / CHIP_SIZE + RETOUCH) * CHIP_SIZE;
	// �E��
	float right_pos = (float)((int)after_x / CHIP_SIZE) * CHIP_SIZE;

	// ���̎d�g�݂����

	// �E�ӂɓ������Ă����ꍇ
	if (*move_x > 0.f) {

		/* �ړ��ʂ�␳����
		�߂��Ăق����ʒu - ���ݒn = �u���b�N�O�܂ł̈ړ��� */
		*move_x = right_pos - pos_x + 1.f;
		return;

	}
	// ���ӂɓ������Ă����ꍇ
	if (*move_x < 0.f) {

		*move_x = left_pos - pos_x - 1.f;
		return;
	}

	// ��ӂɓ������Ă����ꍇ
	if (*move_y > 0.f) {

		*move_y = up_pos + pos_y - 1.f;
		return;
	}

	// ���ӂɓ������Ă����ꍇ
	if (*move_y < 0.f) {

		*move_y = down_pos - pos_y + 1.f;
		return;
	}

}



// ���ړ�
void Map::Colision(float &pos_x, float &pos_y, float *move_x, float *move_y) {

	// �C���萔
	const int RETOUCH = 1;

	// �ړ���̍��W������
	float after_x = pos_x + *move_x;
	float after_y = pos_y + *move_y;

	// �������}�b�v�`�b�v�̍��W������o��
	float chip_pos_x = 0;
	float chip_pos_y = 0;

	// ���ꂼ�ꔻ����s��

	/*
	Y����4���𒲂�
	X����4���𒲂ׂ�
	*/

	// ���݁A�ړ��ʑ����̂��蔲�����N�����Ă���
	float hsize = CHIP_SIZE / 2;

	if (*move_x >= 32.f) {
		*move_x = 32.f;
	}

	// Y����
	if (GetChipParam(after_x + hsize, -after_y + CHIP_SIZE) == 1 ||
		GetChipParam(after_x + CHIP_SIZE - hsize, -after_y + CHIP_SIZE)==1) {

		// �`�b�v�T�C�Y����o��
		chip_pos_y = (float)(int)(-after_y / CHIP_SIZE);
		//  �`�b�v�T�C�Y = ���݂̈ʒu + ��O�̃`�b�v
		pos_y = (-chip_pos_y * CHIP_SIZE) - CHIP_SIZE;// ���ꂪ����
	
		*move_y = 0.f;
	}

	
	// Y���V��
	if (GetChipParam(after_x +hsize, -after_y,4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE -hsize, -after_y,4) == 1) {

		// �`�b�v�T�C�Y����o��
		chip_pos_y = (float)(int)(-after_y / CHIP_SIZE);
		//  �`�b�v�T�C�Y = ���݂̈ʒu + ��O�̃`�b�v
		pos_y = (chip_pos_y * -CHIP_SIZE) - CHIP_SIZE;// ���ꂪ����

		// �ړ��x�N�g���Ȃ�
		*move_y = 0.f;
	}


	// X����
	if (GetChipParam(after_x ,-after_y+hsize,4) == 1 ||
		GetChipParam(after_x, -after_y+ CHIP_SIZE+hsize,4)==1) {// y�������ׂ�

		chip_pos_x = (float)((int)after_x / CHIP_SIZE + 1);// �ړ��オ�傫���̂ŕ␳
														   // �ʒu��߂�
		pos_x = (chip_pos_x * CHIP_SIZE_F);

		// �ړ��x�N�g�����Ȃ��ɂ���
		*move_x = 0.f;
	}

	// X���E
	if (GetChipParam(after_x + CHIP_SIZE, -after_y+hsize,4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE, -after_y + CHIP_SIZE + hsize,4)==1) {

		chip_pos_x = (float)((int)(after_x - CHIP_SIZE) / CHIP_SIZE);
		// �ʒu��߂�
		pos_x = (chip_pos_x * CHIP_SIZE_F) + CHIP_SIZE;

		// �ړ��x�N�g�����Ȃ��ɂ���
		*move_x = 0.f;
	}


	if (*move_x >= 32.f) {
		*move_x = 200;
	}

}



template<class T>
// �Z���ɕϊ�
int Map::GetChipPosCast(const T&pos) {
	return static_cast<int>(std::floor(pos/CHIP_SIZE));
}

// ���W����ꂽ��}�b�v�`�b�v�̈ʒu��Ԃ�
int Map::GetChipParam(const float &pos_x,const float&pos_y,const int&map_number) {
	
	// �}�b�v���W�ϊ�
	int px = GetChipPosCast(pos_x);
	int py = GetChipPosCast(pos_y);

	// �͈͊O�Ȃ�
	if (px < 0 || px >= MAP_NUM_X || py < 0 || py >= MAP_NUM_Y) {
		return 0;
	}
	
	return map[map_number][py][px];
}

// ����ʒu�Ƀu���b�N��u��
void Map::SetChipParam(const int&pos_x,const int&pos_y,const int &cell, const int&map_number) {

	map[map_number][pos_y][pos_x] = cell;
}


// �}�b�v�̃��[�v
void MapWrap() {

}

// �}�b�v�̃��Z�b�g
void MapResat() {

}







// �`��֌W
//for (int i = 0; i < MAP_SAET_NUM; i++) {
//for (int y = 0; y < MAP_NUM_Y; y++) {
//	for (int x = 0; x< MAP_NUM_X; x++){
//
//		if (map[0][y][x] == 1) {
//
//			// �u���b�N�������������Ȃ��Ƃ����Ȃ�
//			// �T�C�Y���ɉ摜��ς���
//			Texture::Draw2D("renga.png",(float)(x * CHIP_SIZE) + start_pos.x,
//				            (float)(y * CHIP_SIZE) + (INTERVAL_HEIGHT) + m_chip_pos.y);// �`�b�v�̈ʒu�����@�̈ʒu
//		}
//	}
//}
//}

/*
// �����蔻��J��

int hsize = CELL_SIZE / 2;

// ��
// ���ۂɉ��Z����Ă��Ȃ��̂�
// �ړ��x�N�g���͎��ۂɓ���Ȃ��ƁA�ړ����Ă��Ȃ����ƂɂȂ�̂Ŗ����ɓ���-1.f�ł��߂����l�������Ȃ�̂�
if (GetCellParam( m_player_pos.x + speed.x, -m_player_pos.y, 0) == 1) {

// �߂��l��I��
int px = ((int)m_player_pos.x + (int)speed.x) / CELL_SIZE + 1;
px *= CELL_SIZE;

// ���̒l�Ɩ߂������l����������߂������l�܂ł̈ړ��l���o��
speed.x = px - (m_player_pos.x);
}

// ����������
//MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y, &speed.x, &speed.y);

// ���Z
m_player_pos += speed;

speed.x = speed.y = 0.f;
*/


// MEMO
// 4������ׂ�֐����������������
// �]�v�Ɋ֐��ɂ���Ȃ��ׂɁA�ʒu���X�V���ꂽ��bool���g��

// �����蔻��

// 1�Z���͈̔͂œ����蔻���ݒ肵�Ă�����A
// 1�Z������΂��ē����蔻����s���Ă��܂�

// -�̋t�ϊ����ǂ��ɂ����Ȃ���΂����Ȃ�

//// ��
//if (GetCellParam(m_player_pos.x,-m_player_pos.y + 10.f,0) == 1) {
//
//	m_player_pos.y = (float)m_player_pos.y + CELL_SIZE_F;
//}
//
//// ��
//if (GetCellParam(m_player_pos.x,-m_player_pos.y - 10.f,0) == 1) {
//
//	m_player_pos.y = (float)m_player_pos.y - CELL_SIZE_F;
//}
//
//// �E
//if (GetCellParam(m_player_pos.x + 10.f,-m_player_pos.y,0) == 1) {
//
//	m_player_pos.x = (float)m_player_pos.x - CELL_SIZE_F;
//}

// �ړ��ʂ͌ォ��������

// 384.0��ڎw��
// 16.f���ړ����Ă���

//m_player_pos.x += 0.5f;// �����蔻��p


//if (-back_pos.y <= (-SCREEN_HEIGHT) * now_graph &&
//	FRACTION + (SCREEN_HEIGHT * now_graph) >= SCREEN_HEIGHT * now_graph) {
//
//	now_graph++;
//	next_graph = now_graph + 1;
//}


// �O�`��
// 50 - 1180
//if (-back_pos.y <= (screen_up) * now_graph) {
//	next_graph = now_graph + 1;
//}
//
//if (-back_pos.y <= (screen_up + FRACTION) * (next_graph + 1)) {
//	now_graph = next_graph + 1;
//}

//Texture::Draw2D(str[4], 0.f, back_pos.y - (float)FRACTION + (-SCREEN_HEIGHT*0));

/*
// �摜���傫���̂ł��ꂮ�炢�ɂȂ�
// 1���ڕ`��
Texture::Draw2D(str[4], 0.f,0.f + back_pos.y - (float)FRACTION);

// �Ō�łȂ��Ȃ�
if (str[GRAPH_NUM] != str[4]) {

// �O�`��
if (-back_pos.y <= -SCREEN_HEIGHT) {
// 2���ڕ`��
Texture::Draw2D(str[4], 0, (-SCREEN_HEIGHT - (float)FRACTION * 2) + back_pos.y);
}
else if (back_pos.y >= SCREEN_HEIGHT) {
// 2���ڕ`��
Texture::Draw2D(str[4], 0, (-SCREEN_HEIGHT - (float)FRACTION * 2) + back_pos.y);
}
}

// �摜�X�V(�����͊֐��ł킯��ׂ�)
// ���̕`��X�V�͈ʒu��߂��A�w�i��������ւ���Ƃ�������

if (-back_pos.y <= -SCREEN_HEIGHT) {

p_pos.y = -FRACTION;
back_pos.y = -FRACTION;

now_graph++;
if (now_graph == 3) {
now_graph = 0;
}
}
else if (back_pos.y >= SCREEN_HEIGHT) {
p_pos.y = -FRACTION;
back_pos.y = -FRACTION;
}
*/



	/*
	const int GRAPH_NUM = 3;
	const int CHIP_SIZE = 32;

	const int CHIP_NUM_X = 20;
	const int CHIP_NUM_Y = 15;

	struct Graph {
		int player;     // ���@
		int background[GRAPH_NUM]; // �w�i
		int chip[3];

		Graph() {
			player = 0;

			for (int i = 0; i < GRAPH_NUM; i++) {
				background[i] = 0;
			}
		}
	};

	void Init();
	void Draw();

	const int SCREEN_HEIGHT = 640;
	const int SCREEN_WIDTH = 480;


	int map[CHIP_NUM_Y][CHIP_NUM_X] = {

	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,2,2,2,2,2,2,2,1,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,2,2,2,2,2,2,2,1,0,0,0,0,0,1 },
	{ 1,0,0,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1 },
	{ 1,2,2,0,1,0,2,2,2,1,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,1,0,2,2,2,1,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,0,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,1,1,1,1,1,1,1,1,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,0,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,1,2,2,2,0,1,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,1,2,2,2,0,1,0,0,2,2,1 },
	{ 1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,2,2,1 },
	{ 1,0,0,0,0,1,2,2,2,2,2,2,2,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,1,2,2,2,2,2,2,2,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1 },
	};


	int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {


		// ������
		if (DirectXInit() == false) {
			return-1;
		}

		// �E�B���h�E�T�C�Y
		//SetWindowSize(1020, 1080);

		// �O���[�o���ϐ�
		D3DXVECTOR2 p_pos;
		Graph gra;

		p_pos.x = p_pos.y = 0.f;
		p_pos.x = 3.f;
		p_pos.y = 3.f;

		// �w�i
		D3DXVECTOR2 back_move;// �w�i�ړ���

		back_move.x = back_move.y = 0;

		float scroll_speed = 3;         // �X�N���[���X�s�[�h
		float width_speed = 3;

		const char *str[3] = {
			"�j�[�A2.jpg",
			"�j�[�APC�ǎ�.jpg",
			"�t�@���^�W�[�n��.jpg",
		};

		// ���@

		//Texture::Load("Boss_spider_attack1.png");
		Texture::Load("Boss_spider_attack1_resizse.png");
		Texture::Load("Title.png");

		int graph_num = 0;
		int timer = 0;

		while (ProcessMessage()==true) {

			// �G�X�P�[�v�L�[
			if (GetKeyState(VK_ESCAPE) & 0x8000) {
				break;
			}

			if (DrawStart() == true) {

				timer++;

				if (timer > 5) {
					graph_num++;
					timer = 0;
				}
				else if (graph_num >= 64) {
					graph_num=0;
				}

				// ���@37000 �c1024
				// ��516 �c30
				// �`��
				//Texture::Draw2D("Boss_spider_attack1.png", 1920/2,1080/2, -23000, 600, 0.5f, 0.5f, true, 46, 1, graph_num);

				// 46
				// 62

				// �� 32768
				// �c 1024

				// 8192���ƍr��Ȃ�

				Texture::Draw2D("Boss_spider_attack1_resizse.png", 1920 / 2, 1080 / 2, -32068, 1, 0.5f, 0.5f, true, 64, 1, graph_num);
				//Texture::Draw2D("Title.png", 1920 / 2, (1080 / 2)+500, -7600, 1000, 0.5f, 0.5f, true, 16, 1, graph_num);

				DrawEnd();
			}
		}
	}
	*/


	// ���̈ʒu���傫���ꍇ��
	//if (back_pos.y > -SCREEN_HEIGHT * now_postion) {
	//	now_postion++;
	//}
	//// ���̈ʒu��菬�����ꍇ��
	//else if (back_pos.y < -SCREEN_HEIGHT * now_postion &&
	//	now_postion!=0) {
	//	now_postion--;
	//}

	//now_postion = 0;

	// �w�i���ړ�������
	//for (int i = 0; i < DRAW_GRAPH_MAX; i++) {
	//
	//	Texture::Draw2D(str[3], 0, (-SCREEN_HEIGHT * now_postion) + back_pos.y, 1, 1, 0.f, 0.f);
	//
	//	now_postion++;
	//}
