#pragma once

#include <vector>
#include "../Math/cPlane.h"
#include "../Entity/cEntity.h"

#define MAX_PLANE_COLLISION 20
#define PLAYER_RADIUS 15.f
#define PLAYER_HEIGHT 50.f
#define STEP_SIZE 30.f

class cBSP
{
public:
	cBSP(void);
	~cBSP(void);

	cVector CheckMovement (cEntity &entity) const;
	void AddEmptyCell (cPlane plane, cVector point);

	class cNode
	{
	public:
		cNode* GetNode (const cVector &position);
		bool HitCheckBSP (cVector v0, cVector v1, cPlane *prevPlane);

		cPlane splitter;
		bool isLeaf;

		// Leafs are after all the nodes
		cNode * frontNode;
		cNode * backNode;

		// Bounding box
		float minBoundingBox[3];
		float maxBoundingBox[3];

		// Leaf specific
		int cluster;
		int leafFace;
		int numLeafFace;
	};

	static cPlane  impactPlane;
	static cVector impactPoint;

	std::vector <cNode> m_tree;
	int		 m_leaves;
	int		 m_nLeaves;
};
