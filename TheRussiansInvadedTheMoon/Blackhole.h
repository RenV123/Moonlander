#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Blackhole Class									
//-----------------------------------------------------
class Blackhole
{
public:
	Blackhole();				// Constructor
	virtual ~Blackhole();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//------------------------------------------------
	bool Create(int x, int y, double mass);
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	DOUBLE2 getPos();
	double getMass();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Bitmap * m_BmpBlackHolePtr;
	DOUBLE2 m_Position;
	double m_Angle,m_Scale,m_Mass;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Blackhole(const Blackhole& yRef);									
	Blackhole& operator=(const Blackhole& yRef);	
};

 
