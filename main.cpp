#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mutex>
#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <time.h>
#include <vector>
#include <map>
#include "PoolAllocator.h"
#include "Jump_Position.h"
#include "Character.h"
#include "obstacle.h"

/* この実習で学んだ様々なものを使って簡単なCUIのゲームを作ってみよう。
 * 作成するものは何でもよいが下記の要件を満たす事。
 * タイトル ゲームシーケンス 結果表示が存在しそれらがステートマシンによってコントロールされていること（任意)
 * クラスの多態性を用いたオブジェクト管理が入っていること(任意)
 * 自分が作成した Poolアロケータが使われていること(必須)
 * 何かしらの処理にスレッドを用いた並行処理が入っていること(任意)
 * ゲームエンジンの使用は不可
 * 使用 する言語は C ++。
 */


int base_y = 11; //ゲームフィールドのバイアス
int touch = -10; // キー入力値
int AREA_SIZE_y = 4;//ゲームエリア_y
int AREA_SIZE_x = 30;//ゲームエリア_x
int Character_default_y = base_y + AREA_SIZE_y - 1;//キャラクターの位置_y
int Character_default_x = 2;//キャラクターの位置_x
int Character_position_y = Character_default_y;//キャラクターの位置_可変
int past = Character_position_y;////キャラクターの位置_過去
int damagetime = 0;//ダメージの表現時間
int LIFE = 3;//残り体力

char attack_word = '*';

std::map<int, int> bullet;//攻撃する弾

Character* Chara1;
_jump jump;

void Keyboard() {
			do
		{
				int fake = _getch();
				if (jump.position_y == 0 && (fake == 'e' || fake == 'w')|| fake == 'r') {
					touch = fake;
				}
				if (fake == 'd' && bullet[2] == 0) {
					bullet[0] = Character_position_y;
					bullet[1] = Character_default_x;
					bullet[2] = 1;//1の時実弾
				}
		} while ('q' != touch); // 'q'キーで終了

}

void Attack(int position_y, int position_x) {
	printf("\x1b[%d;%dH ", position_y, position_x - 1);
	printf("\x1b[%d;%dH\x1b[31m%c\x1b[39m", position_y, position_x, attack_word);//弾 赤色
}

//障害物、キャラクター、時間表示のクラスをそれぞれ呼び出す
//Threadsを作成、(keyboard用)
int main() 
{
	//カーソルを消す
	printf("\x1b[?25l");

	int frame_count = 0;
	int second = 0;
	int random = 0;
	int obstacle_first_x = AREA_SIZE_x;
	srand((unsigned int)time(NULL)); // 乱数の種を初期化（プログラムの先頭で1回のみ）

	const int CHARACTER_SIZE = 1;
	const int OBSTACLE_SIZE = 10;

	std::vector<Obstacle*> obstacle;

	PoolAllocator<Character, CHARACTER_SIZE> a_character;//Character class のPoolAllcatorを作成
	PoolAllocator<Obstacle, OBSTACLE_SIZE> a_obstacle;//obstacle class のPoolAllcatorを作成

	Chara1 = a_character.Alloc();//メモリ確保

	//keyアクションに対応するスレッドが実行
	std::thread key_Threads(Keyboard);

	//弾の状態を初期化
	bullet[0] = 0;
	bullet[1] = 0;
	bullet[2] = 0;
	
	//連続的に描画する
	do {
		Sleep(1 * 100);//-----------------------------------------------------------------------------o.1秒間隔
		if (frame_count % 10 == 0 && frame_count != 0) second++;
		printf("\x1b[%d;%dH%d.%d 秒" , 0 , 0 , second ,frame_count % 10);//カウント
		if (jump.jump_counter == 0) {
			printf("\x1b[%d;%dH ジャンプ時間 : %d ", 0, 10, jump.jump_counter);
		}
		else if (touch == 'w') {
			printf("\x1b[%d;%dH ジャンプ時間 : %d ", 0, 10, Chara1->getMAX_SHORT() - jump.jump_counter);
		}
		else if (touch == 'e') {
			printf("\x1b[%d;%dH ジャンプ時間 : %d ", 0, 10, Chara1->getMAX_HIGH() - jump.jump_counter);
		}
		else if (touch == 'r') {
			printf("\x1b[%d;%dH ジャンプ時間 : %d ", 0, 10, Chara1->getMAX_HIGH_SUPER() - jump.jump_counter);
		}

		printf("\x1b[%d;%dH 残りライフ: %dつ ", 0, 30, LIFE);//---------------------------------------------------カウント
		printf("\x1b[%d;%dH 記号 : ジャンプの高さ(滞空時間) or 攻撃(弾数)", 2, 0);
		printf("\x1b[%d;%dH w : 1段階(1.8秒)", 3, 0);
		printf("\x1b[%d;%dH e : 2段階(1.4秒)", 4, 0);
		printf("\x1b[%d;%dH r : 3段階(1.0秒)", 5, 0);
		printf("\x1b[%d;%dH d : 砲撃(1発) Oは壊せますがMは壊せません（メタル状態）", 6, 0);
		








		//Characterのjump
		if (touch == 'w' || touch == 'e' || touch == 'd' || touch == 'r') {
			switch (touch) {
			case 'w'://小ジャンプ
				jump = Chara1->Jump_short();
				break;
			case 'e'://大ジャンプ
				jump = Chara1->Jump_high();
				break;
			case 'r'://超大ジャンプ
				jump = Chara1->Jump_high_super();
				break;
			}
			past = Character_position_y;
			Character_position_y = Character_default_y - jump.position_y;
			if (jump.position_y == 0 && Character_position_y != past) {
				touch = -10;
			}
		}



		if (bullet[2] == 1) {

			Attack(bullet[0], bullet[1]);
			if (bullet[1] >= 20) {//position_x
				bullet[2] = 0;
			}
			else {
				bullet[1]++;
			}

		}


		//rand()%10;//1/10の乱数を生成
		//obstacle生成
		if( ( frame_count % 7 == 0 || ( random = rand() % 15 ) == 0 ) && obstacle.size() < OBSTACLE_SIZE ) {//7カウントに1回,1/15の確立で
			Obstacle* o= a_obstacle.Alloc();
			if (random == 0) {
				o->setMetal();//メタル化の識別
				o->setWord('M');//メタル化の記号を変える
			}
			o->setPosition(obstacle_first_x, rand() % AREA_SIZE_y );//x,yをセット 0~4まで
			obstacle.push_back(o);//obstacle*型vectorに追加
		}
		//obstacleの描画、端までいったobstacleの削除
		std::vector<Obstacle*>::iterator itr = obstacle.begin();
		for (int i = 0; i < obstacle.size();) {

			if (Character_position_y == obstacle[i]->getPosition().y + base_y && Character_default_x == obstacle[i]->getPosition().x) {
				damagetime = 10;
				LIFE--;
			}

			//xが端まで行ったときにobstacleを削除 obstacleのメモリを解放+bulletと重なった時
			if ( obstacle[i]->getPosition().x == 0 ||
				(obstacle[i]->getmetal() == 0 && obstacle[i]->getPosition().y + base_y == bullet[0] && obstacle[i]->getPosition().x + 3 == bullet[1])
				|| 
				(obstacle[i]->getmetal() == 0 && obstacle[i]->getPosition().y + base_y == bullet[0] && obstacle[i]->getPosition().x + 2 == bullet[1] )
				) {

				printf("\x1b[%d;%dH ", obstacle[i]->getPosition().y + base_y, obstacle[i]->getPosition().x);//------------------------------------------------------------------obstacleを描画
				printf("\x1b[%d;%dH ", obstacle[i]->getPosition().y + base_y, obstacle[i]->getPosition().x + 1);
				a_obstacle.Free(obstacle[i]);
				itr = obstacle.erase(itr, itr + 1);
			}
			else {//次に進める
				int x = obstacle[i]->getPosition().x;
				int y = obstacle[i]->getPosition().y;
				printf("\x1b[%d;%dH ", y + base_y, x+1);//------------------------------------------------------------------obstacleを描画
				if (obstacle[i]->getmetal() == 1) {
					printf("\x1b[%d;%dH\x1b[33m\x1b[47m%c\x1b[49m\x1b[39m", y + base_y, x, obstacle[i]->getWord());//---------obstacleを描画
				}
				else {
					printf("\x1b[%d;%dH\x1b[33m%c\x1b[39m", y + base_y, x, obstacle[i]->getWord());//------------obstacleを描画
				}
				obstacle[i]->setPosition( --x , y );
				i++;
				itr++;
			}
		}
		if (damagetime > 0)damagetime--;
		if (past != Character_position_y) {
			printf("\x1b[%d;%dH ", past, Character_default_x );
		}
		if (damagetime == 0 || damagetime % 2 == 0) {
			printf("\x1b[%d;%dH\x1b[32m%c\x1b[39m", Character_position_y, Character_default_x, Chara1->getCharacter_word());//キャラクターを描画 gray
		}
		else {
			printf("\x1b[%d;%dH ", Character_position_y, Character_default_x);//キャラクターを描画
		}
		
		if (LIFE == 0) {
			break;
		}
		

		if (frame_count == 32767) frame_count %= 3;
		frame_count++;
	} while (touch != 'p');

	
	int y = Character_position_y;
	int x = Character_default_x + 30*2 ;
	printf("\x1b[%d;%dH Thank you for playing!", y+=2 , x );//キャラクターを描画
	printf("\x1b[%d;%dH あそんでくれてありがとう!", y+=2, x );
	printf("\x1b[%d;%dH 今回のタイムは %d.%d 秒だったよ!", y+=2, x , second , frame_count % 10);
	printf("\x1b[%d;%dH またあそんでね!" ,y+=2 , x );


	key_Threads.join();
	return 0;
}


