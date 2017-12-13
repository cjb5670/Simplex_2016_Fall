#include "Octree.h"
using namespace Simplex;


Octree::Octree()
{
}


Octree::~Octree()
{
	for (int i = 0; i < allLeaves.size; i++)
	{
		delete &allLeaves[i];
	}
}

void Simplex::Octree::GenTree(uint levels)
{
	levelsCount = 0;
	for (int i = 0; i < levels - 1; i++)
	{
		if (i == 0)
		{
			Ocleaf root = Ocleaf();
			allLeaves.push_back(root);
			root.ID = 1;
			root.level = levelsCount;
			bool hasChildren = false;

		}
		else
		{
			for (int j = 0; j < allLeaves.size(); j++)
			{
				if (!allLeaves[j].hasChildren)
				{
					allLeaves[j].hasChildren = true;
					SubDivide(allLeaves[j]);
				}
			}
		}
	}
}

/// Subdivides a single leaf
void Simplex::Octree::SubDivide(Ocleaf parentLeaf)
{
	// Incrementation logic.
	bool bottomLevel = true;
	for (int i = 0; i < parentLeaf.Parent->leaves.size; i++)
	{
		if (parentLeaf.Parent->leaves[i]->hasChildren)
		{
			bottomLevel = false;
		}
	}
	if (bottomLevel)
	{
		levelsCount++;
	}
	parentLeaf.hasChildren = true;
	for (int i = 1; i < 8; i++)
	{
		Ocleaf* newLeaf = new Ocleaf();
		parentLeaf.leaves.push_back(newLeaf);
		newLeaf->Parent = &parentLeaf;
		newLeaf->ID = allLeaves.size;
		newLeaf->level = levelsCount;
		newLeaf->hasChildren = false;
	}
}

/// Removes all children of a specific leaf
void Simplex::Octree::DeleteLevel(Ocleaf parentLeaf)
{
	// incrementation logic
	bool bottomLevel = true;
	for (int i = 0; i < parentLeaf.Parent->leaves.size; i++)
	{
		if (parentLeaf.leaves[i]->hasChildren)
		{
			bottomLevel = false;
		}
	}
	if (bottomLevel)
	{
		levelsCount--;
	}
	
	// deleting
	int size = parentLeaf.leaves.size;
	for (int i = size; i > 0; i--)
	{
		Ocleaf toDelete = *parentLeaf.leaves[i];
		parentLeaf.leaves.pop_back();
		delete &toDelete;
	}

}

std::vector<Ocleaf> Simplex::Octree::leavesInLevel(int _level)
{
	std::vector<Ocleaf> leafList = std::vector<Ocleaf>();
	for (int i = 0; i < allLeaves.size; i++)
	{
		if (allLeaves[i].level = _level)
		{
			leafList.push_back(allLeaves[i]);  
		}
	}
	return leafList;
}
