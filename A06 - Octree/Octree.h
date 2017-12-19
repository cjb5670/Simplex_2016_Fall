#pragma once
#include "Ocleaf.h"
#include <vector>

namespace Simplex
{
	class Octree
	{
	public:
		// Members
		Ocleaf* root;
		int levelsCount;
		MeshManager* meshManager;
		MyEntityManager* entityManager;
		
		//std::vector<Ocleaf*> allLeaves;


		// Methods
		Octree();
		~Octree();
		void GenRoot();
		void SubDivide(Ocleaf* leaf, uint level);
		void DeleteLevel(Ocleaf* leaf);
		void Update(Ocleaf* parent);
		//std::vector<Ocleaf*> leavesInLevel(int _level);
		
	};
}




