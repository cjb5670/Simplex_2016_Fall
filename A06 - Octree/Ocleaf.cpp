#include "Ocleaf.h"
using namespace Simplex;


Ocleaf::Ocleaf()
{
	meshManager = meshManager->GetInstance();
}


Ocleaf::~Ocleaf()
{
}

bool Simplex::Ocleaf::Contains(MyEntity* object)
{
	//check if spheres are colliding
	bool bColliding = true;
	//bColliding = (glm::distance(GetCenterGlobal(), other->GetCenterGlobal()) < m_fRadius + other->m_fRadius);
	//if they are check the Axis Aligned Bounding Box
	if (bColliding) //they are colliding with bounding sphere
	{
		if (max.x < object->GetRigidBody()->m_v3MinG.x) //this to the right of other
			bColliding = false;
		if (min.x > object->GetRigidBody()->m_v3MaxG.x) //this to the left of other
			bColliding = false;

		if (max.y < object->GetRigidBody()->m_v3MinG.y) //this below of other
			bColliding = false;
		if (min.y > object->GetRigidBody()->m_v3MaxG.y) //this above of other
			bColliding = false;

		if (max.z < object->GetRigidBody()->m_v3MinG.z) //this behind of other
			bColliding = false;
		if (min.z > object->GetRigidBody()->m_v3MaxG.z) //this in front of other
			bColliding = false;
	}
	return bColliding;
}

void Simplex::Ocleaf::Draw()
{
	vector3 yellow = vector3(1, 1, 0);

	meshManager->AddCubeToRenderList(
		glm::translate(IDENTITY_M4, center) * glm::scale(IDENTITY_M4, vector3(size, size, size)), 
		yellow,
		RENDER_WIRE);
	if (hasChildren)
	{
		for (int i = 0; i < 8; i++)
		{
			leaves[i]->Draw();
		}
	}
}
