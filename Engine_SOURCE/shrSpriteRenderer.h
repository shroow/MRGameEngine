#pragma once
#include "shrComponent.h"
#include "shrMesh.h"
#include "shrMaterial.h"

using namespace shr::graphics;
namespace shr
{
    class SpriteRenderer :
        public Component
    {
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr <Material> shader) { mMaterial = shader; }

	private:
		std::shared_ptr <Mesh> mMesh;
		std::shared_ptr <Material> mMaterial;
    };
}
