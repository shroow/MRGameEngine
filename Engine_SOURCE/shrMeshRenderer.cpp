#include "shrMeshRenderer.h"
#include "shrGameObject.h"
#include "shrTransform.h"

namespace shr
{
	MeshRenderer::MeshRenderer() 
		: Component(eComponentType::Mesh)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::FixedUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mMaterial->Bind();
		mMesh->BindBuffer();


		mMesh->Render();
	}
}