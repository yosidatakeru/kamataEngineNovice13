#include <Novice.h>
#include <stdio.h>
#include "player.h"
const char kWindowTitle[] = "LC1D_30_ヨシダタケル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{

	//シーン0
	Effect blackHole;

	
	//パーティクルの幅を決める値
	blackHole.size.x = 640;
	blackHole.size.y = 720;
	
	
	blackHole.minPos.x = 1;
	blackHole.minPos.y = 100;
	blackHole.maxPos.x = 1;
	blackHole.maxPos.y = 100;

	//別の値を入れたいためfor分から外した
	Vector2 rockPos[2];
	rockPos[0].x = 0;
	rockPos[0].y = 500;
	rockPos[1].x = 1280;
	rockPos[1].y = 500;

	int rockSpeed = 20;


	//衝突したときに出るブラックホール値を決める
	Vector2 blackHolePos;
    blackHolePos.x = 640;
	blackHolePos.y = 500;
    int blackHoleSpawn = 0;
	int blackHoleRadius = 0;


	//シーン１
	Effect meteor;

	//パーティクルの幅を決める値
	meteor.size.x = 640;
	meteor.size.y = 0;

	meteor.minPos.x = 1;
	meteor.minPos.y = 200;
	meteor.maxPos.x = 1;
	meteor.maxPos.y = 100;
	



	//シーン２
	Effect bigMeteor;

	//パーティクルの幅を決める値
	bigMeteor.size.x = 640;
	bigMeteor.size.y = 0;

	bigMeteor.minPos.x = 1;
	bigMeteor.minPos.y = 200;
	bigMeteor.maxPos.x = 1;
	bigMeteor.maxPos.y = 100;
	
	Vector2 meteorPos;
    meteorPos.x = 320;
	meteorPos.y = -300;
	int meteorSpeed = 5;



	//シーン３
	Effect rain;

	//パーティクルの幅を決める値
	rain.size.x = 800;
	rain.size.y = 0;

	rain.minPos.x = 500;
	rain.minPos.y = 100;
	rain.maxPos.x = 500;
	rain.maxPos.y = 100;
	
	
	int deleteFlame = 1;
	int flameTime = 100;


	//パーティクル
	const int MAX = 100;

	int particlePosx[MAX];
	int particlePosy[MAX];
	int particleSpeed[MAX];
	int particleSpawn[MAX];

	//パーティクル初期化
	for (int i = 0; i < MAX; i++)
	{
		particlePosx[i] = 0;
		particlePosy[i] = 0;
		particleSpeed[i] = 0;
		particleSpawn[i] = 0;
	}

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

    //クラスの呼び出し
	Player* player = new Player;

	//画面切り替え
	int scene = 0;

	enum SceneCondition 
	{
		BlackHole,// scene  0
		Meteor,   // scene  1
		BigMeteor,// scene  2
		Rain,     // scene  3	
	};

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) 
	{

		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		switch (scene) 
		{


		case BlackHole:
		{


			//シーンの切り替え操作
			if (keys[DIK_1])
			{
				scene = Meteor;
			}
			if (keys[DIK_2])
			{
				scene = BigMeteor;

			}
			if (keys[DIK_3])
			{
				scene = Rain;
			}
			

			//プレイヤー操作
			player->Update(keys);

			//演出のリセット操作
			if (keys[DIK_R])
			{
				for (int i = 0; i < MAX; i++)
				{
					particlePosx[i] = 0;
					particlePosy[i] = 0;
					particleSpeed[i] = 20;
					particleSpawn[i] = 0;
				}

				rockPos[0].x = 0;
				rockPos[0].y = 500;
				rockPos[1].x = 1280;
				rockPos[1].y = 500;
				rockSpeed = 20;

			
				blackHolePos.x = 640;
				blackHolePos.y = rockPos[0].y;
				blackHoleSpawn = 0;
				blackHoleRadius = 50;
				
			
				blackHole.minPos.y = 100;
				blackHole.maxPos.x = 1;
				blackHole.maxPos.y = 100;
			}

			//岩の移動処理
			if (blackHoleSpawn == 0)
			{
				rockPos[0].x += rockSpeed;
				rockPos[1].x -= rockSpeed;
			}

			//blackHoleSpawn = 1の時ブラックホールが出現する
			if (rockPos[0].x >= 640)
			{
				blackHoleSpawn = 1;
			}

			if (blackHoleSpawn == 1 && blackHoleRadius <= 500)
			{
				blackHoleRadius++;
			}

			if (blackHoleSpawn == 1)
			{
				for (int i = 0; i < MAX; i++)
				{

					if (particleSpawn[i] == 0)
					{
						particleSpawn[i] = 1;
						
						                                       // blackHole.maxPos.x =1 //meteor.minPos.x = 1
						particlePosx[i] = blackHole.size.x + rand() % blackHole.maxPos.x - blackHole.minPos.x;

						                                       //blackHole.maxPos.y = 100 //blackHole.minPos.y = 100
						particlePosy[i] = blackHole.size.y + rand() % blackHole.maxPos.y - blackHole.minPos.y;

						break;
					}

				}

				for (int i = 0; i < MAX; i++) 
				{
					//パーティクル出現//1
					if (particleSpawn[i] == 1)
					{
						particlePosy[i] -= particleSpeed[i];

						if (particlePosy[i] <= 320)
						{
							//パーティクル消滅//0
							particleSpawn[i] = 0;
						}

					}
				}

				//幅の調整
				{
					blackHole.maxPos.x++;
					blackHole.maxPos.x++;
					blackHole.minPos.x = blackHole.maxPos.x / 2;
				}
			}
			
			//描画処理
			if (blackHoleSpawn == 0)
			{
				
				//おなじ値を使うためblackHoleRadiusよ使用
				Novice::DrawEllipse(rockPos[0].x, rockPos[0].y, blackHoleRadius + 50, blackHoleRadius + 50, 0.0f, BLUE, kFillModeSolid);
				Novice::DrawEllipse(rockPos[1].x, rockPos[1].y, blackHoleRadius + 50, blackHoleRadius + 50, 0.0f, RED, kFillModeSolid);
			}

			if (blackHoleSpawn == 1)
			{
				Novice::DrawEllipse(blackHolePos.x, blackHolePos.y, blackHoleRadius, blackHoleRadius, 0.0f, 0x000000FF, kFillModeSolid);
				if (blackHoleRadius < 500)
				{
					for (int i = 0; i < 100; i++)
					{
						if (particleSpawn[i] == 1)
						{
							Novice::DrawEllipse(particlePosx[i], particlePosy[i], 5, 5, 0.0f, 0xFFFFFFFF, kFillModeSolid);

						}

					}
				}
			}

			//プレイヤーの描画
			player->Draw();

			//操作説明
			Novice::ScreenPrintf(100, 100, "WASD/MOVE  R/reset");

			break;
		}

		case Meteor :
		{

			//シーンの切り替え操作
			if (keys[DIK_0])
			{
				scene = BlackHole;
			}
			if (keys[DIK_2])
			{
				scene = BigMeteor;
			}
			if (keys[DIK_3])
			{
				scene = Rain;
			}

			//プレイヤー操作
			player->Update(keys);

			//演出のリセット
			if (keys[DIK_R])
			{
				for (int i = 0; i < MAX; i++)
				{
					particlePosx[i] = 700;
					particlePosy[i] = 0;
					particleSpeed[i] = 20;
					particleSpawn[i] = 0;

				}
			}

			for (int i = 0; i < MAX; i++) 
			{
				if (particleSpawn[i] == 0)
				{
					particleSpawn[i] = 1;
					
                                                          //meteor.maxPos.x = 1//meteor.minPos.x = 1
					particlePosx[i] = meteor.size.x + rand() % meteor.maxPos.x - meteor.minPos.x;

					                                    //meteor.maxPos.y = 100//meteor.minPos.y = 200
					particlePosy[i] = meteor.size.y + rand() % meteor.maxPos.y - meteor.minPos.y;

					break;
				}

			}


			for (int i = 0; i < MAX; i++) 
			{
				//パーティクルの出現//1
				if (particleSpawn[i] == 1)
				{
					particlePosy[i] += particleSpeed[i];
					particlePosx[i] -= particleSpeed[i];

					if (particlePosy[i] >= 3200)
					{
						//パーティクルの消滅//0
						particleSpawn[i] = 0;
					}

				}
			}

			//描画処理
			for (int i = 0; i < 100; i++) 
			{
				if (particleSpawn[i] == 1) 
				{
					Novice::DrawEllipse(particlePosx[i], particlePosy[i], 20, 20, 0.0f, 0x000000FF, kFillModeSolid);
				}

			}

			//操作説明
			Novice::ScreenPrintf(100, 100, "WASD/MOVE  R/reset");
			
			//プレイヤーの描画
			player->Draw();

			break;
		}
		case BigMeteor:
		{

			//シーンの切り替え操作
			if (keys[DIK_0])
			{
				scene = BlackHole;
			}
			if (keys[DIK_1])
			{
				scene = Meteor;
			}
			if (keys[DIK_3])
			{
				scene = Rain;
			}

			//プレイヤー操作
			player->Update(keys);

			//演出のリセット
			if (keys[DIK_R])
			{
				for (int i = 0; i < MAX; i++)
				{
					particlePosx[i] = 700;
					particlePosy[i] = 0;
					particleSpeed[i] = 5;
					particleSpawn[i] = 0;
				}
				meteorPos.x = 320;
				meteorPos.y = -300;
			}

			for (int i = 0; i < MAX; i++) 
			{
				if (particleSpawn[i] == 0)
				{
					particleSpawn[i] = 1;
			
					                                     //bigMeteor.maxPos.x = 1//bigMeteor.minPos.x = 1
					particlePosx[i] = meteorPos.x + rand() % bigMeteor.maxPos.x - bigMeteor.minPos.x;

					                                  //bigMeteor.maxPos.y = 100//bigMeteor.minPos.y = 200               
					particlePosy[i] = meteorPos.y + rand() % bigMeteor.maxPos.y - bigMeteor.minPos.y;

					break;
				}

			}


			for (int i = 0; i < MAX; i++) 
			{
				//パーティクルの出現//1
				if (particleSpawn[i] == 1)
				{
					particlePosy[i] -= particleSpeed[i];

					if (particlePosy[i] <= -300)
					{
						//パーティクルの消滅//0
						particleSpawn[i] = 0;
					}
				}
			}

			meteorPos.y += meteorSpeed;
			
			//描画処理
			for (int i = 0; i < MAX; i++) 
			{
				if (particleSpawn[i] == 1) 
				{
					Novice::DrawEllipse(particlePosx[i], particlePosy[i], 20, 20, 0.0f, 0x000000FF, kFillModeSolid);
				}
			}

			
			Novice::DrawEllipse(meteorPos.x, meteorPos.y, 200, 200, 0.0f, 0x000000FF, kFillModeSolid);
			
			//プレイヤーの描画
			player->Draw();

			//操作説明
			Novice::ScreenPrintf(100, 100, "WASD/MOVE  R/reset");
			break;
		}
		case Rain:
		{

			//シーン切り替え
			if (keys[DIK_0])
			{
				scene = BlackHole;
			}
			if (keys[DIK_1])
			{
				scene = Meteor;
			}
			if (keys[DIK_2])
			{
				scene = BigMeteor;
			}
			
			//プレイヤー操作
			player->Update(keys);

			//演出のリセット
			if (keys[DIK_R])
			{
				for (int i = 0; i < MAX; i++)
				{
					particlePosx[i] = 800;
					particlePosy[i] = 0;
					particleSpeed[i] = 10;
					particleSpawn[i] = 0;
					deleteFlame = 1;
					flameTime = 100;
				}
			}

			//火が消えるまでの時間
			flameTime--;

			for (int i = 0; i < MAX; i++) 
			{
				if (particleSpawn[i] == 0)
				{
					particleSpawn[i] = 1;

					                                      //rain.maxPos.x = 500//rain.minPos.x = 500
					particlePosx[i] = rain.size.x = 0 + rand() % rain.maxPos.x - rain.minPos.x;

					                                    //rain.maxPos.y = 100//rain.minPos.y = 100
					particlePosy[i] = rain.size.y + rand() % rain.maxPos.y - rain.minPos.y;

					break;
				}

			}


			for (int i = 0; i < MAX; i++)
			{
				//パーティクルの出現//1
				if (particleSpawn[i] == 1)
				{
					particlePosy[i] += particleSpeed[i];

					if (particlePosy[i] >= 720)
					{
						//パーティクルの消滅//0
						particleSpawn[i] = 0;
					}

				}

			}

			if (flameTime < 0)
			{
				deleteFlame = 0;
			}
			
			//描画処理
			if (deleteFlame == 1) 
			{
				Novice::DrawBox(500, 600, 40, 40, 0.0f, 0xFFFFFFFF, kFillModeSolid);
			}
			for (int i = 0; i < MAX; i++) 
			{
				if (particleSpawn[i] == 1) 
				{
					Novice::DrawEllipse(particlePosx[i], particlePosy[i], 5, 5, 0.0f, BLUE, kFillModeSolid);

				}

			}
			
			//プレイヤーの描画
			player->Draw();

			//操作説明
			Novice::ScreenPrintf(100, 100, "WASD/MOVE  R/reset");
		}

		}
		
		///
		/// ↑更新処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) 
		{
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
