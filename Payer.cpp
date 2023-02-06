#include <Novice.h>
#include<stdio.h>
#include"player.h"

Player::Player() 
{
	pos_.x = 30;
	pos_.y = 30;
	speed_ = 5;
	radius_ = 10;
}

void Player::Update(char* keys) 
{
	//プレイヤーの操作
	if (keys[DIK_W] || keys[DIK_UP])
	{
		pos_.y -= speed_;
	}
	if (keys[DIK_A] || keys[DIK_LEFT])
	{
		pos_.x -= speed_;
	}
	if (keys[DIK_S] || keys[DIK_DOWN])
	{
		pos_.y += speed_;
	}
	if (keys[DIK_D] || keys[DIK_RIGHT])
	{
		pos_.x += speed_;
	}
	
}

//プレイヤーの描画
void Player::Draw() 
{
	Novice::DrawBox(pos_.x, pos_.y, radius_, radius_, 0.0f, RED, kFillModeSolid);

}
