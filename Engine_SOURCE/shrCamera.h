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
        __forceinline static Matrix& GetViewMatrix() { return mView; }
        __forceinline static Matrix& GetProjectionMatrix() { return mProjection; }

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

    private:
        static Matrix mView;
        static Matrix mProjection;

        eProjectionType mType;
        float mAspectRatio;

        float mNear;
        float mFar;
        float mScale;
    };
}
