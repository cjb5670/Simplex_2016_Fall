#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	// make sure list is empty and count is 0
	m_entityList.clear();
	m_uEntityCount = 0;
}
void MyEntityManager::Release(void)
{
	// iterate and delete references
	for (int i = 0; i < m_uEntityCount; i++)
	{
		MyEntity* pEntity = m_entityList[i];
		SafeDelete(pEntity);
	}
	// make sure list is empty and count is 0
	m_entityList.clear();
	m_uEntityCount = 0;
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	// if populated, delete and dereference
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	// iterate for ID
	for (int i = 0; i < m_uEntityCount; i++)
	{
		if (a_sUniqueID == m_entityList[i]->GetUniqueID())
		{
			return i;
		}
	}
	// else return invalid
	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	// if nothing saved in list, return nothing
	if (m_entityList.size() == 0)
	{
		return nullptr;
	}
	// if out of bounds, go to last
	if (a_uIndex >= m_uEntityCount)
	{
		a_uIndex = m_uEntityCount - 1;
	}
	return m_entityList[a_uIndex]->GetModel();
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{

	MyEntity* temp = MyEntity::GetEntity(a_sUniqueID);
	// if entity exists
	if (temp)
	{
		return temp->GetModel();
	}
	return nullptr;
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	if (m_entityList.size() == 0)
	{
		return nullptr;
	}
	if (a_uIndex >= m_uEntityCount)
	{
		a_uIndex = m_uEntityCount - 1;
	}
	return m_entityList[a_uIndex]->GetRigidBody();
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	MyEntity* temp = MyEntity::GetEntity(a_sUniqueID);
	// if entity exists
	if (temp)
	{
		return temp->GetRigidBody();
	}
	return nullptr;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	if (m_entityList.size() == 0)
	{
		return IDENTITY_M4;
	}
	if (a_uIndex >= m_uEntityCount)
	{
		a_uIndex = m_uEntityCount - 1;
	}

	return IDENTITY_M4;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	MyEntity* temp = MyEntity::GetEntity(a_sUniqueID);
	// if entity exists
	if (temp)
	{
		return temp->GetModelMatrix();
	}
	return IDENTITY_M4;
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	MyEntity* temp = MyEntity::GetEntity(a_sUniqueID);
	// if entity exists
	if (temp)
	{
		return temp->SetModelMatrix(a_m4ToWorld);
	}
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	if (m_entityList.size() == 0)
	{
		return;
	}
	if (a_uIndex >= m_uEntityCount)
	{
		a_uIndex = m_uEntityCount - 1;
	}
	m_entityList[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{
	// Collisions
	for (int i = 0; i < m_uEntityCount - 1; i++)
	{
		for (int j = i + 1; j < m_uEntityCount; j++)
		{
			m_entityList[i]->IsColliding(m_entityList[j]);
		}
	}
}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	
	MyEntity* temp = new MyEntity(a_sFileName, a_sUniqueID);
	// if exists add
	if (temp->IsInitialized())
	{
		m_entityList.push_back(temp);
		m_uEntityCount = m_entityList.size();
	}
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	// do nothing if empty
	if (m_entityList.size() == 0)
	{
		return;
	}

	// move to end if over
	if (a_uIndex >= m_uEntityCount)
	{
		a_uIndex = m_uEntityCount - 1;
	}

	// set entity to end if not already
	if (a_uIndex != m_uEntityCount - 1)
	{
		std::swap(m_entityList[a_uIndex], m_entityList[m_uEntityCount - 1]);
	}

	// remove last
	MyEntity* temp = m_entityList[m_uEntityCount - 1];
	SafeDelete(temp);
	m_entityList.pop_back();
	m_uEntityCount--;
	return;
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	int nIndex = GetEntityIndex(a_sUniqueID);
	RemoveEntity(nIndex);
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	// if empty, return
	if (m_entityList.size() == 0)
	{
		return "";
	}
	// if out of bounds, set to last
	if (a_uIndex >= m_entityList.size())
	{
		a_uIndex = m_entityList.size() - 1;
	}
	return m_entityList[a_uIndex]->GetUniqueID();
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	// if empty return
	if (m_entityList.size() == 0)
	{
		return nullptr;
	}

	// if out of bounds, set last
	if (a_uIndex >= m_entityList.size())
	{
		a_uIndex = m_entityList.size() - 1;
	}

	return m_entityList[a_uIndex];
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	// if out of bounds, build list
	if (a_uIndex >= m_uEntityCount)
	{
		for (a_uIndex = 0; a_uIndex < m_uEntityCount; ++a_uIndex)
		{
			m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
		}
	}
	// if in bounds, set specified
	else 
	{
		m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
	}
}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	MyEntity* temp = MyEntity::GetEntity(a_sUniqueID);

	if (temp)
	{
		temp->AddToRenderList(a_bRigidBody);
	}
}