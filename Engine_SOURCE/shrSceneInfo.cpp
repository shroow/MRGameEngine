#include "shrSceneInfo.h"
#include "shrScene.h"
#include "shrTexture.h"
#include "shrAnimator.h"
#include "shrResources.h"
#include "shrSceneManager.h"
#include "shrShader.h"
#include "shrMaterial.h"
namespace shr
{
	void SceneInfo::Initialize()
	{

	}

	void SceneInfo::LoadResourcesInfo()
	{
		//Test1 Texture
		{
			//Biker
			Resources::Load<Texture>(L"Biker_Idle", L"Monsters\\Cyberpunk\\Biker\\Biker_idle.png");
			Resources::Load<Texture>(L"Biker_Death", L"Monsters\\Cyberpunk\\Biker\\Biker_death.png");
			Resources::Load<Texture>(L"Biker_Attack", L"Monsters\\Cyberpunk\\Biker\\Biker_attack1.png");
			Resources::Load<Texture>(L"Biker_Run", L"Monsters\\Cyberpunk\\Biker\\Biker_run.png");


			//Monster
			Resources::Load<Texture>(L"Monster_Idle", L"Monster\\Idle.png");
			Resources::Load<Texture>(L"Monster_Death", L"Monster\\Death.png");
			Resources::Load<Texture>(L"Monster_Attack2", L"Monster\\Attack2.png");
		}

		//NightBorne /Column
		Resources::Load<Texture>(L"NightBorne_Atlas", L"Monsters\\NightBorne\\NightBorne.png");

		Resources::Load<Texture>(L"CoinTexture", L"UI\\Coin.png");
		Resources::Load<Texture>(L"MoneyPanelTexture", L"UI\\MoneyPanel.png");
		Resources::Load<Texture>(L"BuyUITexture", L"UI\\BuyUI.png");
		Resources::Load<Texture>(L"SellUITexture", L"UI\\SellUI.png");
		Resources::Load<Texture>(L"TempNumTexture", L"UI\\tempNum.png");

		//Ball and Chain Bot /Row
		{
			eUnitType::BallandChainBot;

			/// 126x195/5
			Resources::Load<Texture>(L"1_Idle", L"Monsters\\Ball and Chain Bot\\idle.png");
			/// 126x312/8
			Resources::Load<Texture>(L"1_Attack", L"Monsters\\Ball and Chain Bot\\attack.png");
			/// 126x156/4
			Resources::Load<Texture>(L"1_Charge", L"Monsters\\Ball and Chain Bot\\charge.png");
			/// 126x195/5
			Resources::Load<Texture>(L"1_Death", L"Monsters\\Ball and Chain Bot\\death.png");
			/// 126x78/2
			Resources::Load<Texture>(L"1_Hit", L"Monsters\\Ball and Chain Bot\\hit.png");
			/// 126x312/8
			Resources::Load<Texture>(L"1_Run", L"Monsters\\Ball and Chain Bot\\run.png");
			/// 126x78/2
			Resources::Load<Texture>(L"1_TransitionCharge", L"Monsters\\Ball and Chain Bot\\transition to charge.png");
		}

		//FreeKight_v1  /Column
		{
			eUnitType::FreeKnight;
			//////Colour1
			/// 480x80/5
			//Resources::Load<Texture>(L"FreeKnightv1c1_Attack", L"FreeKnight_v1\\Colour1\\_Attack.png");
			/// 720x80/6							
			//Resources::Load<Texture>(L"FreeKnightv1c1_Attack2", L"FreeKnight_v1\\Colour1\\_Attack2.png");
			/// 720x80/6							
			//Resources::Load<Texture>(L"FreeKnightv1c1_Attack2NoMovement", L"FreeKnight_v1\\Colour1\\_Attack2NoMovement.png");
			/// 1200x80/10							
			//Resources::Load<Texture>(L"FreeKnightv1c1_AttackCombo", L"FreeKnight_v1\\Colour1\\_AttackCombo.png");
			/// 1200x80/10							
			Resources::Load<Texture>(L"0_Attack", L"FreeKnight_v1\\Colour1\\_AttackComboNoMovement.png");
			/// 480x80_4					
			//Resources::Load<Texture>(L"FreeKnightv1c1_AttackNoMovement", L"FreeKnight_v1\\Colour1\\_AttackNoMovement.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"0_Death", L"FreeKnight_v1\\Colour1\\_Death.png");
			/// 1200x80_10							
			//Resources::Load<Texture>(L"FreeKnightv1c1_DeathNoMovement", L"FreeKnight_v1\\Colour1\\_DeathNoMovement.png");
			/// 120x80_1							
			Resources::Load<Texture>(L"0_Hit", L"FreeKnight_v1\\Colour1\\_Hit.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"0_Idle", L"FreeKnight_v1\\Colour1\\_Idle.png");
			/// 1440x80_12							
			Resources::Load<Texture>(L"0_Skill", L"FreeKnight_v1\\Colour1\\_Roll.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"0_Run", L"FreeKnight_v1\\Colour1\\_Run.png");

			/////Colour2
			/// 480x80/5
			//Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_Attack.png");
			/// 720x80/6							  
			//Resources::Load<Texture>(L"FreeKnightv1c2_Attack2", L"FreeKnight_v1\\Colour2\\_Attack2.png");
			/// 720x80/6							  
			//Resources::Load<Texture>(L"FreeKnightv1c2_Attack2NoMovement", L"FreeKnight_v1\\Colour2\\_Attack2NoMovement.png");
			/// 1200x80/10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_AttackCombo.png");
			/// 1200x80/10							
			//Resources::Load<Texture>(L"FreeKnightv1c2_AttackComboNoMovement", L"FreeKnight_v1\\Colour2\\_AttackComboNoMovement.png");
			/// 480x80_4							  
			//Resources::Load<Texture>(L"FreeKnightv1c2_AttackNoMovement", L"FreeKnight_v1\\Colour2\\_AttackNoMovement.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Death", L"FreeKnight_v1\\Colour2\\_Death.png");
			/// 1200x80_10							
			//Resources::Load<Texture>(L"FreeKnightv1c2_DeathNoMovement", L"FreeKnight_v1\\Colour2\\_DeathNoMovement.png");
			/// 120x80_1							
			Resources::Load<Texture>(L"FreeKnightv1c2_Hit", L"FreeKnight_v1\\Colour2\\_Hit.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Idle", L"FreeKnight_v1\\Colour2\\_Idle.png");
			/// 1440x80_12							
			Resources::Load<Texture>(L"FreeKnightv1c2_Skill", L"FreeKnight_v1\\Colour2\\_Roll.png");
			/// 1200x80_10							
			Resources::Load<Texture>(L"FreeKnightv1c2_Run", L"FreeKnight_v1\\Colour2\\_Run.png");
		}

		//Font
		{
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_0", L"UI\\Font\\0.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_0", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_1", L"UI\\Font\\1.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_1", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_2", L"UI\\Font\\2.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_2", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_3", L"UI\\Font\\3.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_3", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_4", L"UI\\Font\\4.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_4", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_5", L"UI\\Font\\5.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_5", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_6", L"UI\\Font\\6.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_6", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_7", L"UI\\Font\\7.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_7", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_8", L"UI\\Font\\8.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_8", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"Num_9", L"UI\\Font\\9.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Material_Num_9", uiMaterial);
			}
		}
	}
}