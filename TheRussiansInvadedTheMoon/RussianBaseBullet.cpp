//---------------------------
// Includes
//---------------------------
#include "RussianBaseBullet.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
RussianBaseBullet::RussianBaseBullet(double x, double y, double dirx, double diry) 
	:m_Pos(x,y) 
	,m_CollissionRect(0,0,0,0)
	,m_IsAsteroidHit(0)
	,m_Speed(10)
	,m_Direction(dirx,diry)
{
	
}
RussianBaseBullet::~RussianBaseBullet()
{
}
void RussianBaseBullet::Tick(double deltaTime)
{

	m_CollissionRect.top = m_Pos.y-7;
	m_CollissionRect.left = m_Pos.x-8;
	m_CollissionRect.bottom = m_Pos.y+7;
	m_CollissionRect.right = m_Pos.x +17;

	//Movement


	DOUBLE2 velocity = m_Speed*m_Direction;
	DOUBLE2 displacement = velocity * deltaTime;
	m_Pos+=displacement;
}
void RussianBaseBullet::Paint(MATRIX3X2 matView,MATRIX3X2 matRotate)
{
	MATRIX3X2 matTranslate, matTransform,matCenter, matReset;
	matCenter.SetAsTranslate(0,0);
	matTranslate.SetAsTranslate(m_Pos);
	GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
	GAME_ENGINE->SetColor(COLOR(255,255,0));
	GAME_ENGINE->FillEllipse(0,0,3,3);
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
double RussianBaseBullet::GetWidth()
{
	return 20;
}
DOUBLE2 RussianBaseBullet::GetPos()
{
	return m_Pos;
}
RECT2 RussianBaseBullet::GetRect()
{
	return m_CollissionRect;
}
void RussianBaseBullet::SetIsAsteroidHit(bool SetAsteroidHit)
{
	m_IsAsteroidHit = SetAsteroidHit;
}