//---------------------------
// Includes
//---------------------------
#include "Blackhole.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Blackhole::Blackhole(): m_BmpBlackHolePtr(nullptr),
						m_Position(0,0),
						m_Angle(0),
						m_Scale(0.4),
						m_Mass(0)
{
	// nothing to create
}

Blackhole::~Blackhole()
{
	delete m_BmpBlackHolePtr;
	m_BmpBlackHolePtr = nullptr;
}

//---------------------------
// Own methods
//---------------------------
bool Blackhole::Create(int x, int y,double mass)
{
	m_Position =  DOUBLE2(x,y);
	m_Mass = mass;
	m_BmpBlackHolePtr = new Bitmap(IDB_BLACKHOLE);
	m_BmpBlackHolePtr->SetTransparencyColor(255,0,255);
	if(m_BmpBlackHolePtr->Exists()) return true;
	else return false;
}
void Blackhole::Tick(double deltaTime)
{
	m_Angle+=0.05;
}
void Blackhole::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matCenter,matRotate,matScale,matTranslate;
	matCenter.SetAsTranslate(-m_BmpBlackHolePtr->GetWidth()/2,-m_BmpBlackHolePtr->GetHeight()/2);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matTranslate.SetAsTranslate(m_Position);
	GAME_ENGINE->SetTransformMatrix(matCenter*matRotate*matScale*matTranslate*matView);
	GAME_ENGINE->DrawBitmap(m_BmpBlackHolePtr,0,0);
}
DOUBLE2 Blackhole::getPos()
{
	return m_Position;
}
double Blackhole::getMass()
{
	return m_Mass;
}

