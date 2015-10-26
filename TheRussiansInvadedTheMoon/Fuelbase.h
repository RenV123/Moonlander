#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Fuelbase Class									
//-----------------------------------------------------
class Fuelbase
{
public:
	Fuelbase();				// Constructor
	virtual ~Fuelbase();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	bool Create(int x, int y, int fuel);
	void Paint(MATRIX3X2 matView);
	DOUBLE2 GetPos();
	int GetFuel();
	void RemoveFuel( int fuel);
	RECT2 GetRect();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_Position;
	int m_Fuel;
	RECT2 m_RectFuelbase;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Fuelbase(const Fuelbase& yRef);									
	Fuelbase& operator=(const Fuelbase& yRef);	
};

 
