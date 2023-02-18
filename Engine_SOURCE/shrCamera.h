#pragma once
#include "shrComponent.h"

namespace shr
{
    using namespace shr::math;
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
        __forceinline static Matrix& GetViewMatrix() { return View; }
        __forceinline static Matrix& GetProjectionMatrix() { return Projection; }

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
        std::vector<GameObject*> mOpaqueGameObjects;
        std::vector<GameObject*> mCutoutGameObjects;
        std::vector<GameObject*> mTransparentGameObjects;
    };
}
