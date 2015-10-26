//-----------------------------------------------------------------
// Game File
// C++ Source - TheRussiansInvadedTheMoon.cpp - version v2_12 jan 2013 
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "TheRussiansInvadedTheMoon.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// TheRussiansInvadedTheMoon methods																				
//-----------------------------------------------------------------

TheRussiansInvadedTheMoon::TheRussiansInvadedTheMoon():
	m_MoonlanderPtr(nullptr),
	m_BmpBackgroundPtr(nullptr),
	m_HitLevelPtr(nullptr),
	m_HitFuelbasesPtr(nullptr),
	m_Blackhole1Ptr(nullptr),
	m_Blackhole2Ptr(nullptr),
	m_BmpAmericanFlag(nullptr),
	m_BlAmericanFlag(false),
	m_StateOfInfo(STATE_SHOW_GUI),
	m_Scale(1),
	m_CameraPos(0,480)
{
	for (int i = 0; i < NUMBER_OF_FUELBASES ; i++)
	{
		m_FuelBasePtrArr[i] = nullptr;
	}
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		m_RussianbasePtrArr[i] = nullptr;
	}
}

TheRussiansInvadedTheMoon::~TheRussiansInvadedTheMoon()																						
{

}

void TheRussiansInvadedTheMoon::GameInitialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::GameInitialize(hInstance);
	GAME_ENGINE->SetTitle("TheRussiansInvadedTheMoon - Vandamme René - 1DAE5");					
	GAME_ENGINE->RunGameLoop(true);

	// Set the optional values
	GAME_ENGINE->SetWidth(1280);
	GAME_ENGINE->SetHeight(720);
	GAME_ENGINE->SetKeyList(String("T") + (TCHAR) VK_CONTROL +(TCHAR) VK_SPACE);
}

void TheRussiansInvadedTheMoon::GameStart()
{
	//Create the Background
	m_BmpBackgroundPtr = new Bitmap(IDB_BACKGROUND);
	m_HitLevelPtr = new HitRegion();
	m_HitLevelPtr->CreateFromSVG("./resources/Backgroundhitregion.svg");

	//'merica
	m_BmpAmericanFlag = new Bitmap(IDB_AMERICANFLAG);

	//Fuelbases
	m_HitFuelbasesPtr = new HitRegion();
	m_HitFuelbasesPtr->CreateFromSVG("./resources/Fuelbaseshitregion.svg");

	//Create the Blackhole
	m_Blackhole1Ptr = new Blackhole();
	if(!m_Blackhole1Ptr->Create(2000,500,2000)) GAME_ENGINE->MessageBox(String("blackhole1 failed to create!"));

	m_Blackhole2Ptr = new Blackhole();
	if(!m_Blackhole2Ptr->Create(500,500,2000)) GAME_ENGINE->MessageBox(String("blackhole2 failed to create!"));

	//Create the RussianBase
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		m_RussianbasePtrArr[i] = new RussianBase();
	}
	if(!m_RussianbasePtrArr[0]->Create(400,820)) GAME_ENGINE->MessageBox(String("russianbase failed to create!"));
	if(!m_RussianbasePtrArr[1]->Create(1050,800)) GAME_ENGINE->MessageBox(String("russianbase failed to create!"));
	if(!m_RussianbasePtrArr[2]->Create(1737,800)) GAME_ENGINE->MessageBox(String("russianbase failed to create!"));
	if(!m_RussianbasePtrArr[3]->Create(2320,817)) GAME_ENGINE->MessageBox(String("russianbase failed to create!"));
	if(!m_RussianbasePtrArr[4]->Create(2980,840)) GAME_ENGINE->MessageBox(String("russianbase failed to create!"));



	//	fill m_BlackholeStatsObject
	m_BlackholeStatsObject.Blackhole1Mass=m_Blackhole1Ptr->getMass();
	m_BlackholeStatsObject.Blackhole1Pos=m_Blackhole1Ptr->getPos();
	m_BlackholeStatsObject.Blackhole2Mass=m_Blackhole2Ptr->getMass();
	m_BlackholeStatsObject.Blackhole2Pos=m_Blackhole2Ptr->getPos();


	//Create FuelBases
	m_FuelBasePtrArr[0] = new Fuelbase();
	m_FuelBasePtrArr[1] = new Fuelbase();
	m_FuelBasePtrArr[2] = new Fuelbase();
	m_FuelBasePtrArr[3] = new Fuelbase();
	m_FuelBasePtrArr[4] = new Fuelbase();
	if(!m_FuelBasePtrArr[0]->Create(230,855,90))  GAME_ENGINE->MessageBox(String("fuelbase failed to create!"));
	if(!m_FuelBasePtrArr[1]->Create(885,828,90)) GAME_ENGINE->MessageBox(String(" fuelbase failed to create!"));
	if(!m_FuelBasePtrArr[2]->Create(1537,812,90)) GAME_ENGINE->MessageBox(String("fuelbase failed to create!"));
	if(!m_FuelBasePtrArr[3]->Create(2165,827,90)) GAME_ENGINE->MessageBox(String("fuelbase failed to create!"));
	if(!m_FuelBasePtrArr[4]->Create(2809,850,90)) GAME_ENGINE->MessageBox(String("fuelbase failed to create!"));

	RECT2ARRAYSTRUCT rect2ArrstructFuel;
	rect2ArrstructFuel.rect2struct1 = m_FuelBasePtrArr[0]->GetRect();
	rect2ArrstructFuel.rect2struct2 = m_FuelBasePtrArr[1]->GetRect();
	rect2ArrstructFuel.rect2struct3 = m_FuelBasePtrArr[2]->GetRect();
	rect2ArrstructFuel.rect2struct4 = m_FuelBasePtrArr[3]->GetRect();
	rect2ArrstructFuel.rect2struct5 = m_FuelBasePtrArr[4]->GetRect();

	m_MoonlanderPtr = new Moonlander(310,820); //50,862  
	if(!m_MoonlanderPtr->Create(m_HitLevelPtr,m_HitFuelbasesPtr, rect2ArrstructFuel,500)) GAME_ENGINE->MessageBox(String("moonlander failed to create!"));
}

void TheRussiansInvadedTheMoon::GameEnd()
{
	//remove the moonlander
	delete m_MoonlanderPtr;
	m_MoonlanderPtr = nullptr;

	//Remove the Background
	delete m_BmpBackgroundPtr;
	m_BmpBackgroundPtr= nullptr;
	delete m_HitLevelPtr;
	m_HitLevelPtr = nullptr;

	//remove the American Flag
	delete m_BmpAmericanFlag;
	m_BmpAmericanFlag = nullptr;

	//remove the blackhole1
	delete m_Blackhole1Ptr;
	m_Blackhole1Ptr = nullptr;

	//remove the blackhole2
	delete m_Blackhole2Ptr;
	m_Blackhole2Ptr = nullptr;


	//remove the Russianbase
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		if(m_RussianbasePtrArr[i] != nullptr)
		{
			delete m_RussianbasePtrArr[i];
			m_RussianbasePtrArr[i] = nullptr;
		}
	}

	//remove the Fuelbases
	for (int i = 0; i < NUMBER_OF_FUELBASES ; i++)
	{
		delete m_FuelBasePtrArr[i];
		m_FuelBasePtrArr[i] = nullptr;
	}
}

void TheRussiansInvadedTheMoon::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	


	if (isLeft == true && isDown == true) 
	{	
		if ( x >= 0 && x <= m_BmpBackgroundPtr->GetWidth() ) 
		{
			if ( y >= 0 && y <= m_BmpBackgroundPtr->GetHeight() ) 
			{
				m_MoonlanderPtr->MouseButtonAction(x,y);
			}
		}
	}

}
//
//void TheRussiansInvadedTheMoon::MouseMove(int x, int y, WPARAM wParam)
//{	
//	// Insert the code that needs to be executed when the mouse pointer moves across the game window
//
//	/* Example:
//	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
//	{
//		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
//		{
//			GAME_ENGINE->MessageBox("Da mouse wuz here.");
//		}
//	}
//	*/
//
//}
//
//void TheRussiansInvadedTheMoon::CheckKeyboard()
//{	
//	// Here you can check if a key of choice is held down
//	// Is executed once per frame 
//
//	/* Example:
//	if (GAME_ENGINE->IsKeyDown('K')) xIcon -= xSpeed;
//	if (GAME_ENGINE->IsKeyDown('L')) yIcon += xSpeed;
//	if (GAME_ENGINE->IsKeyDown('M')) xIcon += xSpeed;
//	if (GAME_ENGINE->IsKeyDown('O')) yIcon -= ySpeed;
//	*/
//}
//
void TheRussiansInvadedTheMoon::KeyPressed(TCHAR cKey)
{	
	switch (cKey)
	{
	case VK_SPACE:
		m_MoonlanderPtr->KeyPressed();
		break;
	case VK_CONTROL:
		m_StateOfInfo++;
		if(m_StateOfInfo>2) m_StateOfInfo=STATE_SHOW_GUI; 
		break;
	}

}

void TheRussiansInvadedTheMoon::GameTick(double deltaTime)
{
	//Destroy Russianbases if possible
	RECT2 russianbaseHitRect = m_MoonlanderPtr->IsRussianBaseHit();
	if(russianbaseHitRect.left !=0)
	{
		for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
		{
			if(m_RussianbasePtrArr[i] != nullptr)
			{
				if(m_RussianbasePtrArr[i]->GetRect().left == russianbaseHitRect.left)
				{
					m_RussianbasePtrArr[i]->Decreasehealth();
				}
			}

		}
	}
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		if(m_RussianbasePtrArr[i] != nullptr)
		{
			if(m_RussianbasePtrArr[i]->IsRussianBaseReadytoDestroy() == true)
			{
				delete m_RussianbasePtrArr[i];
				m_RussianbasePtrArr[i] = nullptr;
			}
		}
	}
	if(m_RussianbasePtrArr[4] == nullptr)
	{
		m_BlAmericanFlag=true;
	}
	//Tick moonlander
	//Create Moonlander		
	RECT2ARRAYSTRUCT rect2ArrstructRussianBase;
	if(m_RussianbasePtrArr[0] != nullptr)rect2ArrstructRussianBase.rect2struct1 = m_RussianbasePtrArr[0]->GetRect();
	else rect2ArrstructRussianBase.rect2struct1= RECT2(-3,-3,-1,-1);
	if(m_RussianbasePtrArr[1] != nullptr)rect2ArrstructRussianBase.rect2struct2 = m_RussianbasePtrArr[1]->GetRect();
	else rect2ArrstructRussianBase.rect2struct1= RECT2(-3,-3,-1,-1);
	if(m_RussianbasePtrArr[2] != nullptr)rect2ArrstructRussianBase.rect2struct3 = m_RussianbasePtrArr[2]->GetRect();
	else rect2ArrstructRussianBase.rect2struct1= RECT2(-3,-3,-1,-1);
	if(m_RussianbasePtrArr[3] != nullptr)rect2ArrstructRussianBase.rect2struct4 = m_RussianbasePtrArr[3]->GetRect();
	else rect2ArrstructRussianBase.rect2struct1= RECT2(-3,-3,-1,-1);
	if(m_RussianbasePtrArr[4] != nullptr)rect2ArrstructRussianBase.rect2struct5 = m_RussianbasePtrArr[4]->GetRect();
	else rect2ArrstructRussianBase.rect2struct1= RECT2(-3,-3,-1,-1);
	m_MoonlanderPtr->Tick(deltaTime,m_CameraPos,m_BlackholeStatsObject,m_StateOfInfo,rect2ArrstructRussianBase);

	if(deltaTime>0.3) deltaTime=0.1;

	SpaceShipFuelbaseIntersect();
	//Tick BlackHole1
	m_Blackhole1Ptr->Tick(deltaTime);

	//Tick BlackHole2
	m_Blackhole2Ptr->Tick(deltaTime);

	//Tick RussianBase
	RECT2 moonlanderRect = m_MoonlanderPtr->GetRect();
	//remove the Russianbase
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		if(m_RussianbasePtrArr[i] != nullptr)
		{
			m_RussianbasePtrArr[i]->Tick(m_CameraPos,deltaTime,moonlanderRect,m_StateOfInfo);
		}
	}

	//Camera

	DOUBLE2 mlanderPos = m_MoonlanderPtr->GetPos();
	m_CameraPos= DOUBLE2(mlanderPos.x-GAME_ENGINE->GetWidth()/2,mlanderPos.y-GAME_ENGINE->GetHeight()/2);
	if(m_CameraPos.x<0) m_CameraPos.x=0;
	if(m_CameraPos.x>m_BmpBackgroundPtr->GetWidth()-GAME_ENGINE->GetWidth()) m_CameraPos.x=m_BmpBackgroundPtr->GetWidth()-GAME_ENGINE->GetWidth();
	if(m_CameraPos.y<0) m_CameraPos.y=0;
	if(m_CameraPos.y>m_BmpBackgroundPtr->GetHeight()-GAME_ENGINE->GetHeight()) m_CameraPos.y=m_BmpBackgroundPtr->GetHeight()-GAME_ENGINE->GetHeight();

	//Scale Camera
	if(GAME_ENGINE->IsKeyDown('O')) m_Scale+=0.1;
	if(GAME_ENGINE->IsKeyDown('P')) m_Scale-=0.1;
	if(GAME_ENGINE->IsKeyDown(VK_NUMPAD8)) m_CameraPos.y-=5;
	if(GAME_ENGINE->IsKeyDown(VK_NUMPAD2)) m_CameraPos.y+=5;
	if(GAME_ENGINE->IsKeyDown(VK_NUMPAD4)) m_CameraPos.x-=5;
	if(GAME_ENGINE->IsKeyDown(VK_NUMPAD6)) m_CameraPos.x+=5;
	if(GAME_ENGINE->IsKeyDown('R'))
	{
		m_Scale=1;
		DOUBLE2 mlanderPos = m_MoonlanderPtr->GetPos();
		m_CameraPos= DOUBLE2(mlanderPos.x-GAME_ENGINE->GetWidth()/2,mlanderPos.y-GAME_ENGINE->GetHeight()/2);
	}

	//Check Bullets
	//remove health
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		if(m_RussianbasePtrArr[i] != nullptr)
		{
			if(m_RussianbasePtrArr[i]->IsMoonlanderHit())
			{
				m_MoonlanderPtr->Decreasehealth(); 
				m_RussianbasePtrArr[i]->SetMoonlanderHit(false);
			}
		}
	}

	if(m_MoonlanderPtr->IsMoonlanderDead()==true)
	{
		GameEnd();
		GameStart();
	}
	if(GAME_ENGINE->IsKeyDown(VK_RETURN) == true && m_BlAmericanFlag==true)
	{
		GameEnd();
		GameStart();
		m_BlAmericanFlag=false;
	}


}

void TheRussiansInvadedTheMoon::GamePaint(RECT rect)
{
	//Create the Camera;
	MATRIX3X2 matCamera,matView,matScale;
	matCamera.SetAsTranslate(m_CameraPos);
	matView = matCamera.Inverse();
	matScale.SetAsScale(m_Scale);
	matView = matView*matScale;

	//Paint Background
	GAME_ENGINE->SetTransformMatrix(matView);
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr,0,0);

	//Paint Hitregion
	if(m_StateOfInfo==STATE_SHOW_DEBUG)
	{
		GAME_ENGINE->SetColor(COLOR(255,0,0,100));
		GAME_ENGINE->FillHitRegion(m_HitLevelPtr);
	}

	//Paint BlackHole1
	m_Blackhole1Ptr->Paint(matView);

	//Paint BlackHole2
	m_Blackhole2Ptr->Paint(matView);

	//Paint Russianbase
	for (int i = 0; i < NUMBER_OF_RUSSIANBASES ; i++)
	{
		if(m_RussianbasePtrArr[i] != nullptr)
		{
			m_RussianbasePtrArr[i]->Paint(matView);
		}
	}

	//Paint moonlander
	m_MoonlanderPtr->Paint(matView);


	//Paint Keys
	if(m_StateOfInfo==STATE_SHOW_KEYS)
	{
		GAME_ENGINE->SetTransformMatrix(MATRIX3X2::CreateIdentityMatrix());
		GAME_ENGINE->SetColor(COLOR(255,0,255));
		GAME_ENGINE->DrawString(String("Press the spacebar to shoot ") +
			String("\nPress up,left or right to move ") +
			String("\nPress A Z to toggle universal Gravitation (Debug mode only) ") +
			String("\nPress G H to toggle Gravitation (Debug mode only) "),200,10);
	}

	if(m_BlAmericanFlag == true)
	{
		MATRIX3X2 matCenter, matTranslate;
		matCenter.SetAsTranslate(-m_BmpAmericanFlag->GetWidth()/2,-m_BmpAmericanFlag->GetHeight()/2);
		matTranslate.SetAsTranslate(GAME_ENGINE->GetWidth()/2,GAME_ENGINE->GetHeight()/2);
		GAME_ENGINE->SetTransformMatrix(matCenter*matTranslate);
		GAME_ENGINE->DrawBitmap(m_BmpAmericanFlag,0,0);
	}

	//Paint fuelbase
	for (int i = 0; i < NUMBER_OF_FUELBASES; i++)
	{
		m_FuelBasePtrArr[i]->Paint(matView);
	}
}

void TheRussiansInvadedTheMoon::SpaceShipFuelbaseIntersect()
{
	RECT2 fuelbaseRect , spaceshipRect ;
	spaceshipRect = m_MoonlanderPtr->GetRect();

	for (int i = 0; i < NUMBER_OF_FUELBASES ; i++)
	{
		fuelbaseRect = m_FuelBasePtrArr[i]->GetRect();
		if(RectIntersectTest(fuelbaseRect,spaceshipRect)) 
		{
			double fuelinBase = m_FuelBasePtrArr[i]->GetFuel();
			double fuelinMoonlander = m_MoonlanderPtr->GetFuel();
			double fuelToRemove = 50-fuelinMoonlander; //50 is max  fuel

			if(fuelinMoonlander<50) 
			{
				if(fuelToRemove<fuelinBase)
				{
					m_FuelBasePtrArr[i]->RemoveFuel(fuelToRemove);
					m_MoonlanderPtr->SetFuel(50);
				}
				else
				{
					m_MoonlanderPtr->SetFuel(fuelinBase+fuelinMoonlander);
					m_FuelBasePtrArr[i]->RemoveFuel(fuelinBase);
				}
			}

		}
	}
}
bool TheRussiansInvadedTheMoon::RectIntersectTest(RECT2 r1, RECT2 r2)
{
	bool noIntersect=
		r1.right < r2.left || r1.left> r2.right ||
		r1.top> r2.bottom || r1.bottom < r2.top;
	return !noIntersect;
}





