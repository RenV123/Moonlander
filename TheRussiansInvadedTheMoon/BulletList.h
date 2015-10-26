#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Bullet.h"
#include "RussianBaseBullet.h"


struct RECT2ARRAYSTRUCT
{
	RECT2 rect2struct1,
		rect2struct2,
		rect2struct3,
		rect2struct4,
		rect2struct5;
};
//-----------------------------------------------------
// BulletList Class									
//-----------------------------------------------------
class BulletList
{
public:
	BulletList();				// Constructor
	virtual ~BulletList();		// Destructor

	bool AddBullet(Bullet* BulletPtr);
	bool RemoveBullet(Bullet* BulletPtr);
	bool AddRussianBaseBullet(RussianBaseBullet* BulletPtr);
	bool RemoveRussianBaseBullet(RussianBaseBullet* BulletPtr);
	void RemoveAll();
	int GetSizeOfBullets();
	int GetSizeOfRussianBaseBullet();
	void Tick(DOUBLE2 PosCamera, double deltaTime, RECT2 targetRect );
	void Tick(DOUBLE2 PosCamera, double deltaTime, RECT2ARRAYSTRUCT targetRectArrStruct);
	void Paint(MATRIX3X2 matView,MATRIX3X2 matRotate);
	Bullet * GetBulletPtrArr();
	RussianBaseBullet * GetRussianBaseBulletPtrArr(); 
	bool IsTargetHit();
	RECT2 IsRussianBaseHit();
	void setTargetHit(bool targetHit);
private: 
	bool RectIntersectTest(RECT2 r1, RECT2 r2);
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int MAX_NR_OF_BULLETS = 100, NUMBER_OF_RUSSIANBASE =5;
	Bullet * m_BulletPtrArr[MAX_NR_OF_BULLETS];
	RussianBaseBullet * m_RussianBaseBulletPtrArr[MAX_NR_OF_BULLETS];
	bool m_BulletIsHit;
	RECT2 m_TargetRect, m_RussianBaseRectArr[NUMBER_OF_RUSSIANBASE];
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BulletList(const BulletList& yRef);									
	BulletList& operator=(const BulletList& yRef);	
};

 
