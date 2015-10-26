//---------------------------
// Includes
//---------------------------
#include "BulletList.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
BulletList::BulletList(): m_BulletIsHit(false),m_TargetRect()
{
	for( int i=0 ; i < MAX_NR_OF_BULLETS ; ++i )
	{
		m_BulletPtrArr[i]=nullptr;
	}

	for( int i=0 ; i < MAX_NR_OF_BULLETS ; ++i )
	{
		m_RussianBaseBulletPtrArr[i]=nullptr;
	}
	for( int i=0 ; i < NUMBER_OF_RUSSIANBASE ; ++i )
	{
		m_RussianBaseBulletPtrArr[i]=nullptr;
	}

}

BulletList::~BulletList()
{
	// nothing to destroy
}

bool BulletList::AddBullet(Bullet* BulletPtr)
{
	for(int i=0;i<MAX_NR_OF_BULLETS;++i)
	{
		if(m_BulletPtrArr[i]==nullptr)
		{
			m_BulletPtrArr[i]=BulletPtr;
			return true;
		}
	}

	return false;
}
bool BulletList::AddRussianBaseBullet(RussianBaseBullet* BulletPtr)
{
	for(int i=0;i<MAX_NR_OF_BULLETS;++i)
	{
		if(m_BulletPtrArr[i]==nullptr)
		{
			m_RussianBaseBulletPtrArr[i]=BulletPtr;
			return true;
		}
	}

	return false;
}
bool BulletList::RemoveBullet(Bullet* BulletPtr)
 {
	for(int i=0; i<MAX_NR_OF_BULLETS;++i)
	{
 		if(m_BulletPtrArr[i]==BulletPtr)
		{
			delete m_BulletPtrArr[i];
			m_BulletPtrArr[i]=nullptr;
			return true;
		}
	}
	return false;

}
bool BulletList::RemoveRussianBaseBullet(RussianBaseBullet* BulletPtr)
{
	for(int i=0; i<MAX_NR_OF_BULLETS;++i)
	{
		if(m_RussianBaseBulletPtrArr[i]==BulletPtr)
		{
			delete m_RussianBaseBulletPtrArr[i];
			m_RussianBaseBulletPtrArr[i]=nullptr;
			return true;
		}
	}
	return false;

}

void BulletList::RemoveAll()
{
	for(int i=0; i<MAX_NR_OF_BULLETS;++i)
	{
		delete m_BulletPtrArr[i];
		m_BulletPtrArr[i]=nullptr;
	}

	for(int i=0; i<MAX_NR_OF_BULLETS;++i)
	{
		delete m_RussianBaseBulletPtrArr[i];
		m_RussianBaseBulletPtrArr[i]=nullptr;
	}

}

int BulletList::GetSizeOfBullets()
{
	int numberOfElementes=0;
	for(int i=0;i<MAX_NR_OF_BULLETS;++i)
		if(m_BulletPtrArr[i]!=nullptr)
			++numberOfElementes;
	// Counts the number of Fuels in the array and returns this number
	return numberOfElementes;
}

int BulletList::GetSizeOfRussianBaseBullet()
{
	int numberOfElementes=0;
	for(int i=0;i<MAX_NR_OF_BULLETS;++i)
		if(m_RussianBaseBulletPtrArr[i]!=nullptr)
			++numberOfElementes;
	// Counts the number of Fuels in the array and returns this number
	return numberOfElementes;
}

void BulletList::Tick(DOUBLE2 PosCamera, double deltaTime, RECT2 targetRect)   
{
	m_TargetRect = targetRect;
	//Calls the Tick method on each Bullet in the list
	for(int i=0;i<MAX_NR_OF_BULLETS;++i)
		if(m_BulletPtrArr[i]!=nullptr)
		{
			m_BulletPtrArr[i]->Tick(deltaTime);
		}

		//Calls the Tick method on each RussianBullet in the list
		for(int i=0;i<MAX_NR_OF_BULLETS;++i)
			if(m_RussianBaseBulletPtrArr[i]!=nullptr)
			{
				m_RussianBaseBulletPtrArr[i]->Tick(deltaTime);
			}

			//delete every bullet who leaves the camera's view
			for(int i=0;i<MAX_NR_OF_BULLETS;++i)
				if(m_BulletPtrArr[i]!=nullptr)
				{
					if(m_BulletPtrArr[i]->GetPos().x>PosCamera.x+GAME_ENGINE->GetWidth()) RemoveBullet(m_BulletPtrArr[i]);
					else if(m_BulletPtrArr[i]->GetPos().x<0) RemoveBullet(m_BulletPtrArr[i]);
					else if(m_BulletPtrArr[i]->GetPos().y<0) RemoveBullet(m_BulletPtrArr[i]);
					else if(m_BulletPtrArr[i]->GetPos().y>PosCamera.y+GAME_ENGINE->GetHeight()) RemoveBullet(m_BulletPtrArr[i]);
				}

				for(int i=0;i<MAX_NR_OF_BULLETS;++i)
					if(m_RussianBaseBulletPtrArr[i]!=nullptr)
					{
						if(m_RussianBaseBulletPtrArr[i]->GetPos().x>PosCamera.x+GAME_ENGINE->GetWidth()) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
						else if(m_RussianBaseBulletPtrArr[i]->GetPos().x<0) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
						else if(m_RussianBaseBulletPtrArr[i]->GetPos().y<0) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
						else if(m_RussianBaseBulletPtrArr[i]->GetPos().y>PosCamera.y+GAME_ENGINE->GetHeight()) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
					}
}
void BulletList::Tick(DOUBLE2 PosCamera, double deltaTime, RECT2ARRAYSTRUCT targetRectStruct)   
{
	m_RussianBaseRectArr[0] = targetRectStruct.rect2struct1;
	m_RussianBaseRectArr[1] = targetRectStruct.rect2struct2;
	m_RussianBaseRectArr[2] = targetRectStruct.rect2struct3;
	m_RussianBaseRectArr[3] = targetRectStruct.rect2struct4;
	m_RussianBaseRectArr[4] = targetRectStruct.rect2struct5;

	//Calls the Tick method on each Bullet in the list
	for(int i=0;i<MAX_NR_OF_BULLETS;++i)
		if(m_BulletPtrArr[i]!=nullptr)
		{
			m_BulletPtrArr[i]->Tick(deltaTime);
		}

		//Calls the Tick method on each RussianBullet in the list
		for(int i=0;i<MAX_NR_OF_BULLETS;++i)
			if(m_RussianBaseBulletPtrArr[i]!=nullptr)
			{
				m_RussianBaseBulletPtrArr[i]->Tick(deltaTime);
			}

			//delete every bullet who leaves the camera's view
			for(int i=0;i<MAX_NR_OF_BULLETS;++i)
				if(m_BulletPtrArr[i]!=nullptr)
				{
					if(m_BulletPtrArr[i]->GetPos().x>PosCamera.x+GAME_ENGINE->GetWidth()) RemoveBullet(m_BulletPtrArr[i]);
					else if(m_BulletPtrArr[i]->GetPos().x<0) RemoveBullet(m_BulletPtrArr[i]);
					else if(m_BulletPtrArr[i]->GetPos().y<0) RemoveBullet(m_BulletPtrArr[i]);
					else if(m_BulletPtrArr[i]->GetPos().y>PosCamera.y+GAME_ENGINE->GetHeight()) RemoveBullet(m_BulletPtrArr[i]);
				}

				for(int i=0;i<MAX_NR_OF_BULLETS;++i)
					if(m_RussianBaseBulletPtrArr[i]!=nullptr)
					{
						if(m_RussianBaseBulletPtrArr[i]->GetPos().x>PosCamera.x+GAME_ENGINE->GetWidth()) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
						else if(m_RussianBaseBulletPtrArr[i]->GetPos().x<0) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
						else if(m_RussianBaseBulletPtrArr[i]->GetPos().y<0) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
						else if(m_RussianBaseBulletPtrArr[i]->GetPos().y>PosCamera.y+GAME_ENGINE->GetHeight()) RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
					}
}

void BulletList::Paint(MATRIX3X2 matView,MATRIX3X2 matRotate)
{
	for (int i = 0; i < MAX_NR_OF_BULLETS; ++i)
	{
		if (m_BulletPtrArr[i] != nullptr)
		{
			m_BulletPtrArr[i]->Paint(matView, matRotate);

		}
	}
	for (int i = 0; i < MAX_NR_OF_BULLETS; ++i)
	{
		if (m_RussianBaseBulletPtrArr[i] != nullptr)
		{
			m_RussianBaseBulletPtrArr[i]->Paint(matView, matRotate);
		}
	}
			
}

bool BulletList::IsTargetHit()
{
	for (int i = 0; i < MAX_NR_OF_BULLETS ; i++)
	{
		if(m_RussianBaseBulletPtrArr[i]!=nullptr)
		{
			RECT2 bulletRect = m_RussianBaseBulletPtrArr[i]->GetRect();
			if( RectIntersectTest(m_TargetRect , bulletRect) == true)
			{
				m_BulletIsHit=true;
				RemoveRussianBaseBullet(m_RussianBaseBulletPtrArr[i]);
			}
		}
	}
	return m_BulletIsHit;
}
RECT2 BulletList::IsRussianBaseHit()
{
	RECT2 russianbaserect(0,0,0,0);
	for (int i = 0; i < MAX_NR_OF_BULLETS ; i++)
	{
		if(m_BulletPtrArr[i]!=nullptr)
		{
   			RECT2 bulletRect = m_BulletPtrArr[i]->GetRect();
			for (int i = 0; i < NUMBER_OF_RUSSIANBASE ; i++)
			{
				if( RectIntersectTest(m_RussianBaseRectArr[i] , bulletRect) == true)
				{
 					RemoveBullet(m_BulletPtrArr[i]);
					russianbaserect = m_RussianBaseRectArr[i];
				}
			}
		}
	}
	return russianbaserect;
}
void BulletList::setTargetHit(bool targetHit)
{
	m_BulletIsHit = targetHit;
}
Bullet * BulletList::GetBulletPtrArr()
{
	return m_BulletPtrArr[0];
}
bool BulletList::RectIntersectTest(RECT2 r1, RECT2 r2)
{
	bool noIntersect=
		r1.right < r2.left || r1.left> r2.right ||
		r1.top> r2.bottom || r1.bottom < r2.top;
	return !noIntersect;
}



