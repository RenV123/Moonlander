#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "BulletList.h"
#include "Bullet.h"

//-----------------------------------------------------
// RussianBase Class									
//-----------------------------------------------------
class RussianBase
{
public:
	RussianBase();				// Constructor
	virtual ~RussianBase();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	bool Create(int x, int y);
	void Tick(DOUBLE2 posCamera,double deltaTime, RECT2 moonlanderRect, int stateOfInfo);
	void Paint(MATRIX3X2 matView);
	DOUBLE2 GetPos();
	RECT2 GetRect();
	bool IsMoonlanderHit();
	void SetMoonlanderHit(bool hit);
	void Decreasehealth();
	bool IsRussianBaseReadytoDestroy();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Bitmap * m_BmpRussianBasePtr, *m_BmpRussianBaseGunPtr, *m_BmpExplosionPtr;
	DOUBLE2 m_Position;
	double m_AnimatedAngle,m_Tickcounter,m_TicksTillNextFire;
	bool m_BlRotateLeft,m_BlExplodeRussianBase,m_BlRussianBaseDead;
	BulletList * m_BulletListPtr;
	RECT2 m_RussianBaseRect;
	int m_StateOfInfo,m_Health,m_TickCounter,m_AnimatedIndex;
	static const int STATE_SHOW_GUI=0,STATE_SHOW_KEYS=1,STATE_SHOW_DEBUG=2;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	RussianBase(const RussianBase& yRef);									
	RussianBase& operator=(const RussianBase& yRef);	
};

 
