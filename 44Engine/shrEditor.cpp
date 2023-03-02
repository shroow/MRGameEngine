#include "shrEditor.h"
#include "shrResources.h"
#include "shrMesh.h"
#include "shrMaterial.h"
#include "shrGameObject.h"
#include "shrTransform.h"
#include "shrMeshRenderer.h"

namespace shr
{
	void Editor::Initalize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Transform>();
		
		MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();
		
		renderer->SetMaterial(material);
		renderer->SetMesh(rectMesh);

		std::shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"CircleMesh");

		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<Transform>();

		renderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();

		renderer->SetMaterial(material);
		renderer->SetMesh(circleMesh);
	}

	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
	}

	void Editor::FixedUpdate()
	{
	}

	void Editor::Render()
	{
	}

	void Editor::Release()
	{
	}

	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		//DebugObject* debugObj = 
	}
}