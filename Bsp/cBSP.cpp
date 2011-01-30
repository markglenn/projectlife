#include "cbsp.h"
#include <windows.h>

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

cPlane  cBSP::impactPlane;
cVector cBSP::impactPoint;

/////////////////////////////////////////////////////////////////////////////////////
cBSP::cBSP(void)
	: m_tree(0)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cBSP::~cBSP(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cBSP::cNode * cBSP::cNode::GetNode(const cVector &position)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (isLeaf)
		return this;

	ePointLoc loc = splitter.TestPoint(position);

	if (loc == PT_FRONT)
		return frontNode->GetNode(position);
	else
		return backNode->GetNode(position);

	// Should never reach this
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cBSP::cNode::HitCheckBSP (cVector v0, cVector v1, cPlane *prevPlane)
/////////////////////////////////////////////////////////////////////////////////////
{
	bool hit = false;
	cVector w0, w1;
	cPlane p;
	cVector refPoint;
	float root;
	float mult = 1.0f;

	if (isLeaf)
	{
		// Determine the collision point and plane
		if (cluster < 0)
		{
			cBSP::impactPlane = *prevPlane;
			cBSP::impactPlane.m_d = prevPlane->m_d - 0.5f;
			cBSP::impactPoint = v0;
			return true;
		}

		// No collision on empty leaves
		return false;
	}

	root = sqrtf (splitter.m_normal.x * splitter.m_normal.x + splitter.m_normal.y * splitter.m_normal.y);
	if (root == 0.f)
		root = 0.1f;

	root = 1.f / root;

	// Create the reference point
	refPoint.x = PLAYER_RADIUS * splitter.m_normal.x * root;
    refPoint.y = PLAYER_RADIUS * splitter.m_normal.y * root;
    refPoint.z = (splitter.m_normal.z > 0) ?  PLAYER_HEIGHT / 2.f : -PLAYER_HEIGHT / 2.f;  

	// Determine the offset
	float offset = -(refPoint * splitter.m_normal);

	// Adjust the plane to test the ray
	p = splitter;
	p.m_d += offset;

	// Calculate the new plane direction based on the direction vector
	cPlane new_plane;
	if (splitter.m_normal * (v1-v0) > 0)
	{
		new_plane.m_normal = - p.m_normal;
		new_plane.m_d = - p.m_d;
		mult = -1.0f;
	} else {
		new_plane.m_normal = p.m_normal;
		new_plane.m_d = p.m_d;
	}

	if (p.RayUnder (v0, v1, &w0, &w1))
	{
		hit = backNode->HitCheckBSP(w0, w1, ((w0==v0)?prevPlane:&new_plane));
		if (hit)
			v1.SetVector(cBSP::impactPoint);
	}

	// Adjust the D component
	p.m_d -= offset * 2;
	new_plane.m_d = mult * p.m_d;
	if (splitter.m_normal * (v1-v0) > 0)
	{
		new_plane.m_normal = - p.m_normal;
		new_plane.m_d = - p.m_d;
		mult = -1.0f;
	} else {
		new_plane.m_normal = p.m_normal;
		new_plane.m_d = p.m_d;
	}
	if (p.RayOver (v0, v1, &w0, &w1))
		hit |= frontNode->HitCheckBSP(v0, v1, ((w0==v0)?prevPlane:&new_plane));

	return hit;
}

/////////////////////////////////////////////////////////////////////////////////////
cVector cBSP::CheckMovement (cEntity& entity) const
/////////////////////////////////////////////////////////////////////////////////////
{
	int iter = 0;
	cNode *tree = (cNode *)&m_tree[0];
	cVector stepStart, stepEnd;
	cVector impact;
	cVector start, end;
	
	// Get the vector from the entity
	start = entity.GetLastPosition();
	end = entity.GetPosition();

	// Player is assumed floating
	entity.SetOnGround(false);

	while (tree->HitCheckBSP(start, end, &impactPlane))
	{
		// Increment the number of collisions
		iter++;

		// Max collisions, just return
		if (iter == MAX_PLANE_COLLISION)
			return impactPoint;
		else
		{
			// Save the impact point
			impact = impactPoint;

			// Set the OnGround boolean if we hit a horizontal plane
			if (impactPlane.m_normal.z < -0.7f)			
				entity.SetOnGround(true);

			// Vertical plane?
			if (ABS(impactPlane.m_normal.z) < 0.01f)
			{
				// Try moving up (step in the way)
				stepStart = impactPoint + cVector (0, 0, -STEP_SIZE);
				stepEnd = end + cVector (0, 0, -STEP_SIZE);

				// Check if the step-up is free of obstacles
				if (!tree->HitCheckBSP(stepStart, stepEnd, &impactPlane))
				{
					// Move back down after movement
					stepStart = stepEnd;
					stepEnd = end;

					// Try moving down
					if (((cNode *)&m_tree[0])->HitCheckBSP(stepStart, stepEnd, &impactPlane))
						return entity.HandlePlaneCollision(impactPlane, impactPoint, stepStart, stepEnd);

					return stepEnd;
				}
			}	
			// Recover the impact point
			impactPoint = impact;

			// Recalculate directional vector
			start = impactPoint;
			end = entity.HandlePlaneCollision(impactPlane, impactPoint, start, end);
		}
	}

//	Assert (impactPlane.m_d == impactPoint.z);
	return end;
}

/////////////////////////////////////////////////////////////////////////////////////
void cBSP::AddEmptyCell(cPlane plane, cVector point)
/////////////////////////////////////////////////////////////////////////////////////
{
	/* Does Not Work!!! */

	cNode *tree = (cNode *)&m_tree[0];
	cNode node, *n1, *n2;
	ePointLoc loc;
	int nodeNum;

	do {
		loc = tree->splitter.TestPoint(point);

		if (point == PT_FRONT)
		{
			if (tree->frontNode->isLeaf)
				return;
			tree = tree->frontNode;
		}
		else
		{
			if (tree->backNode->isLeaf)
			{
				nodeNum = m_tree.size();
				m_tree.push_back (node);
				m_tree.push_back (node);

				ZeroMemory (&m_tree[nodeNum], sizeof (cNode));
				ZeroMemory (&m_tree[nodeNum + 1], sizeof (cNode));

				n1 = &m_tree[nodeNum];
				n2 = &m_tree[nodeNum + 1];
			
				// Setup the splitter node
				m_tree[nodeNum].splitter = plane;
				m_tree[nodeNum].isLeaf = false;
				m_tree[nodeNum].backNode = tree->backNode;
				m_tree[nodeNum].frontNode = &m_tree[nodeNum + 1];

				// Setup the empty node
				m_tree[nodeNum + 1].isLeaf = true;
				m_tree[nodeNum + 1].cluster = 0;

				tree->backNode = &m_tree[nodeNum];
				return;
			}

			tree = tree->backNode;

		}
	} while(true);
}