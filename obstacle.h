#pragma once
#include "Jump_Position.h"
class Obstacle  {
private:
	char word = 'O';
	int metal = 0;//0の時ノーマル 1の時メタル状態
	_position position;
public:
	void setWord(char w) {//メタル状態の時は文字を変える
		this->word = w;
	}
	char getWord() {
		return word;
	}
	void setPosition(int x , int y) {
		position.x = x;
		position.y = y;
	}
	_position getPosition() {
		return position;
	}
	void setMetal() {
		metal = 1;
	}
	int getmetal() {
		return metal;
	}
};