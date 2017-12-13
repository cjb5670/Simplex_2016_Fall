#pragma once
#ifndef __OCLEAF_H_
#define __OCLEAF_H_

#include "MyEntityManager.h"
namespace Simplex
{
	class Ocleaf
	{
	public:
	
		// Members
		// Data for tree
		int leafCount;


		// Data for leaf
		int ID;
		int level;
		bool hasChildren;
		float size;
		vector3 center;
		vector3 min;
		vector3 max;

		std::vector<int> EntityList; 

		Ocleaf* Parent;
		std::vector<Ocleaf*> leaves;

		MeshManager* meshManager;
		MyEntityManager* entityManager;

		// Methods
		Ocleaf();
		~Ocleaf();
		bool Contains(MyEntity object);
	};
}
#endif


