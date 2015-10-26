//-----------------------------------------------------------------
// Game File
// C++ Source - TheRussiansInvadedTheMoon.h - version v2_12 jan 2013 
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Student data
// Name:
// Group:
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"
#include "Moonlander.h"
#include "Blackhole.h"
#include "Russianbase.h"
#include "Fuelbase.h"
//-----------------------------------------------------------------
// TheRussiansInvadedTheMoon Class																
//-----------------------------------------------------------------
class TheRussiansInvadedTheMoon : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	TheRussiansInvadedTheMoon();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~TheRussiansInvadedTheMoon();

	//---------------------------
	// General Methods
	//---------------------------

	void GameInitialize(HINSTANCE hInstance);
	void GameStart();				
	void GameEnd();
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	//void MouseMove(int x, int y, WPARAM wParam);
	//void CheckKeyboard();
	void KeyPressed(TCHAR cKey);
	void GameTick(double deltaTime);
	void GamePaint(RECT rect);

	//void CallAction(Caller* callerPtr);

	// -------------------------
	// Member functions
	// -------------------------

private:
	// -------------------------
	// Member functions
	// -------------------------
	void SpaceShipFuelbaseIntersect();
	bool RectIntersectTest(RECT2 r1, RECT2 r2);
	// -------------------------
	// Datamembers
	// -------------------------
	static const int NUMBER_OF_FUELBASES=5, NUMBER_OF_RUSSIANBASES=5;
	Moonlander * m_MoonlanderPtr;
	Bitmap * m_BmpBackgroundPtr, *m_BmpAmericanFlag;
	HitRegion * m_HitLevelPtr, *m_HitFuelbasesPtr;
	DOUBLE2 m_CameraPos;
	Blackhole * m_Blackhole1Ptr,
			  * m_Blackhole2Ptr;
	RussianBase * m_RussianbasePtrArr[NUMBER_OF_RUSSIANBASES];
	BlackHoleStats m_BlackholeStatsObject;
	
	
	Fuelbase * m_FuelBasePtrArr[NUMBER_OF_FUELBASES];
	double m_Scale;
	int m_StateOfInfo;
	bool m_BlAmericanFlag;
	static const int STATE_SHOW_GUI=0,STATE_SHOW_KEYS=1,STATE_SHOW_DEBUG=2;
						
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	TheRussiansInvadedTheMoon(const TheRussiansInvadedTheMoon& tRef);
	TheRussiansInvadedTheMoon& operator=(const TheRussiansInvadedTheMoon& tRef);
};
