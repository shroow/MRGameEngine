#include "shrEditor.h"
#include "shrResources.h"
#include "shrMesh.h"
#include "shrMaterial.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrMeshRenderer.h"
#include "shrGridScript.h"
#include "shrObject.h"
#include "shrGridScript.h"
#include "shrObject.h"

namespace shr
{
	void Editor::Initalize()
	{
		mDebugObjectVec.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"DebugRectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"DebugMaterial");

		mDebugObjectVec[(UINT)eColliderType::Rect] = new DebugObject();
		
		MeshRenderer* renderer = mDebugObjectVec[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();
		
		renderer->SetMaterial(material);
		renderer->SetMesh(rectMesh);

		std::shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"CircleMesh");

		mDebugObjectVec[(UINT)eColliderType::Circle] = new DebugObject();

		renderer = mDebugObjectVec[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();

		renderer->SetMaterial(material);
		renderer->SetMesh(circleMesh);

		
		//Grid Object
		{
			EditorObject* gridObject = new EditorObject();
			MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridScript = gridObject->AddComponent<GridScript>();
			gridScript->SetCamera(mainCamera);

			mEditorObjectVec.push_back(gridObject);
		}
	}

	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjectVec)
		{
			obj->Update();
		}
	}

	void Editor::FixedUpdate()
	{
		for (EditorObject* obj : mEditorObjectVec)
		{
			obj->FixedUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjectVec)
		{
			obj->Render();
		}

		for (DebugMesh& mesh : renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
	}

	void Editor::Release()
	{
		for (Widget* obj : mWidgetVec)
		{
			delete obj;
			obj = nullptr;
		}

		for (EditorObject* obj : mEditorObjectVec)
		{
			delete obj;
			obj = nullptr;
		}

		delete mDebugObjectVec[(UINT)eColliderType::Rect];
		delete mDebugObjectVec[(UINT)eColliderType::Circle];
	}

	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjectVec[(UINT)mesh.type];

		Transform* tr = debugObj->GetComponent<Transform>();
		tr->SetPosition(mesh.position);
		tr->SetRotation(mesh.rotatation);

		if (mesh.type == eColliderType::Rect)
			tr->SetScale(mesh.scale);
		else
			tr->SetScale(Vector3(mesh.radius));

		BaseRenderer* renderer = debugObj->GetComponent<BaseRenderer>();
		Camera* camera = renderer::mainCamera;

		tr->FixedUpdate();

		Camera::SetGPUViewMatrix(renderer::mainCamera->GetGPUViewMatrix());
		Camera::SetGPUProjectionMatrix(renderer::mainCamera->GetGPUProjectionMatrix());

		debugObj->Render();
	}
}