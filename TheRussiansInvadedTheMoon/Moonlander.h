#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "BulletList.h"
#include "Bullet.h"

struct BlackHoleStats
{
	DOUBLE2 Blackhole1Pos;
	DOUBLE2 Blackhole2Pos;
	double Blackhole1Mass;
	double Blackhole2Mass;
};
/*
struct RECT2ARRAYSTRUCT
{
	RECT2 rect2struct1,
		  rect2struct2,
		  rect2struct3,
		  rect2struct4,
		  rect2struct5;
};*/
//-----------------------------------------------------
// Moonlander Class									
//-----------------------------------------------------
class Moonlander
{
public:
	Moonlander(int posX,int PosY);				// Constructor
	virtual ~Moonlander();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	bool Create(HitRegion * hitLevelPtr, HitRegion * hitFuelbasesPtr, RECT2ARRAYSTRUCT rectArrstruct,int health);
	void Tick(double deltaTime, DOUBLE2 cameraPos,BlackHoleStats blackholeStatsObject,int stateOfInfo, RECT2ARRAYSTRUCT russianbaseRectstruct);
	void KeyPressed();
	void MouseButtonAction(int x,int y);
	void Paint(MATRIX3X2 matView);
	DOUBLE2 GetPos();
	RECT2 GetRect();
	double GetFuel();
	void SetFuel(int fuel);
	void Decreasehealth();
	bool IsMoonlanderDead();
	RECT2 IsRussianBaseHit();

	

private: 
	//-------------------------------------------------
	// Own methods								
	//------------------------------------------------
	void Move(double deltaTime);
	void CollisionDetection();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int NUMBER_OF_FUELBASES = 5;
	Bitmap * m_BmpMoonlanderPtr, * m_BmpFirePtr, *m_BmpExplosionPtr;
	HitRegion * m_HitLevelPtr, * m_HitFuelbasesPtr;
	RECT2 m_RectMoonlander;
	RECT2 m_RectFuelBaseArr[NUMBER_OF_FUELBASES];
	RECT2ARRAYSTRUCT m_RectRussianBaseStruct;
	BulletList * m_BulletListPtr;
	DOUBLE2 m_Position
		   ,m_StartPos
		   ,m_Gravity
		   ,m_Velocity
		   ,m_Direction
		   ,m_FrictionForce
		   ,m_Acceleration
		   ,m_EngineForce
		   ,m_StartRay
		   ,m_RayVector
		   ,m_CameraPos
		   ,m_BlackHole1Force
		   ,m_BlackHole2Force
		   ,m_ProjectedRay
		   ,m_ReflectedRay;
	BlackHoleStats m_BlackholeStatsObject;
	double m_Angle
		  ,m_Speed
		  ,m_Fuel
		  ,m_ValueOfSpeed
		  ,m_Scale
		  ,m_AngularVelocity
		  ,m_K
		  ,m_G
		  ,m_Mass
		  ,m_SpaceShipOpacity
		  ,m_Radius1
		  ,m_Radius2
		  ,m_Radius3;
	bool m_BlDrawFire,m_BlackHoleHit,m_IsLevelHit,m_BlMoonlanderDead,m_BlMoonlanderExplode;
	int m_StateOfInfo,m_TickCounter,m_Health,m_AnimatedIndex;
	static const int STATE_SHOW_GUI=0,STATE_SHOW_KEYS=1,STATE_SHOW_DEBUG=2;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Moonlander(const Moonlander& yRef);									
	Moonlander& operator=(const Moonlander& yRef);	
};

 
