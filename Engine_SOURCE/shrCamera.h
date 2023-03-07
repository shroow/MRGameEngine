#pragma once
#include "shrComponent.h"

namespace shr
{
    using namespace math;
    class Camera :
        public Component
    {
    public:
        enum eProjectionType //����Ÿ��
        {
            Perspective, //����
            Orthographic, //����
        };

        //__inline �ϸ� �Լ����·� Ÿ�� �������ʰ� �����ϰ������� ��ȯ���ش� __forceinline�� ������ ���� ���� �ִ� 
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
