#include "Octree.h"
using namespace Simplex;


Octree::Octree()
{
	entityManager = entityManager->GetInstance();
	//meshManager = meshManager->GetInstance();
}


Octree::~Octree()
{
	/*for (int i = 0; i < allLeaves.size() ; i++)
	{
		delete &allLeaves[i];
	}*/
}

void Simplex::Octree::GenRoot()
{
	meshManager = meshManager->GetInstance();
	levelsCount = 1;
	root = new Ocleaf();
	//allLeaves.push_back(root);
	root->ID = 1;
	root->level = levelsCount;
	bool hasChildren = false;
	
	float grandMinx = FLT_MAX;
	float grandMaxx = FLT_MIN;
	float grandMiny = FLT_MAX;
	float grandMaxy = FLT_MIN;
	float grandMinz = FLT_MAX;
	float grandMaxz = FLT_MIN;

	int entityNum = entityManager->GetEntityCount();
	matrix4 mat;
	// set size
	for (int i = 0; i < entityNum; i++)
	{
		MyEntity* cur = entityManager->GetEntity(i);
		mat = cur->GetModelMatrix();
		if (grandMinx > mat[3].x)
		{
			grandMinx = mat[3].x;
		}
		else if (grandMaxx < mat[3].x)
		{
			grandMaxx = mat[3].x;
		}
		if (grandMiny > mat[3].y)
		{
			grandMiny = mat[3].y;
		}
		else if (grandMaxy < mat[3].y)
		{
			grandMaxy = mat[3].y;
		}
		if (grandMinz > mat[3].z)
		{
			grandMinz = mat[3].z;
		}
		else if (grandMaxz < mat[3].z)
		{
			grandMaxz = mat[3].z;
		}

		root->size = glm::max(grandMaxx - grandMinx, grandMaxy - grandMiny, grandMinz - grandMinz);
		root->min = vector3(-root->size - grandMinx, -root->size - grandMiny, -root->size - grandMinz);
		root->max = vector3(root->size + grandMinx, root->size + grandMiny, root->size + grandMinz);
		root->center = vector3((root->size / 2), root->size / 2, root->size / 2) + root->min;
	}
}

/// Subdivides a single leaf
void Simplex::Octree::SubDivide(Ocleaf *parentLeaf, uint curLevel)
{
	//// Incrementation logic.
	//bool bottomLevel = true;
	//if (parentLeaf != root)
	//{
	//	for (int i = 0; i < parentLeaf->Parent->leaves.size(); i++)
	//	{
	//		if (parentLeaf->Parent->leaves[i]->hasChildren)
	//		{
	//			bottomLevel = false;
	//		}
	//	}
	//}
	//
	//if (bottomLevel)
	//{
	//	levelsCount++;
	//}
	// Creating children
	if (parentLeaf->hasChildren)
	{
		for (int i = 0; i < 8; i++)
		{
			SubDivide(parentLeaf->leaves[i], curLevel);
		}
	}

	parentLeaf->hasChildren = true;
	levelsCount = curLevel;

	for (int x = -1; x <= 1; x += 2)
	{
		for (int y = -1; y <= 1; y += 2)
		{
			for (int z = -1; z <= 1; z += 2)
			{
				Ocleaf* newLeaf = new Ocleaf();
				parentLeaf->leaves.push_back(newLeaf);
				//allLeaves.push_back(newLeaf);
				newLeaf->Parent = parentLeaf;
				//newLeaf->ID = allLeaves.size();
				newLeaf->level = curLevel;
				newLeaf->hasChildren = false;
				newLeaf->size = parentLeaf->size / 2;

				float halfsize = parentLeaf->size / 2;
				float quartsize = halfsize / 2;

				newLeaf->center = vector3(parentLeaf->center.x + (x * quartsize), parentLeaf->center.y + (y * quartsize), parentLeaf->center.z + (z * quartsize));
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		Ocleaf* newLeaf = new Ocleaf();
		parentLeaf->leaves.push_back(newLeaf);
		//allLeaves.push_back(newLeaf);
		newLeaf->Parent = parentLeaf;
		//newLeaf->ID = allLeaves.size();
		newLeaf->level = curLevel;
		newLeaf->hasChildren = false;
		newLeaf->size = parentLeaf->size / 2;
	}
}

/// Removes all children of a specific leaf
void Simplex::Octree::DeleteLevel(Ocleaf *parentLeaf)
{
	// incrementation logic
	/*bool bottomLevel = true;
	for (int i = 0; i < parentLeaf->Parent->leaves.size(); i++)
	{
		if (parentLeaf->leaves[i]->hasChildren)
		{
			bottomLevel = false;
		}
	}
	if (bottomLevel)
	{
		levelsCount--;
	}*/
	if (parentLeaf->leaves[0]->hasChildren)
	{
		for (int i = 0; i < 8; i++)
		{
			DeleteLevel(parentLeaf->leaves[i]);
		}
	}
	else 
	{
		// deleting
		int size = parentLeaf->leaves.size();
		for (int i = size; i > 0; i--)
		{
			delete parentLeaf->leaves[i - 1];
			parentLeaf->leaves.pop_back();
		}
		parentLeaf->hasChildren = false;
	}
	

}

void Simplex::Octree::Update(Ocleaf* _parent)
{
	if (_parent->hasChildren )
	{
		for (int i = 0; i < 8; i++)
		{
			Update(_parent->leaves[i]);
		}
	}
	else
	{
		
		for (uint i = 0; i < entityManager->GetEntityCount() - 1; i++)
		{
			// Make vector of entities in this octant
			if (_parent->Contains(entityManager->GetEntity(i)))
			{
				_parent->fullyContained.push_back(*entityManager->GetEntity(i));
			}
		}
		// Check each entity against each other entity in octant.
		//for (uint i = 0; i < _parent->fullyContained.size() - 1; i++)
		{
		//	for (uint j = i + 1; j < _parent->fullyContained.size(); j++)
			{
		//		_parent->fullyContained[i].IsColliding(&_parent->fullyContained[j]);
			}
		}
		
	}
}

//std::vector<Ocleaf*> Simplex::Octree::leavesInLevel(int _level)
//{
	/*std::vector<Ocleaf*> leafList = std::vector<Ocleaf*>();
	for (int i = 0; i < allLeaves.size(); i++)
	{
		if (allLeaves[i]->level = _level)
		{
			leafList.push_back(allLeaves[i]);  
		}
	}
	return leafList;*/
//}
