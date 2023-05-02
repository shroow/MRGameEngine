#include "shrPlayerScript.h"
#include "shrTransform.h"
#include "shrGameObject.h"
#include "shrInput.h"
#include "shrTime.h"
#include "shrAnimator.h"

#include "shrPlayerObject.h"
#include "shrSceneManager.h"
#include "shrBattleScene.h"
#include "shrStoreScene.h"

namespace shr
{
	PlayerScript::PlayerScript() 
		: Script(eScriptType::UnitScript)
		, mOwner(nullptr)
		, mMaxMoney(0.f)
		, mMoney(0.f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		mOwner = (PlayerObject*)GetOwner();
	}

	void PlayerScript::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		//플레이어 HP=0 죽었을때의 UI화면 띄워주기
		if (mOwner->GetPlayerState() == ePlayerState::Dead)
		{
			GameObject* gameObj = new GameObject();
			Layer& layer = scene->GetLayer(eLayerType::SystemUI);
			gameObj->SetLayerType(eLayerType::SystemUI);
			layer.AddGameObject(gameObj);
			gameObj->Initialize();
			
			{
				//UI 오브젝트 추가해주기
			}

			return;
		}


	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
}