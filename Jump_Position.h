#pragma once
#ifndef __Jump_Position__
#define __Jump_Position__

struct _jump {
	int jump_counter = 0;//short,high‚Æ‚à‚Éjump_counter‚Í—p‚¢‚é
	int position_y =0 ;
	const _jump& operator=(const _jump& rhs)
	{
		this->jump_counter = rhs.jump_counter;
		this->position_y = rhs.position_y;
		return *this;
	}
};
struct _position {
	int x = 0;
	int y = 0;
};
#endif