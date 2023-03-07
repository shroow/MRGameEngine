#pragma once
#include "shrComponent.h"

namespace shr
{
    using namespace math;
    class Camera :
        public Component
    {
    public:
        enum eProjectionType //투영타입
        {
            Perspective, //원근
            Orthographic, //직교
        };

        //__inline 하면 함수형태로 타고 들어오지않고 컴파일과정에서 변환해준다 __forceinline은 강제성 또한 갖고 있다 
        __forceinline static Matrix& GetGPUViewMatrix() { return View; }
        __forceinline static Matrix& GetGPUProjectionMatrix() { return Projection; }
        __forceinline static void SetGPUViewMatrix(Matrix view) { View = view; }
        __forceinline static void SetGPUProjectionMatrix(Matrix projection) { Projection = projection; }

    public:
        Camera();
        virtual ~Camera();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

    public:
        void CreateViewMatrix();
        void CreateProjectionMatrix();
        void RegisterCameraInRenderer();

        void TurnLayerMask(eLayerType layer, bool enable = true);
        void EnableLayerMasks() { mLayerMasks.set(); }
        void DisableLayerMasks() { mLayerMasks.reset(); }

        void SetProjectionType(eProjectionType type) { mType = type; }

        float GetScale() { return mScale; }
        Matrix& GetViewMatrix() { return mView; }
        Matrix& GetProjectionMatrix() { return mProjection; }


    private:
        void sortGameObjects();
        void renderOpaque();
        void renderCutout();
        void renderTransparent();
        void pushGameObjectToRenderingModes(GameObject* gameObj);

    private:
        static Matrix View;
        static Matrix Projection;

        Matrix mView;
        Matrix mProjection;

        eProjectionType mType;
        float mAspectRatio;

        float mNear;
        float mFar;
        float mScale;

        std::bitset<(UINT)eLayerType::End> mLayerMasks;
        std::vector<GameObject*> mOpaqueGameObjectVec;
        std::vector<GameObject*> mCutoutGameObjectVec;
        std::vector<GameObject*> mTransparentGameObjectVec;
    };
}
