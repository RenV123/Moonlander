//---------------------------
// Includes
//---------------------------
#include "Bullet.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bullet::Bullet(double x, double y, double dirx, double diry) 
	:m_Pos(x,y) 
	,m_CollissionRect(0,0,0,0)
	,m_IsAsteroidHit(0)
	,m_Speed(10)
	,m_Direction(dirx,diry)
{
	
}
Bullet::~Bullet()
{
}
void Bullet::Tick(double deltaTime)
{

	m_CollissionRect.top = m_Pos.y-3;
	m_CollissionRect.left = m_Pos.x-3;
	m_CollissionRect.bottom = m_Pos.y+3;
	m_CollissionRect.right = m_Pos.x +3;

	//Movement

	DOUBLE2 velocity = m_Speed*m_Direction;
	DOUBLE2 displacement = velocity * deltaTime;
	m_Pos+=displacement;
}
void Bullet::Paint(MATRIX3X2 matView,MATRIX3X2 matRotate)
{
	MATRIX3X2 matTranslate, matTransform,matCenter, matReset;
 	matCenter.SetAsTranslate(0,0);
	matTranslate.SetAsTranslate(m_Pos);
  	GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
	GAME_ENGINE->SetColor(COLOR(200,200,200));
	GAME_ENGINE->FillEllipse(0,0,3,3);
	//GAME_ENGINE->SetTransformMatrix(matView);
	//GAME_ENGINE->SetColor(COLOR(0,0,0));
	//GAME_ENGINE->DrawRect(m_CollissionRect,1.0);

/*
	GAME_ENGINE->SetColor(COLOR(255,255,,230));
	GAME_ENGINE->FillEllipse(0,0,3,3);*/
	//GAME_ENGINE->SetColor(COLOR(255,255,255));
	//GAME_ENGINE->DrawString(m_Direction.ToString()+String("\n")+m_Pos.ToString(),0,0);

	//GAME_ENGINE->SetTransformMatrix(matView);
	//GAME_ENGINE->SetColor(COLOR(0,0,255,200));
	//GAME_ENGINE->FillRect(m_CollissionRect);

	matReset.SetAsIdentity();
	GAME_ENGINE->SetTransformMatrix(matReset);
}
double Bullet::GetWidth()
{
	return 20;
}
DOUBLE2 Bullet::GetPos()
{
	return m_Pos;
}
RECT2 Bullet::GetRect()
{
	return m_CollissionRect;
}
void Bullet::SetIsAsteroidHit(bool SetAsteroidHit)
{
	m_IsAsteroidHit = SetAsteroidHit;
}