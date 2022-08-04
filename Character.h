#pragma once
#include "Jump_Position.h"
//�L�����N�^�[�̓���A�������`
//�J�E���g�̕b���ƈʒu���~����
class Character {
private :
	//�L�����N�^�[�̕������`
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

	//�L�����N�^�[�̕������Z�b�g
	void SetCharacter_word(char word) {
		this->character_word = word;
	}
	char getCharacter_word() {
		return character_word;
	}
	//�W�����v���͎�(short)�̏������` 
	//counter��30�J�E���g����܂�jump�����𑱂���
	//�W�����v����Ƃ���1�A�I���������0��Ԃ�
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
	//�W�����v���͎�(high)�̏������` 
	//counter��20�J�E���g����܂�jump�����𑱂���
	//�W�����v�o�n�߂�1�A�W�����v����2�A�I���������0��Ԃ�
	_jump Jump_high() {
		j_high.jump_counter++;
		if (j_high.jump_counter >= MAX_HIGH) {
			j_high.jump_counter = 0;
			j_high.position_y = 0;
		}
		//jump�̏o�n�߁A���n�ۂ�1��Ԃ��A
		else if (j_high.jump_counter == 1 || j_high.jump_counter == MAX_HIGH - 1) {
			j_high.position_y = 1;
		}
		else {
			j_high.position_y = 2;
		}
		return j_high;
	}
	//�W�����v���͎�(super_high)�̏������` 
	//counter��20�J�E���g����܂�jump�����𑱂���
	//�W�����v�o�n�߂�1�A�W�����v����2�A�I���������0��Ԃ�
	_jump Jump_high_super() {
		j_high_super.jump_counter++;
		if (j_high_super.jump_counter >= MAX_HIGH_SUPER) {
			j_high_super.jump_counter = 0;
			j_high_super.position_y = 0;
		}
		//jump�̏o�n�߁A���n�ۂ�1��Ԃ��A
		else if (j_high_super.jump_counter == 1 || j_high_super.jump_counter == MAX_HIGH_SUPER - 1) {
			j_high_super.position_y = 1;
		}
		//jump�̏o�n�߁A���n��+1��2��Ԃ��A
		else if (j_high_super.jump_counter == 2 || j_high_super.jump_counter == MAX_HIGH_SUPER - 2) {
			j_high_super.position_y = 2;
		}
		else {
			j_high_super.position_y = 3;
		}
		return j_high_super;
	}
};