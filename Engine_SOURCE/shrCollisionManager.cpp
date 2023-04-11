#include "shrCollisionManager.h"
#include "shrScene.h"
#include "shrSceneManager.h"
#include "shrInput.h"

namespace shr
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;
	std::bitset<(UINT)eLayerType::End> CollisionManager::mMouseLayerCollisionBit = {};
	Collider2D* CollisionManager::mPrevMouseCollision;

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; column++)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
		MouseCollision(scene);
	}

	void CollisionManager::FixedUpdate()
	{
	}

	void CollisionManager::Render()
	{
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}

		mLayerCollisionMatrix[row][column] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjectVec(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjectVec(right);

		for (GameObject* left : lefts)
		{
			if (left->GetState() != GameObject::Active)
				continue;
			if (left->GetComponent<Collider2D>() == nullptr)
				continue;


			for (GameObject* right : rights)
			{
				if (right->GetState() != GameObject::Active)
					continue;
				if (right->GetComponent<Collider2D>() == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<Collider2D>(), right->GetComponent<Collider2D>());
			}

			if ((UINT)left == (UINT)right)
				break;
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체 레이어로 구성된 ID 확인
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		// 이전 충돌 정보를 검색한다.
		// 만약에 충돌정보가 없는 상태라면
		// 충돌정보를 생성해준다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// 충돌체크를 해준다.
		if (Intersect(left, right)) // 충돌을 한 상태
		{
			// 최초 충돌중 Enter
			if (iter->second == false)
			{
				if (left->IsTrigger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTrigger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else // 충돌 중이지 않은 상태 Enter
			{
				if (left->IsTrigger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTrigger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}
		}
		else // 충돌하지 않은상태
		{
			// 충돌 중인상태 Exit
			if (iter->second == true)
			{
				if (left->IsTrigger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTrigger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{

		eColliderType leftType = left->GetType();
		eColliderType rightType = right->GetType();

		if(leftType == eColliderType::Rect && rightType == eColliderType::Rect)
		{
			// Rect vs Rect 
			// 0 --- 1
			// |     |
			// 3 --- 2

			Vector3 arrLocalPos[4] =
			{
				Vector3{-0.5f, 0.5f, 0.0f}
				,Vector3{0.5f, 0.5f, 0.0f}
				,Vector3{0.5f, -0.5f, 0.0f}
				,Vector3{-0.5f, -0.5f, 0.0f}
			};

			Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
			Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

			Matrix leftMat = leftTr->GetWorldMatrix();
			Matrix rightMat = rightTr->GetWorldMatrix();


			// 분리축 벡터 4개 구하기
			Vector3 Axis[4] = {};

			Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);

			Matrix finalLeft = Matrix::CreateScale(leftScale);
			finalLeft *= leftMat;

			Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
			Matrix finalRight = Matrix::CreateScale(rightScale);
			finalRight *= rightMat;

			Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
			Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
			Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
			Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

			Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

			for (size_t i = 0; i < 4; i++)
				Axis[i].z = 0.0f;

			Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
			vc.z = 0.0f;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vA = Axis[i];
				//vA.Normalize();

				float projDist = 0.0f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
				}

				if (projDist < fabsf(centerDir.Dot(vA)))
				{
					return false;
				}
			}
		}
		// 숙제 Circle vs Cirlce
		else if (leftType == eColliderType::Circle && rightType == eColliderType::Circle)
		{
			Vector3 leftPos = left->GetPosition();
			Vector3 rightPos = right->GetPosition();

			//float fRadius = 0.5f;
			float leftRadius = left->GetRadius();
			float rightRadius = right->GetRadius();

			float distance = Vector2::Distance(Vector2(leftPos.x, leftPos.y), Vector2(rightPos.x, rightPos.y));

			if (distance > leftRadius + rightRadius)
				return false;
			else
				return true;
		}
		//Point 
		//Rotation collide needed
		else if (leftType == eColliderType::Point && rightType == eColliderType::Rect)
		{
			Vector3 pointPos = left->GetPosition();

			Vector3 rectPos = right->GetPosition() + right->GetCenter();

			Vector3 rectSclae = right->GetOwner()->GetComponent<Transform>()->GetScale();

			if ((right->GetSize().x * rectSclae.x * 0.5f) >= abs(pointPos.x - rectPos.x)
				&& (right->GetSize().y * rectSclae.y * 0.5f) >= abs(pointPos.y - rectPos.y))
			{
				return true;
			}
			else
				return false;

			////Rotation
			//Vector2	CenterLine = left - right.Center;

			//Vector2	Axis = right.Axis[AXIS2D_X];

			//float CenterProjDist = abs(Axis.Dot(CenterLine));

			//if (CenterProjDist > right.Length[AXIS2D_X])
			//	return false;

			//Axis = right.Axis[AXIS2D_Y];

			//CenterProjDist = abs(Axis.Dot(CenterLine));

			//if (CenterProjDist > right.Length[AXIS2D_Y])
			//	return false;

			//HitPoint = Src;

			//return true;
		}
		else if (leftType == eColliderType::Line && rightType == eColliderType::Rect)
		{
			Vector3 linePos = left->GetPosition() + right->GetCenter();
			Vector3 lineRPos = linePos; 
			float radius = left->GetRadius() * 0.5f;
			Vector3 lineRotation = left->GetRotation();
			lineRPos += Vector3(radius * cosf(XMConvertToRadians(lineRotation.z))
								, radius * sinf(XMConvertToRadians(lineRotation.z)), 0.f);

			Vector3 rectPos = right->GetPosition() + right->GetCenter();
			Vector3 rectRotation = right->GetRotation();

			Vector3 rectScale = right->GetOwner()->GetComponent<Transform>()->GetScale();
			Vector2 rectSize = right->GetSize();
			rectScale *= Vector3(rectSize.x, rectSize.y, 1.0f);



			Vector3 arrLocalPos[4] =
			{
				Vector3{-0.5f, 0.5f, 0.0f}
				,Vector3{0.5f, 0.5f, 0.0f}
				,Vector3{0.5f, -0.5f, 0.0f}
				,Vector3{-0.5f, -0.5f, 0.0f}
			};


			if (rectRotation.z != 0.f)
				int a = 0;

			for (size_t i = 0; i < 4; i++)
			{
				arrLocalPos[i] = rectPos + rectScale * arrLocalPos[i];
				
				//Vector3 vertexPos = rectScale * arrLocalPos[i];
				//float x = 0.5f * sinf(rectRotation.z);
				//float y = 0.5f * cosf(rectRotation.z);
				//vertexPos.x += sinf(rectRotation.z);
				//vertexPos.y += cosf(rectRotation.z);
				//arrLocalPos[i] = rectPos + Vector3(vertexPos.x, vertexPos.y, 0.f);			
			}


			for (size_t i = 0; i < 4; i++)
			{
				size_t j = i + 1;
				if (j == 4)
					j = 0;

				//float x1 = linePos.x;
				//float y1 = linePos.y;
				//float x2 = lineRPos.x;
				//float y2 = lineRPos.y;
				// 
				//float x3 = arrLocalPos[i].x;
				//float y3 = arrLocalPos[i].y;
				//float x4 = arrLocalPos[j].x;
				//float y4 = arrLocalPos[j].y;
				//
				//// calculate the direction of the lines
				//float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) 
				//			/ ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
				//float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3))
				//			/ ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
				
				// calculate the direction of the lines
				float uA = ((arrLocalPos[j].x - arrLocalPos[i].x) * (linePos.y - arrLocalPos[i].y) - (arrLocalPos[j].y - arrLocalPos[i].y) * (linePos.x - arrLocalPos[i].x))
					/ ((arrLocalPos[j].y - arrLocalPos[i].y) * (lineRPos.x - linePos.x) - (arrLocalPos[j].x - arrLocalPos[i].x) * (lineRPos.y - linePos.y));
				float uB = ((lineRPos.x - linePos.x) * (linePos.y - arrLocalPos[i].y) - (lineRPos.y - linePos.y) * (linePos.x - arrLocalPos[i].x))
					/ ((arrLocalPos[j].y - arrLocalPos[i].y) * (lineRPos.x - linePos.x) - (arrLocalPos[j].x - arrLocalPos[i].x) * (lineRPos.y - linePos.y));

				// if uA and uB are between 0-1, lines are colliding
				if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
					return true;
			}

			return false;

		}
		else
		{
			return false;
		}

		return true;
	}

	void CollisionManager::MouseCollision(Scene* scene)
	{
		Collider2D* mostFront = nullptr;

		for (UINT type = 0; type < (UINT)eLayerType::End; type++)
		{
			if (!mMouseLayerCollisionBit[type])
				continue;

			const std::vector<GameObject*>& objs = scene->GetGameObjectVec((eLayerType)type);

			for (GameObject* obj : objs)
			{
				if (obj->GetState() != GameObject::Active)
					continue;
				if (obj->GetComponent<Collider2D>() == nullptr)
					continue;

				Collider2D* objCol = obj->GetComponent<Collider2D>();

				if (MouseIntersect(objCol))
				{
					if (mostFront == nullptr)
						mostFront = objCol;
					else
					{
						Vector3 mostFrontPos = objCol->GetPosition();
						Vector3 objPos = objCol->GetPosition();

						if (mostFrontPos.z < objPos.z)
						{
							mostFront = objCol;
						}
						else if (mostFrontPos.z == objPos.z)
						{
							if (mostFrontPos.y < objPos.y)
								mostFront = objCol;
							else if (mostFrontPos.y == objPos.y)
								mostFront = objCol;
						}
					}
				}
				else
					continue;
			}
		}

		if (mostFront == nullptr) //충돌 안 한상태
		{
			// 충돌 중인상태 Exit
			if (mPrevMouseCollision != nullptr)
			{
				mPrevMouseCollision->OnMouseCollisionExit();

				mPrevMouseCollision = nullptr;
			}
			return;
		}

		if (mPrevMouseCollision != nullptr) // 충돌을 한 상태
		{
			// 최초 충돌중 Enter
			if (mPrevMouseCollision != mostFront)
			{
				mostFront->OnMouseCollisionEnter();

				mPrevMouseCollision->OnMouseCollisionExit();

				mPrevMouseCollision = mostFront;
			}
			else // 이미 충돌한 물체 Stay
			{
				mostFront->OnMouseCollisionStay();

				mPrevMouseCollision = mostFront;
			}
		}
		else
		{
			mostFront->OnMouseCollisionEnter();

			mPrevMouseCollision = mostFront;
		}
	}
	bool CollisionManager::MouseIntersect(Collider2D* collider)
	{
		eColliderType cType = collider->GetType();

		GameObject* objg = collider->GetOwner();

		if (cType == eColliderType::Rect)
		{
			Vector2 pointPos = Input::GetMouseWorldPos();

			Vector3 rectPos = collider->GetPosition();

			Vector3 rectSclae = collider->GetOwner()->GetComponent<Transform>()->GetScale();

			if ((collider->GetSize().x * rectSclae.x * 0.5f) >= abs(pointPos.x - rectPos.x)
				&& (collider->GetSize().y * rectSclae.y * 0.5f) >= abs(pointPos.y - rectPos.y))
			{
				return true;
			}
		}

		return false;
	}
	void CollisionManager::MouseCollisionLayerCheck(eLayerType type, bool enable)
	{
		mMouseLayerCollisionBit[(UINT)type] = enable;
	}
}
