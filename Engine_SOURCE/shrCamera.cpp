#include "shrCamera.h"
#include "shrTransform.h"
#include "shrGameObject.h"
#include "shrApplication.h"
#include "shrRenderer.h"
#include "shrScene.h"
#include "shrSceneManager.h"
#include "shrMaterial.h"
#include "shrBaseRenderer.h"

extern shr::Application application;

namespace shr
{
	Matrix Camera::View = Matrix::Identity;			//View와 mView를 따로 만든 이유 찾기
	Matrix Camera::Projection = Matrix::Identity;	//Proj와 mProj를 따로 만든 이유 찾기

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mAspectRatio(1.0f)
		, mNear(1.f)
		, mFar(1000.0f)
		, mScale(1.0f)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		RegisterCameraInRenderer();
	}

	void Camera::Update()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void Camera::FixedUpdate()
	{
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Crate Translate view matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		mView *= viewRotate;
	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH
			(
				XM_2PI / 6.0f
				, mAspectRatio
				, mNear
				, mFar
			);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 50.f, height / 50.f, mNear, mFar);
		}
	}

	void Camera::RegisterCameraInRenderer()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		renderer::cameras[(UINT)type].push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}

	Vector3 Camera::GetWorldPos()
	{
		return GetOwner()->GetComponent<Transform>()->GetPosition();
	}

	void Camera::sortGameObjects()
	{
		mOpaqueGameObjectVec.clear();
		mCutoutGameObjectVec.clear();
		mTransparentGameObjectVec.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjectVec vecGameObj = layer.GetGameObjectVec();
				if (vecGameObj.size() == 0)
					continue;

				for (GameObject* obj : vecGameObj)
				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}

	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjectVec)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjectVec)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjectVec)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer
			= gameObj->GetComponent<BaseRenderer>();

		if (renderer == nullptr)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();

		std::wstring DebugName = gameObj->GetName();
		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case shr::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjectVec.push_back(gameObj);
			break;
		case shr::graphics::eRenderingMode::CutOut:
			mCutoutGameObjectVec.push_back(gameObj);
			break;
		case shr::graphics::eRenderingMode::Transparent:
			mTransparentGameObjectVec.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}