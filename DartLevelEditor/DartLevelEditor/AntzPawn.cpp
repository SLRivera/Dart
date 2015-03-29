#include "AntzPawn.h"


AntzPawn::AntzPawn()
{
	m_ePawnType = PawnType::PT_EnemyType1SpawnLocale;
	m_vDiffuseColor = D3DXVECTOR4(0.8f, 0.0f, 0.2f, 1.0f);
	m_vScale = D3DXVECTOR3(10.f, 10.f, 10.0f);
}


AntzPawn::~AntzPawn()
{
}
