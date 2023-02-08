#pragma once
#include "shrComponent.h"
#include "shrMesh.h"
//#include "shrShader.h"
#include "shrMaterial.h"

using namespace shr::graphics;
namespace shr
{

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; };
		//void SetShader(Shader* shader) { mShader = shader; };
		void SetMaterial(Material* material) { mMaterial = material; };

	private:
		Mesh* mMesh;
		//Shader* mShader;
		Material* mMaterial;
	};

}