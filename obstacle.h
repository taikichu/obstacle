#pragma once
#include "Jump_Position.h"
class Obstacle  {
private:
	char word = 'O';
	int metal = 0;//0�̎��m�[�}�� 1�̎����^�����
	_position position;
public:
	void setWord(char w) {//���^����Ԃ̎��͕�����ς���
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