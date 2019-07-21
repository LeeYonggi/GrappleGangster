#include "DXUT.h"
#include "Player.h"

void Player::Init()
{
	mainTexture = Resources->LoadTexture("Character/test.png");

}

void Player::Update()
{

}

void Player::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, {0, 0, 0}, scale, rotate);

}

void Player::Release()
{
}
