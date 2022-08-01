#include "DxLib.h"
#include <math.h>

#define SHOT 20

struct Character
{
	int x, y, w, h, Sw, Sh;
	int muki, graph, damageGraph, damageCounter;
	bool damageFlag;
};

struct Bullet
{
	double x, y, Sx, Sy;
	int w, h;
	int flag, graph, counter;
};

void mainExec() {

	int ShotGraph, ShotBFlag;
	int ShotX[SHOT], ShotY[SHOT], ShotFlag[SHOT];

	// �{�[���N�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	Character Ball;
	Ball.x = 288;
	Ball.y = 400;
	Ball.muki = 0;
	Ball.graph = LoadGraph("Ball.png");
	Ball.damageGraph = 0;
	Ball.damageFlag = FALSE;

	// �l�p�N�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	Character Sikaku;
	Sikaku.x = 0;
	Sikaku.y = 50;
	Sikaku.muki = 1;
	Sikaku.graph = LoadGraph("Sikaku.png");
	Sikaku.damageGraph = LoadGraph("SikakuDam.png");
	Sikaku.damageFlag = FALSE;

	Bullet Tama;
	Tama.graph = LoadGraph("EShot.png");
	Tama.counter = 0;
	Tama.flag = FALSE;


	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����O�������Ă���
	for (int i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	// �e�̃O���t�B�b�N���������Ƀ��[�h
	ShotGraph = LoadGraph("Shot.png");

	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO(�����ꂢ�Ȃ�)����
	ShotBFlag = 0;

	// �l�p�N�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(Sikaku.graph, &Sikaku.w, &Sikaku.h);

	// �{�[���N�ƒe�̉摜�̃T�C�Y�𓾂�
	GetGraphSize(Ball.graph, &Ball.w, &Ball.h);

	// �e�̃O���t�B�b�N�̃T�C�Y������
	GetGraphSize(ShotGraph, &Sikaku.Sw, &Sikaku.Sh);

	GetGraphSize(ShotGraph, &Ball.Sw, &Ball.Sh);

	// �G�̒e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(Tama.graph, &Tama.w, &Tama.h);

	// �ړ����[�`��
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		// �{�[���N�̑��샋�[�`��
		{
			// ���L�[�������Ă�����{�[���N����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_UP) == 1) Ball.y -= 3;

			// ���L�[�������Ă�����{�[���N�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) Ball.y += 3;

			// ���L�[�������Ă�����{�[���N�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) Ball.x -= 3;

			// ���L�[�������Ă�����{�[���N���E�Ɉړ�������
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) Ball.x += 3;

			// �X�y�[�X�L�[���������ꍇ�͏����𕪊�
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ����O��������e�𔭎�
				if (ShotBFlag == 0)
				{
					// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
					for (int i = 0; i < SHOT; i++)
					{
						// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
						if (ShotFlag[i] == 0)
						{
							// �ei�̈ʒu���Z�b�g�A�ʒu�̓{�[���N�̒��S�ɂ���
							ShotX[i] = (Ball.w - Ball.Sw) / 2 + Ball.x;
							ShotY[i] = (Ball.h - Ball.Sh) / 2 + Ball.y;

							// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
							ShotFlag[i] = 1;

							// ��e���o�����̂Œe���o�����[�v���甲���܂�
							break;
						}
					}
				}

				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂP(������Ă���)����
				ShotBFlag = 1;
			}
			else
			{
				// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO(������Ă��Ȃ�)����
				ShotBFlag = 0;
			}

			// �{�[���N����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (Ball.x < 0) Ball.x = 0;

			// �{�[���N����ʉE�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (Ball.x > 640 - 64) Ball.x = 640 - 64;

			// �{�[���N����ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (Ball.y < 0) Ball.y = 0;

			// �{�[���N����ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (Ball.y > 480 - 64) Ball.y = 480 - 64;

			// �{�[���N��`��
			DrawGraph(Ball.x, Ball.y, Ball.graph, FALSE);
		}

		// �e�̐������e�𓮂����������J��Ԃ�
		for (int i = 0; i < SHOT; i++)
		{
			// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e���P(���݂���)�̏ꍇ�̂ݍs�� )
			if (ShotFlag[i] == 1)
			{
				// �ei���P�U�h�b�g��Ɉړ�������
				ShotY[i] -= 16;

				// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ��ɂO(���݂��Ȃ�)��������
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				// ��ʂɒei��`�悷��
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, FALSE);
			}
		}

		// �l�p�N�̈ړ����[�`��
		{
			// ���c�߂Ă��邩�ǂ����ŏ����𕪊�
			if (Sikaku.damageFlag)
			{
				// ���c�߂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
				DrawGraph(Sikaku.x, Sikaku.y, Sikaku.damageGraph, FALSE);

				// ���c�߂Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
				Sikaku.damageCounter++;

				// �������c�ߏ��߂� �R�O �t���[���o�߂��Ă������̘c�񂾏�Ԃ���
				// ���ɖ߂��Ă�����
				if (Sikaku.damageCounter == 30)
				{
					// �w�c��ł��Ȃ��x��\���O����
					Sikaku.damageFlag = FALSE;
				}
			}
			else
			{
				// �c��ł��Ȃ��ꍇ�͍��܂Œʂ�̏���

				// �l�p�N�̍��W���ړ����Ă�������Ɉړ�����
				if (Sikaku.muki == 1) Sikaku.x += 3;
				if (Sikaku.muki == 0) Sikaku.x -= 3;

				// �l�p�N����ʉE�[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (Sikaku.x > 576)
				{
					Sikaku.x = 576;
					Sikaku.muki = 0;
				}

				// �l�p�N����ʍ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (Sikaku.x < 0)
				{
					Sikaku.x = 0;
					Sikaku.muki = 1;
				}

				// �l�p�N��`��
				DrawGraph(Sikaku.x, Sikaku.y, Sikaku.graph, FALSE);

				// �e�����^�C�~���O���v�����邽�߂̃J�E���^�[�ɂP�𑫂�
				Tama.counter++;

				// �����J�E���^�[�ϐ����U�O�������ꍇ�͒e�����������s��
				if (Tama.counter == 60)
				{
					// �������ɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
					if (Tama.flag)
					{
						// �e�̔��ˈʒu��ݒ肷��
						Tama.x = Sikaku.x + Sikaku.w / 2 - Tama.w / 2;
						Tama.y = Sikaku.y + Sikaku.h / 2 - Tama.h / 2;

						// �e�̈ړ����x��ݒ肷��
						{
							double sb, sbx, sby, bx, by, sx, sy;

							sx = Tama.x + Tama.w / 2;
							sy = Tama.y + Tama.h / 2;

							bx = Ball.x + Ball.w / 2;
							by = Ball.y + Ball.h / 2;

							sbx = bx - sx;
							sby = by - sy;

							// �����������߂�̂ɕW���֐��� sqrt ���g���A
							// ������g���ɂ� math.h ���C���N���[�h����K�v������
							sb = sqrt(sbx * sbx + sby * sby);

							// �P�t���[��������W�h�b�g�ړ�����悤�ɂ���
							Tama.Sx = sbx / sb * 8;
							Tama.Sy = sby / sb * 8;
						}

						// �e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
						Tama.flag = TRUE;
					}

					// �e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
					Tama.counter = 0;
				}
			}
		}

		// �G�̒e�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
		if (Tama.flag)
		{
			// �e���ړ�������
			Tama.x += Tama.Sx;
			Tama.y += Tama.Sy;

			// �����e����ʂ���͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
			// ��\���O�ɂ���
			if (Tama.y > 480 || Tama.y < 0 ||
				Tama.x > 640 || Tama.x < 0) Tama.flag = FALSE;

			// ��ʂɕ`�悷��( ETamaGraph : �G�̒e�̃O���t�B�b�N�̃n���h�� )
			DrawGraph((int)Tama.x, (int)Tama.y, Tama.graph, FALSE);
		}

		// �e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
		for (int i = 0; i < SHOT; i++)
		{
			// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
			if (ShotFlag[i] == 1)
			{
				// �l�p�N�Ƃ̓����蔻��
				if (((ShotX[i] > Sikaku.x && ShotX[i] < Sikaku.x + Sikaku.w) ||
					(Sikaku.x > ShotX[i] && Sikaku.x < ShotX[i] + Sikaku.Sw)) &&
					((ShotY[i] > Sikaku.y && ShotY[i] < Sikaku.y + Sikaku.h) ||
						(Sikaku.y > ShotY[i] && Sikaku.y < ShotY[i] + Sikaku.Sh)))
				{
					// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					ShotFlag[i] = 0;

					// �l�p�N�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\���P����
					Sikaku.damageFlag = TRUE;

					// �l�p�N�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
					Sikaku.damageCounter = 0;
				}
			}
		}

		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
}

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	mainExec();


	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}

