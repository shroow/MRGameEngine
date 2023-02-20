#pragma once
#include "shrComponent.h"
//����������Ʈ: �������� ���� : ���콺�� Ŭ������ ����, ��ġ, ������.

namespace shr 
{
    class UnitComponent :
        public Component
    {
    public:
        UnitComponent();
        virtual ~UnitComponent();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() = 0;

    private:

    };
}
