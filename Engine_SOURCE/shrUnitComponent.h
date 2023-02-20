#pragma once
#include "shrComponent.h"
//유닛컴포넌트: 유닛제어 관련 : 마우스로 클릭시의 반응, 배치, 움직임.

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
