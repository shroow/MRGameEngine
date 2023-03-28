#include "shrMeshRenderer.h"
#include "shrGameObject.h"
#include "shrTransform.h"

namespace shr
{
	MeshRenderer::MeshRenderer() 
		: BaseRenderer(eComponentType::MeshRenderer)
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
			
		GetMesh()->BindBuffer();
		GetMaterial()->Bind();

		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}