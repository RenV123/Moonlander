//---------------------------
// Includes
//---------------------------
#include "Fuelbase.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Fuelbase::Fuelbase()
{

}

Fuelbase::~Fuelbase()
{
}
bool Fuelbase::Create(int x, int y, int fuel)
{
	m_Position = DOUBLE2(x,y);
	m_Fuel = fuel;

	m_RectFuelbase = RECT2(m_Position.x,m_Position.y,m_Position.x+ 160,  m_Position.y+20);

	return true;
}

void Fuelbase::Paint(MATRIX3X2 matView)
{
	//GAME_ENGINE->SetTransformMatrix(matView);
	//GAME_ENGINE->SetColor(COLOR(0,0,0,100));
	//GAME_ENGINE->FillRect(m_RectFuelbase);
	//cout << m_Fuel << endl;
}
DOUBLE2 Fuelbase::GetPos()
{
	return m_Position;
}
int Fuelbase::GetFuel()
{
	return m_Fuel;
}
void Fuelbase::RemoveFuel( int fuel)
{
	m_Fuel -= fuel;
}
RECT2 Fuelbase::GetRect()
{
	return m_RectFuelbase;
}

