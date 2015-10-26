//---------------------------
// Includes
//---------------------------
#include "Moonlander.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Moonlander::Moonlander(int posX,int PosY): 
	m_BmpMoonlanderPtr(nullptr),
	m_BmpFirePtr(nullptr),
	m_HitLevelPtr(nullptr),
	m_HitFuelbasesPtr(nullptr),
	m_BulletListPtr(nullptr),
	m_BmpExplosionPtr(nullptr),
	m_Position(posX,PosY),
	m_StartPos(posX,PosY),
	m_Velocity(0,0),
	m_Gravity(0,40),
	m_Direction(0,0),
	m_Acceleration(0,0),
	m_EngineForce(0,0),
	m_StartRay(0,0),
	m_RayVector(0,0),
	m_BlackHole1Force(0,0),
	m_BlackHole2Force(0,0),
	m_CameraPos(0,0),
	m_ProjectedRay(0,0),
	m_ReflectedRay(0,0),
	m_K(20),
	m_G(2000), 
	m_Mass(10),
	m_Angle(0),
	m_Scale(1),
	m_Speed(0),
	m_Health(0),
	m_ValueOfSpeed(1500),
	m_AngularVelocity(3),
	m_SpaceShipOpacity(1),
	m_Radius1(0),
	m_Radius2(0),
	m_Radius3(0),
	m_BlMoonlanderDead(false),
	m_Fuel(50),
	m_TickCounter(0),
	m_AnimatedIndex(0),
	m_RectRussianBaseStruct(),
	m_BlDrawFire(false),
	m_BlackHoleHit(false),
	m_IsLevelHit(false),
	m_StateOfInfo(STATE_SHOW_GUI),
	m_BlackholeStatsObject()
{
	for (int i = 0; i < NUMBER_OF_FUELBASES ; i++)
	{
		m_RectFuelBaseArr[i] = RECT2();
	}
}
Moonlander::~Moonlander()
{
	delete m_BmpMoonlanderPtr;
	m_BmpMoonlanderPtr = nullptr;

	delete m_BmpFirePtr;
	m_BmpFirePtr = nullptr;

	m_BulletListPtr->RemoveAll();
	delete m_BulletListPtr;
	m_BulletListPtr = nullptr;

	delete m_BmpExplosionPtr;
	m_BmpExplosionPtr = nullptr;
}

//---------------------------
// Own methods
//---------------------------
bool Moonlander::Create(HitRegion * hitLevelPtr,HitRegion * hitFuelbasesPtr, RECT2ARRAYSTRUCT rectArrstruct, int health)
{
	// fill up the array of rects
	m_RectFuelBaseArr[0] = rectArrstruct.rect2struct1;
	m_RectFuelBaseArr[1] = rectArrstruct.rect2struct2;
	m_RectFuelBaseArr[2] = rectArrstruct.rect2struct3;
	m_RectFuelBaseArr[3] = rectArrstruct.rect2struct4;
	m_RectFuelBaseArr[4] = rectArrstruct.rect2struct5;


	m_Health = health;

	//Create Bitmap Moonlander
	m_BmpMoonlanderPtr = new Bitmap(IDB_MOONLANDER);
	if(!m_BmpMoonlanderPtr->Exists()) return false;
	m_BmpMoonlanderPtr->SetTransparencyColor(255,0,255);

	//Create FireBitmap
	m_BmpFirePtr = new Bitmap(IDB_FIRE);
	if(!m_BmpFirePtr->Exists()) return false;
	m_BmpFirePtr->SetTransparencyColor(255,0,255);

	//Create ExplosionBitmap
	m_BmpExplosionPtr = new Bitmap(IDB_EXPLOSION);
	m_BmpExplosionPtr->SetTransparencyColor(255,0,255);

	m_HitLevelPtr=hitLevelPtr;
	m_HitFuelbasesPtr=hitFuelbasesPtr;
	//Create BulletList
	m_BulletListPtr = new BulletList();
	return true;
}
void Moonlander::Tick(double deltaTime, DOUBLE2 cameraPos,BlackHoleStats blackholeStatsObject,int stateOfInfo, RECT2ARRAYSTRUCT russianbaseRectstruct)
{

	m_RectRussianBaseStruct = russianbaseRectstruct;

	//Check if Moonlander should explode
	if(m_Health==0) m_BlMoonlanderExplode=true;
	//Exploding clip
	if(m_BlMoonlanderExplode==true)
	{
		m_TickCounter++;
		if(m_TickCounter%5 ==0)
		{
			m_AnimatedIndex++;
		}
		if(m_AnimatedIndex>4)
		{
			m_BlMoonlanderDead=true;
			m_AnimatedIndex=0;
		}
	}
	
	//update rect2
	m_RectMoonlander = RECT2(m_Position.x-m_BmpMoonlanderPtr->GetWidth()/2   , 

		m_Position.y-m_BmpMoonlanderPtr->GetHeight()/2  ,
		m_Position.x + m_BmpMoonlanderPtr->GetWidth()/2 , 
		m_Position.y+m_BmpMoonlanderPtr->GetHeight()/2 );

	m_CameraPos=cameraPos;
	m_BlackholeStatsObject = blackholeStatsObject;
	m_StateOfInfo=stateOfInfo;
	//Bullets
	m_BulletListPtr->Tick(m_CameraPos,deltaTime,m_RectRussianBaseStruct);

	Move(deltaTime);
	//Limit the Angle to positive values
	if(m_Angle<0) m_Angle+=(M_PI*2);
	if(m_Angle>(M_PI*2)) m_Angle-=(M_PI*2);

}
void Moonlander::KeyPressed()
{
	//The bullet use Cartesian Coordinates we have polar coordinates 
	double radius=sqrt(m_BmpMoonlanderPtr->GetWidth()/2*m_BmpMoonlanderPtr->GetWidth()/2 +m_BmpMoonlanderPtr->GetHeight()/2*m_BmpMoonlanderPtr->GetHeight()/2);
	DOUBLE2 direction = DOUBLE2(radius*cos(m_Angle-M_PI_2),radius*sin(m_Angle-M_PI_2)); //converting from pl cc
	Bullet * bulletPtr;
	DOUBLE2 FirePosition = m_Position + direction;
	bulletPtr=new Bullet(FirePosition.x,FirePosition.y ,direction.x,direction.y);
	m_BulletListPtr->AddBullet(bulletPtr);
}
void Moonlander::MouseButtonAction(int x,int y)
{

/*
	if(x+m_CameraPos.x >= m_Position.x-m_BmpMoonlanderPtr->GetWidth()/2 && x +m_CameraPos.x  < m_Position.x+m_BmpMoonlanderPtr->GetWidth()/2)
	{
		if(y +m_CameraPos.y >= m_Position.y-m_BmpMoonlanderPtr->GetHeight()/2 && y +m_CameraPos.y < m_Position.y+m_BmpMoonlanderPtr->GetHeight()/2)
		{
			m_BlIsMoonlanderActive=true;
		}
		else
		{
			m_BlIsMoonlanderActive=false;
		}
	}
	else
	{
		m_BlIsMoonlanderActive=false;
	}*/


}
void Moonlander::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matCenter,matRotate,matScale,matTranslate;
	matCenter.SetAsTranslate(-m_BmpMoonlanderPtr->GetWidth()/2,-m_BmpMoonlanderPtr->GetHeight()/2);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matTranslate.SetAsTranslate(m_Position.x,m_Position.y);
	GAME_ENGINE->SetTransformMatrix(matCenter*matRotate*matScale*matTranslate*matView);

	GAME_ENGINE->DrawBitmap(m_BmpMoonlanderPtr,0,0);
	//Draw Fire
	if(m_BlDrawFire==true)
	{
		matCenter.SetAsTranslate(-m_BmpMoonlanderPtr->GetWidth()/2+12,-m_BmpMoonlanderPtr->GetHeight()/2+61); //12 and 61 are the objectspacedcoordinates of the fire
		matTranslate.SetAsTranslate(m_Position.x,m_Position.y); 
		GAME_ENGINE->SetTransformMatrix(matCenter*matRotate*matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpFirePtr,0,0);
	}

	//Draw Bullets
	m_BulletListPtr->Paint(matView,matRotate);

	//Draw Explosion
	if(m_BlMoonlanderExplode == true)
	{
		RECT clip;
		clip.left =  (m_BmpExplosionPtr->GetWidth()/5)* m_AnimatedIndex;
		clip.right = clip.left  + m_BmpExplosionPtr->GetWidth()/5;
		clip.top = 0;
		clip.bottom = clip.top + m_BmpExplosionPtr->GetHeight();

		matCenter.SetAsTranslate(-m_BmpExplosionPtr->GetWidth()/10,-m_BmpExplosionPtr->GetHeight()/2);
		matRotate.SetAsRotate(m_Angle);
		matScale.SetAsScale(1.2);
		matTranslate.SetAsTranslate(m_Position.x,m_Position.y);
		GAME_ENGINE->SetTransformMatrix(matCenter*matRotate*matScale*matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpExplosionPtr,0,0,clip);
	}

	//Reset 
	GAME_ENGINE->SetTransformMatrix(matView);

	//Draw Health Bar and fuel
	GAME_ENGINE->SetTransformMatrix(MATRIX3X2::CreateIdentityMatrix());
	GAME_ENGINE->SetColor(COLOR(255,0,0));
	if(m_Health>0.1)GAME_ENGINE->FillRect(11,11,(m_Health/5)+1,31);
	GAME_ENGINE->SetColor(COLOR(0,0,0));
	GAME_ENGINE->DrawRect(10,10,50*2,30,3.0);
	GAME_ENGINE->DrawString(String("HEATLH"),12,11);

	GAME_ENGINE->SetColor(COLOR(255,255,0));
	GAME_ENGINE->FillRect(11,51,11+((m_Fuel)*1.8),71);
	GAME_ENGINE->SetColor(COLOR(0,0,0));
	GAME_ENGINE->DrawRect(10,50,50*2,70,3.0);
	GAME_ENGINE->DrawString(String("FUEL"),12,51);

	//DebugPaint
	if(m_StateOfInfo==STATE_SHOW_DEBUG)
	{
		//Draw Rays
		GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(COLOR(255,255,255,100));
		GAME_ENGINE->DrawLine(m_StartRay,m_StartRay+m_RayVector,3.0);
		GAME_ENGINE->DrawLine(m_Position,m_Position + m_Velocity,3.0);

		//Draw Info
		GAME_ENGINE->SetTransformMatrix(MATRIX3X2::CreateIdentityMatrix());
		GAME_ENGINE->SetColor(COLOR(255,0,255));
		GAME_ENGINE->DrawString(String("m_Position: ")+ m_Position.ToString() +
			String("\nm_Gravity: ")+m_Gravity.ToString() +
			String("\nm_Velocity: ")+m_Velocity.ToString()+
			String("\nm_Direction: ")+m_Direction.ToString() +
			String("\nm_ValueOfSpeed: ")+m_ValueOfSpeed,200,10);

		GAME_ENGINE->DrawString(String("m_Angle: ")+m_Angle +
			String("\nm_Acceleration: ")+m_Acceleration.ToString() +
			String("\nm_EngineForce: ")+m_EngineForce.ToString() +
			String("\nm_FrictionForce: ")+m_FrictionForce.ToString(),400,10);

		GAME_ENGINE->DrawString(String("m_G: ")+m_G +
			String("\nm_BlackHole1Force: ")+m_BlackHole1Force.ToString() +
			String("\nm_BlackHole2Force: ")+m_BlackHole2Force.ToString() +
			String("\nm_Radius1: ")+m_Radius1 +
			String("\nm_Radius2: ")+m_Radius2 + 
			String("\nm_Radius3: ")+m_Radius3 +
			String("\nm_Fuel: ")+m_Fuel +
			String("\nm_Health: ")+m_Health,620,10);
	}

}
void Moonlander::Move(double deltaTime)
{
	//--------------------------------------------------------------------------
	//Debug
	//--------------------------------------------------------------------------
	//Reset Moonlander
	if(GAME_ENGINE->IsKeyDown('R'))
	{
		m_Position=m_StartPos;
		m_Velocity=DOUBLE2(0,0);
		m_Direction=DOUBLE2(0,0);
		m_Acceleration=DOUBLE2(0,0);
		m_Angle=0;
		m_Scale=1;
		m_Fuel = 50;
		m_SpaceShipOpacity=1;
		m_BmpMoonlanderPtr->SetOpacity(m_SpaceShipOpacity);
		m_BmpFirePtr->SetOpacity(m_SpaceShipOpacity);
	}

	if(m_StateOfInfo==STATE_SHOW_DEBUG)
	{
		if(GAME_ENGINE->IsKeyDown('G')) m_Gravity.y=0;
		if(GAME_ENGINE->IsKeyDown('H')) m_Gravity.y=40;

		if(GAME_ENGINE->IsKeyDown('A')) m_G=1;
		if(GAME_ENGINE->IsKeyDown('Z')) m_G=2000;
	}



	//--------------------------------------------------------------------------
	//Calculate The gravitational Force between the SpaceShip and the Blackhole1
	//--------------------------------------------------------------------------
	//Calculate the radius between the blackhole and SpaceShip
	m_Radius1 = (m_Position - m_BlackholeStatsObject.Blackhole1Pos).Length();
	//calculate the Force
	double ForcebetweenMasses = m_G*((m_Mass*m_BlackholeStatsObject.Blackhole1Mass)/(m_Radius1*m_Radius1));
	// The Force is strong with this one. we must limit it!
	if(ForcebetweenMasses>5000) ForcebetweenMasses = 5000;

	//Calculate the direction 
	DOUBLE2 directionToBlackhole = (m_BlackholeStatsObject.Blackhole1Pos-m_Position).Normalized();
	//no friction yet
	if(m_Radius1<70 || m_BlackHoleHit==true)
	{
		m_BlackHoleHit=true;
		m_SpaceShipOpacity*=0.9;
		m_Scale*=0.9;
		m_BmpMoonlanderPtr->SetOpacity(m_SpaceShipOpacity);
		m_BmpFirePtr->SetOpacity(m_SpaceShipOpacity);
		if(m_SpaceShipOpacity<0.1)
		{
			m_BlackHoleHit=false;
			m_Scale=1;
			m_SpaceShipOpacity=1;
			m_BmpMoonlanderPtr->SetOpacity(m_SpaceShipOpacity);
			m_BmpFirePtr->SetOpacity(m_SpaceShipOpacity);
			m_Position = m_BlackholeStatsObject.Blackhole2Pos;
			m_Velocity=DOUBLE2(0,0);
		}
	}
	//Limit the force based on the radius
	if(m_Radius1<400) m_BlackHole1Force = ForcebetweenMasses*directionToBlackhole;
	else m_BlackHole1Force = DOUBLE2(0,0);

	//--------------------------------------------------------------------------
	//Calculate The gravitational Force between the SpaceShip and the Blackhole2
	//--------------------------------------------------------------------------
	m_Radius2 = (m_Position - m_BlackholeStatsObject.Blackhole2Pos).Length();
	if(m_G==0) m_G =1;
	ForcebetweenMasses = (-m_G)*((m_Mass*m_BlackholeStatsObject.Blackhole2Mass)/(m_Radius2*m_Radius2));
	//cout << ForcebetweenMasses << endl;
	if(ForcebetweenMasses<-5000) ForcebetweenMasses=-5000;
	directionToBlackhole = (m_BlackholeStatsObject.Blackhole2Pos-m_Position).Normalized();

	//Limit the force based on the radius
	if(m_Radius2<400) m_BlackHole2Force = ForcebetweenMasses*directionToBlackhole;
	else m_BlackHole2Force = DOUBLE2(0,0);

	//-------------------------------------------------------------------------
	//SpaceShip calculations
	//-------------------------------------------------------------------------
	//Calculate angularVelocity 
	double step=m_AngularVelocity*deltaTime;
	//Calculate Direction of Spaceship based on angle
	m_Radius3=sqrt(m_BmpMoonlanderPtr->GetWidth()/2*m_BmpMoonlanderPtr->GetWidth()/2 +m_BmpMoonlanderPtr->GetHeight()/2*m_BmpMoonlanderPtr->GetHeight()/2); //Pythagoras 
	m_Direction = DOUBLE2(m_Radius3*cos(m_Angle-M_PI_2),m_Radius3*sin(m_Angle-M_PI_2)); //converting from pl cc
	m_Direction = m_Direction.Normalized();
	//Calculate The FrictionForce
	m_FrictionForce = m_K*(-m_Velocity.Normalized());
	if(m_Radius1<50) //spaceship afremmen in het zwarte gat met frictionforce
	{
		m_FrictionForce = 100*(-m_Velocity);
	}
	//Reset Speed and DrawFire if not key is pressed
	m_Speed=0;
	m_BlDrawFire=false;
	if(GAME_ENGINE->IsKeyDown(VK_LEFT)) 
	{
		m_Angle-=step;
		//m_blDrawFire=true;
	}
	if(GAME_ENGINE->IsKeyDown(VK_RIGHT))
	{
		m_Angle+=step;
		//m_blDrawFire=true;
	}
	if(GAME_ENGINE->IsKeyDown(VK_UP)) 
	{
		if(m_Fuel>0)
		{
			m_Speed = m_ValueOfSpeed;
			m_BlDrawFire=true;
		}

	}  
	//Calculate amount of fuel burned
	if(m_StateOfInfo != STATE_SHOW_DEBUG) m_Fuel -=m_Speed/40000;
	//cout << m_Speed/25000 << endl;
	//Apply Gravity and calculate the new EngineForce
	m_EngineForce=m_Speed*m_Direction;
	m_Acceleration=(m_BlackHole1Force+m_BlackHole2Force+m_EngineForce+m_FrictionForce)/m_Mass;
	DOUBLE2 sumOfAccelerations = m_Acceleration+m_Gravity;
	m_Velocity+=sumOfAccelerations*deltaTime;
	CollisionDetection();

	//-----------------------------------------------------------------------
	//Prevent the spaceShip from leaving the level
	//-----------------------------------------------------------------------
	if(m_Position.y>m_HitLevelPtr->GetBounds().bottom-m_BmpMoonlanderPtr->GetHeight())
	{
		m_Position.y=m_HitLevelPtr->GetBounds().bottom-m_BmpMoonlanderPtr->GetHeight();
		m_Velocity.y=0;
	}
	if(m_Position.y+m_BmpMoonlanderPtr->GetHeight()<0) 
	{
		m_Angle=M_PI;
		if(m_Position.y<-m_BmpMoonlanderPtr->GetHeight()) m_Position.y=-m_BmpMoonlanderPtr->GetHeight()+1;
	}
	if(m_Position.x+m_BmpMoonlanderPtr->GetWidth()<0) 
	{
		m_Angle=M_PI_2;
		if(m_Position.x<-m_BmpMoonlanderPtr->GetWidth()) m_Position.x=-m_BmpMoonlanderPtr->GetWidth()+1;
	}
	if(m_Position.x>m_HitLevelPtr->GetBounds().right+m_BmpMoonlanderPtr->GetWidth())
	{
		m_Angle=M_PI+M_PI_2;
		m_Position.x=m_HitLevelPtr->GetBounds().right;
	}
	m_Position += m_Velocity*deltaTime;

}
void Moonlander::CollisionDetection()
{
	//--------------------------------------------------------------------------
	//RayCast
	//--------------------------------------------------------------------------
	DOUBLE2 direction = DOUBLE2((m_Radius3)*cos(m_Angle+M_PI_2),(m_Radius3)*sin(m_Angle+M_PI_2)); 

	//Bottom and Top (two rays Left and Right)
	m_StartRay = DOUBLE2(m_Position.x,m_Position.y);

	/*MATRIX3X2 matRotateRay;
	matRotateRay.SetAsRotate(m_Angle);*/
	//m_RayVector = matRotateRay.TransformVector(m_startRayLeft);
	m_RayVector = DOUBLE2(direction.x*0.85,direction.y*0.85);
	HIT hitArr[1];

	int numberOfHits = m_HitLevelPtr->Raycast(m_StartRay,m_RayVector,hitArr,1,0);

	if(numberOfHits>0 )
	{
		if(m_Velocity.Length()>10 ) m_IsLevelHit=true;
		else
		{
			if(hitArr[0].lambda>0.5)
			{
				DOUBLE2 d = (1-hitArr[0].lambda)*m_RayVector;
				m_Position-=d;
				m_Velocity= DOUBLE2(0,0);		
			}
			if(hitArr[0].lambda<=0.5)
			{
				DOUBLE2 d = (hitArr[0].lambda)*m_RayVector;
				m_Position+=d;
				m_Velocity.y=0;
			}
		}

	}
	//--------------------------------------------------------------------------
	//Reflection
	//--------------------------------------------------------------------------
	// reflectie implementeren
	HIT hitArrReflected[1];
	if( m_HitLevelPtr->Raycast(m_Position, m_Velocity, hitArrReflected, 1, 0) > 0)
	{
		m_ProjectedRay =  hitArrReflected[0].normal.DotProduct(m_Velocity) * hitArrReflected[0].normal;
		m_ReflectedRay = (m_Velocity - 2 * m_ProjectedRay).Normalized();
		m_ReflectedRay = m_ReflectedRay * ((1-hitArrReflected[0].lambda)* m_Velocity.Length());	
		if(m_IsLevelHit == true)
		{
			m_Velocity = (m_ReflectedRay*0.75);
		}

	}		
	else
	{
		m_IsLevelHit = false;
	}

	//--------------------------------------------------------------------------
	//Fuelbases
	//--------------------------------------------------------------------------

	numberOfHits = m_HitFuelbasesPtr->Raycast(m_StartRay,m_RayVector,hitArr,1,0);

	if(numberOfHits > 0 )
	{

		if(hitArr[0].lambda > 0.5)
		{
			DOUBLE2 d = (1-hitArr[0].lambda)*m_RayVector;
			m_Position-=d;
			if(m_Velocity.Norm()>10) m_Velocity= DOUBLE2(0,0);	
			if(m_Angle> M_PI + M_PI_2 || m_Angle <M_PI_2) m_Angle=0;
		}
		if(hitArr[0].lambda<=0.5)
		{
			DOUBLE2 d = (hitArr[0].lambda)*m_RayVector;
			m_Position+=d;
			if(m_Velocity.Norm()>10) m_Velocity.y=0;
		}
	}

}
DOUBLE2 Moonlander::GetPos()
{
	return m_Position;
}
RECT2 Moonlander::GetRect()
{
	return m_RectMoonlander;
}
double Moonlander::GetFuel()
{
	return m_Fuel;
}
void Moonlander::SetFuel(int fuel)
{
	m_Fuel = fuel;
}
void Moonlander::Decreasehealth()
{
	if(m_StateOfInfo!=STATE_SHOW_DEBUG)
	{
		if(m_Health>0) m_Health-=50;
		else m_Health=0;
	}
}
bool Moonlander::IsMoonlanderDead()
{
	return m_BlMoonlanderDead;
}
RECT2 Moonlander::IsRussianBaseHit()
{
	return m_BulletListPtr->IsRussianBaseHit();
}



