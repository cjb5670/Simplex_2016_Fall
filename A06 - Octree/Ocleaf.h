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
		std::vector<MyEntity> fullyContained;

		Ocleaf* Parent;
		std::vector<Ocleaf*> leaves;

		MeshManager* meshManager;

		// Methods
		Ocleaf();
		~Ocleaf();
		bool Contains(MyEntity* object);
		void Draw();
	};
}
#endif


