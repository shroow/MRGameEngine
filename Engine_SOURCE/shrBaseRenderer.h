#pragma once
#include "shrComponent.h"
#include "shrMesh.h"
#include "shrMaterial.h"

namespace shr
{
    class BaseRenderer :
        public Component
    {
    public:
        BaseRenderer(eComponentType type);
        virtual ~BaseRenderer();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
        void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
        std::shared_ptr<Mesh> GetMesh() { return mMesh; }
        std::shared_ptr<Material> GetMaterial() { return mMaterial; }

    private:
        std::shared_ptr<Mesh> mMesh;
        std::shared_ptr<Material> mMaterial;
    };
}
