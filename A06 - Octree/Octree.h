#pragma once
#include "Ocleaf.h"
#include <vector>

namespace Simplex
{
	class Octree
	{
	public:
		// Members
		Ocleaf Parent;
		int levelsCount;
		
		std::vector<Ocleaf> allLeaves;


		// Methods
		Octree();
		~Octree();
		void GenTree(uint levels);
		void SubDivide(Ocleaf leaf);
		void DeleteLevel(Ocleaf leaf);
		std::vector<Ocleaf> leavesInLevel(int _level);
		
	};
}




