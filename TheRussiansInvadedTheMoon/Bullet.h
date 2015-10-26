#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Bullet Class									
//-----------------------------------------------------
class Bullet
{
public:
	Bullet(double x, double y, double dirx, double diry);				// Constructor
	virtual ~Bullet();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView,MATRIX3X2 matRotate);
	double GetWidth();
	DOUBLE2 GetPos();
	RECT2 GetRect();
	void SetIsAsteroidHit(bool SetAsteroidHit);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	bool m_IsAsteroidHit;
	DOUBLE2 m_Pos,m_Direction;
	RECT2 m_CollissionRect;
	double m_Speed;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bullet(const Bullet& yRef);									
	Bullet& operator=(const Bullet& yRef);	
};

 
