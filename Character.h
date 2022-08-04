#pragma once
#include "Jump_Position.h"
//キャラクターの動作、文字を定義
//カウントの秒数と位置が欲しい
class Character {
private :
	//キャラクターの文字を定義
	char character_word = 'A';
	int MAX_SHORT = 18;
	int MAX_HIGH = 14;
	int MAX_HIGH_SUPER = 10;
	int attack_counter = 0;
	_jump j_short;
	_jump j_high;
	_jump j_high_super;
public:
	Character() {
	}
	int getMAX_SHORT() {
		return MAX_SHORT;
	}
	int getMAX_HIGH() {
		return MAX_HIGH;
	}
	int getMAX_HIGH_SUPER() {
		return MAX_HIGH_SUPER;
	}

	//キャラクターの文字をセット
	void SetCharacter_word(char word) {
		this->character_word = word;
	}
	char getCharacter_word() {
		return character_word;
	}
	//ジャンプ入力時(short)の処理を定義 
	//counterが30カウントするまでjump処理を続ける
	//ジャンプするときは1、終わった時は0を返す
	_jump Jump_short() {
		j_short.jump_counter++;
		if (j_short.jump_counter >= MAX_SHORT){
			j_short.jump_counter = 0;
			j_short.position_y = 0;
		}
		else {
			j_short.position_y = 1;
		}
		return j_short;
	}
	//ジャンプ入力時(high)の処理を定義 
	//counterが20カウントするまでjump処理を続ける
	//ジャンプ出始めは1、ジャンプ中は2、終わった時は0を返す
	_jump Jump_high() {
		j_high.jump_counter++;
		if (j_high.jump_counter >= MAX_HIGH) {
			j_high.jump_counter = 0;
			j_high.position_y = 0;
		}
		//jumpの出始め、着地際は1を返す、
		else if (j_high.jump_counter == 1 || j_high.jump_counter == MAX_HIGH - 1) {
			j_high.position_y = 1;
		}
		else {
			j_high.position_y = 2;
		}
		return j_high;
	}
	//ジャンプ入力時(super_high)の処理を定義 
	//counterが20カウントするまでjump処理を続ける
	//ジャンプ出始めは1、ジャンプ中は2、終わった時は0を返す
	_jump Jump_high_super() {
		j_high_super.jump_counter++;
		if (j_high_super.jump_counter >= MAX_HIGH_SUPER) {
			j_high_super.jump_counter = 0;
			j_high_super.position_y = 0;
		}
		//jumpの出始め、着地際は1を返す、
		else if (j_high_super.jump_counter == 1 || j_high_super.jump_counter == MAX_HIGH_SUPER - 1) {
			j_high_super.position_y = 1;
		}
		//jumpの出始め、着地際+1は2を返す、
		else if (j_high_super.jump_counter == 2 || j_high_super.jump_counter == MAX_HIGH_SUPER - 2) {
			j_high_super.position_y = 2;
		}
		else {
			j_high_super.position_y = 3;
		}
		return j_high_super;
	}
};