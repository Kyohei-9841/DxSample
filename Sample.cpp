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

	// ボール君のグラフィックをメモリにロード＆表示座標をセット
	Character Ball;
	Ball.x = 288;
	Ball.y = 400;
	Ball.muki = 0;
	Ball.graph = LoadGraph("Ball.png");
	Ball.damageGraph = 0;
	Ball.damageFlag = FALSE;

	// 四角君のグラフィックをメモリにロード＆表示座標をセット
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


	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味する０を代入しておく
	for (int i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	// 弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("Shot.png");

	// ショットボタンが前のフレームで押されたかどうかを保存する変数に０(押されいない)を代入
	ShotBFlag = 0;

	// 四角君のグラフィックのサイズを得る
	GetGraphSize(Sikaku.graph, &Sikaku.w, &Sikaku.h);

	// ボール君と弾の画像のサイズを得る
	GetGraphSize(Ball.graph, &Ball.w, &Ball.h);

	// 弾のグラフィックのサイズをえる
	GetGraphSize(ShotGraph, &Sikaku.Sw, &Sikaku.Sh);

	GetGraphSize(ShotGraph, &Ball.Sw, &Ball.Sh);

	// 敵の弾のグラフィックのサイズを得る
	GetGraphSize(Tama.graph, &Tama.w, &Tama.h);

	// 移動ルーチン
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		// ボール君の操作ルーチン
		{
			// ↑キーを押していたらボール君を上に移動させる
			if (CheckHitKey(KEY_INPUT_UP) == 1) Ball.y -= 3;

			// ↓キーを押していたらボール君を下に移動させる
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) Ball.y += 3;

			// ←キーを押していたらボール君を左に移動させる
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) Ball.x -= 3;

			// →キーを押していたらボール君を右に移動させる
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) Ball.x += 3;

			// スペースキーを押した場合は処理を分岐
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				// 前フレームでショットボタンを押したかが保存されている変数が０だったら弾を発射
				if (ShotBFlag == 0)
				{
					// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
					for (int i = 0; i < SHOT; i++)
					{
						// 弾iが画面上にでていない場合はその弾を画面に出す
						if (ShotFlag[i] == 0)
						{
							// 弾iの位置をセット、位置はボール君の中心にする
							ShotX[i] = (Ball.w - Ball.Sw) / 2 + Ball.x;
							ShotY[i] = (Ball.h - Ball.Sh) / 2 + Ball.y;

							// 弾iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
							ShotFlag[i] = 1;

							// 一つ弾を出したので弾を出すループから抜けます
							break;
						}
					}
				}

				// 前フレームでショットボタンを押されていたかを保存する変数に１(おされていた)を代入
				ShotBFlag = 1;
			}
			else
			{
				// ショットボタンが押されていなかった場合は
				// 前フレームでショットボタンが押されていたかを保存する変数に０(おされていない)を代入
				ShotBFlag = 0;
			}

			// ボール君が画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (Ball.x < 0) Ball.x = 0;

			// ボール君が画面右端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (Ball.x > 640 - 64) Ball.x = 640 - 64;

			// ボール君が画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (Ball.y < 0) Ball.y = 0;

			// ボール君が画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (Ball.y > 480 - 64) Ball.y = 480 - 64;

			// ボール君を描画
			DrawGraph(Ball.x, Ball.y, Ball.graph, FALSE);
		}

		// 弾の数だけ弾を動かす処理を繰り返す
		for (int i = 0; i < SHOT; i++)
		{
			// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容が１(存在する)の場合のみ行う )
			if (ShotFlag[i] == 1)
			{
				// 弾iを１６ドット上に移動させる
				ShotY[i] -= 16;

				// 画面外に出てしまった場合は存在状態を保持している変数に０(存在しない)を代入する
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				// 画面に弾iを描画する
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, FALSE);
			}
		}

		// 四角君の移動ルーチン
		{
			// 顔を歪めているかどうかで処理を分岐
			if (Sikaku.damageFlag)
			{
				// 顔を歪めている場合はダメージ時のグラフィックを描画する
				DrawGraph(Sikaku.x, Sikaku.y, Sikaku.damageGraph, FALSE);

				// 顔を歪めている時間を測るカウンターに１を加算する
				Sikaku.damageCounter++;

				// もし顔を歪め初めて ３０ フレーム経過していたら顔の歪んだ状態から
				// 元に戻してあげる
				if (Sikaku.damageCounter == 30)
				{
					// 『歪んでいない』を表す０を代入
					Sikaku.damageFlag = FALSE;
				}
			}
			else
			{
				// 歪んでいない場合は今まで通りの処理

				// 四角君の座標を移動している方向に移動する
				if (Sikaku.muki == 1) Sikaku.x += 3;
				if (Sikaku.muki == 0) Sikaku.x -= 3;

				// 四角君が画面右端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
				if (Sikaku.x > 576)
				{
					Sikaku.x = 576;
					Sikaku.muki = 0;
				}

				// 四角君が画面左端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
				if (Sikaku.x < 0)
				{
					Sikaku.x = 0;
					Sikaku.muki = 1;
				}

				// 四角君を描画
				DrawGraph(Sikaku.x, Sikaku.y, Sikaku.graph, FALSE);

				// 弾を撃つタイミングを計測するためのカウンターに１を足す
				Tama.counter++;

				// もしカウンター変数が６０だった場合は弾を撃つ処理を行う
				if (Tama.counter == 60)
				{
					// もし既に弾が『飛んでいない』状態だった場合のみ発射処理を行う
					if (Tama.flag)
					{
						// 弾の発射位置を設定する
						Tama.x = Sikaku.x + Sikaku.w / 2 - Tama.w / 2;
						Tama.y = Sikaku.y + Sikaku.h / 2 - Tama.h / 2;

						// 弾の移動速度を設定する
						{
							double sb, sbx, sby, bx, by, sx, sy;

							sx = Tama.x + Tama.w / 2;
							sy = Tama.y + Tama.h / 2;

							bx = Ball.x + Ball.w / 2;
							by = Ball.y + Ball.h / 2;

							sbx = bx - sx;
							sby = by - sy;

							// 平方根を求めるのに標準関数の sqrt を使う、
							// これを使うには math.h をインクルードする必要がある
							sb = sqrt(sbx * sbx + sby * sby);

							// １フレーム当たり８ドット移動するようにする
							Tama.Sx = sbx / sb * 8;
							Tama.Sy = sby / sb * 8;
						}

						// 弾の状態を保持する変数に『飛んでいる』を示す１を代入する
						Tama.flag = TRUE;
					}

					// 弾を打つタイミングを計測するための変数に０を代入
					Tama.counter = 0;
				}
			}
		}

		// 敵の弾の状態が『飛んでいる』場合のみ弾の移動処理を行う
		if (Tama.flag)
		{
			// 弾を移動させる
			Tama.x += Tama.Sx;
			Tama.y += Tama.Sy;

			// もし弾が画面からはみ出てしまった場合は弾の状態を『飛んでいない』
			// を表す０にする
			if (Tama.y > 480 || Tama.y < 0 ||
				Tama.x > 640 || Tama.x < 0) Tama.flag = FALSE;

			// 画面に描画する( ETamaGraph : 敵の弾のグラフィックのハンドル )
			DrawGraph((int)Tama.x, (int)Tama.y, Tama.graph, FALSE);
		}

		// 弾と敵の当たり判定、弾の数だけ繰り返す
		for (int i = 0; i < SHOT; i++)
		{
			// 弾iが存在している場合のみ次の処理に映る
			if (ShotFlag[i] == 1)
			{
				// 四角君との当たり判定
				if (((ShotX[i] > Sikaku.x && ShotX[i] < Sikaku.x + Sikaku.w) ||
					(Sikaku.x > ShotX[i] && Sikaku.x < ShotX[i] + Sikaku.Sw)) &&
					((ShotY[i] > Sikaku.y && ShotY[i] < Sikaku.y + Sikaku.h) ||
						(Sikaku.y > ShotY[i] && Sikaku.y < ShotY[i] + Sikaku.Sh)))
				{
					// 接触している場合は当たった弾の存在を消す
					ShotFlag[i] = 0;

					// 四角君の顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
					Sikaku.damageFlag = TRUE;

					// 四角君の顔を歪めている時間を測るカウンタ変数に０を代入
					Sikaku.damageCounter = 0;
				}
			}
		}

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// 画面モードの設定
	SetGraphMode(640, 480, 16);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	mainExec();


	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}

