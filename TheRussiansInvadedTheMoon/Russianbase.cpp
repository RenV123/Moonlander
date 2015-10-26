//---------------------------
// Includes
//---------------------------
#include "RussianBase.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
RussianBase::RussianBase():
		m_Position(0,0),
		m_AnimatedAngle(0),
		m_BmpRussianBasePtr(nullptr),
		m_BmpRussianBaseGunPtr(nullptr),
		m_BulletListPtr(nullptr),
		m_BmpExplosionPtr(nullptr),
		m_BlRotateLeft(false),
		m_Tickcounter(0),
		m_TicksTillNextFire(30),
		m_RussianBaseRect(),
		m_StateOfInfo(0),
		m_Health(200),
		m_TickCounter(0),
		m_AnimatedIndex(0),
		m_BlExplodeRussianBase(false),
		m_BlRussianBaseDead(false)
{
}

RussianBase::~RussianBase()
{
	delete m_BmpRussianBaseGunPtr;
	m_BmpRussianBaseGunPtr = nullptr;

	delete m_BmpRussianBasePtr;
	m_BmpRussianBasePtr = nullptr;

	//m_BulletListPtr->RemoveAll();
	delete m_BulletListPtr;
	m_BulletListPtr = nullptr;

	delete m_BmpExplosionPtr;
	m_BmpExplosionPtr= nullptr;
}
bool RussianBase::Create(int x, int y)
{
	m_Position= DOUBLE2(x,y);
	m_BmpRussianBasePtr = new Bitmap(IDB_RUSSIANBASE);
	m_BmpRussianBasePtr->SetTransparencyColor(255,0,255);
	m_BmpRussianBaseGunPtr = new Bitmap(IDB_RUSSIANBASEGUN);
	m_BmpRussianBaseGunPtr->SetTransparencyColor(255,0,255);
	m_BmpExplosionPtr = new Bitmap(IDB_EXPLOSION);
	m_BmpExplosionPtr->SetTransparencyColor(255,0,255);

	m_RussianBaseRect = RECT2(m_Position.x, m_Position.y,m_Position.x +m_BmpRussianBasePtr->GetWidth(), m_Position.y +m_BmpRussianBasePtr->GetHeight()  );

	m_BulletListPtr = new BulletList();

	if(m_BmpRussianBaseGunPtr->Exists() && m_BmpRussianBasePtr->Exists()) return true;
	else return false;

}
void RussianBase::Tick(DOUBLE2 posCamera,double deltaTime , RECT2 moonlanderRect,int stateOfInfo)
{
	if(m_BlRotateLeft == false)m_AnimatedAngle+=0.01;
	else m_AnimatedAngle-=0.01;
	if(m_AnimatedAngle>M_PI_2-0.35) m_BlRotateLeft=true;
	if(m_AnimatedAngle<-M_PI_2+0.35) m_BlRotateLeft=false;

	m_StateOfInfo = stateOfInfo;
	//Create bullets
	if( m_Tickcounter==m_TicksTillNextFire)
	{
		m_Tickcounter=0;
		//The bullet use Cartesian Coordinates we have polar coordinates 
		//double radius=sqrt(m_Position.x*m_Position.x + m_Position.y*m_Position.y); //Pythagoras
		double radius=sqrt(m_BmpRussianBasePtr->GetWidth()/2*m_BmpRussianBasePtr->GetWidth()/2 +m_BmpRussianBasePtr->GetHeight()/2*m_BmpRussianBasePtr->GetHeight()/2);
		DOUBLE2 direction = DOUBLE2(radius*cos(m_AnimatedAngle-M_PI_2),radius*sin(m_AnimatedAngle-M_PI_2)); //converting from pl cc
		RussianBaseBullet * bulletPtr;
		DOUBLE2 FirePosition = DOUBLE2(m_Position.x+m_BmpRussianBasePtr->GetWidth()/2,m_Position.y+m_BmpRussianBasePtr->GetHeight()/2) +(direction);
		bulletPtr=new RussianBaseBullet(FirePosition.x,FirePosition.y ,direction.x,direction.y);
		m_BulletListPtr->AddRussianBaseBullet(bulletPtr);
	}
	else if(m_Tickcounter<m_TicksTillNextFire)
	{
		m_Tickcounter++;
	}
	
	m_BulletListPtr->Tick(posCamera,deltaTime,moonlanderRect);

	//Check Health state and explode if necessary 
	if(m_Health==0) m_BlExplodeRussianBase =true;
	if(m_BlExplodeRussianBase == true)
	{
		m_TickCounter++;
		if(m_TickCounter%5 ==0)
		{
			m_AnimatedIndex++;
		}
		if(m_AnimatedIndex>4)
		{
			m_BlRussianBaseDead=true;
			m_AnimatedIndex=0;
		}
	}
	

	
}
void RussianBase::Paint(MATRIX3X2 matView)
{
	//Draw the base
	MATRIX3X2 matCenter,matRotate,matTranslate,matRadius,matTransform,matScale;
	matTranslate.SetAsTranslate(m_Position);
	GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
	GAME_ENGINE->DrawBitmap(m_BmpRussianBasePtr,0,0);

	//Draw The Gun
	GAME_ENGINE->SetTransformMatrix(MATRIX3X2::CreateIdentityMatrix());
	matCenter.SetAsTranslate(-m_BmpRussianBaseGunPtr->GetWidth()/2,-m_BmpRussianBaseGunPtr->GetHeight()/2);
	matRadius.SetAsTranslate(0,-m_BmpRussianBasePtr->GetHeight()-m_BmpRussianBaseGunPtr->GetHeight()/2+3); //3to overlap bitmaps a bit
	matRotate.SetAsRotate(m_AnimatedAngle);
	matTranslate.SetAsTranslate(m_Position.x+m_BmpRussianBasePtr->GetWidth()/2,m_Position.y+m_BmpRussianBasePtr->GetHeight());
	matTransform = matCenter*matRadius*matRotate*matTranslate*matView;
	GAME_ENGINE->SetTransformMatrix(matTransform);
	GAME_ENGINE->DrawBitmap(m_BmpRussianBaseGunPtr,0,0);

	//Draw The Bullets
	m_BulletListPtr->Paint(matView,matRotate);

	//Draw Explosion
	if(m_BlExplodeRussianBase == true)
	{
		RECT clip;
		clip.left =  (m_BmpExplosionPtr->GetWidth()/5)* m_AnimatedIndex;
		clip.right = clip.left  + m_BmpExplosionPtr->GetWidth()/5;
		clip.top = 0;
		clip.bottom = clip.top + m_BmpExplosionPtr->GetHeight();

		matCenter.SetAsTranslate(-m_BmpExplosionPtr->GetWidth()/10,-m_BmpExplosionPtr->GetHeight()/2);
		matTranslate.SetAsTranslate(m_Position.x+m_BmpRussianBasePtr->GetWidth()/2,m_Position.y+m_BmpRussianBasePtr->GetHeight()/2);
		matScale.SetAsScale(2);
		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpExplosionPtr,0,0,clip);
	}

	//Draw Rect
	if(m_StateOfInfo==STATE_SHOW_DEBUG)
	{
		GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(COLOR(255,255,0));
		GAME_ENGINE->DrawRect(m_RussianBaseRect,1.0);
		GAME_ENGINE->SetTransformMatrix(MATRIX3X2::CreateIdentityMatrix());
	}

}
DOUBLE2 RussianBase::GetPos()
{
	return m_Position;
}
RECT2 RussianBase::GetRect()
{
	return m_RussianBaseRect;
}
bool RussianBase::IsMoonlanderHit()
{
	return m_BulletListPtr->IsTargetHit();
	
}
void RussianBase::SetMoonlanderHit(bool hit)
{
	m_BulletListPtr->setTargetHit(hit);

}
void RussianBase::Decreasehealth()
{
	m_Health-=50;
}
bool RussianBase::IsRussianBaseReadytoDestroy()
{
	return m_BlRussianBaseDead;
}
