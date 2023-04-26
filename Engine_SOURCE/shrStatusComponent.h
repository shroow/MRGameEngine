#pragma once
#include "shrComponent.h"

namespace shr
{
    class StatusComponent :
        public Component
    {
    public:
        StatusComponent();
        virtual ~StatusComponent();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() = 0;

        void SetStatus(Status status) { mStatus = status; }
        Status GetStatus() { return mStatus; }

    private:
        Status mStatus;
    };
}

