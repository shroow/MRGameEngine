#include "shrSceneInfo.h"
#include "shrScene.h"
#include "shrTexture.h"
#include "shrAnimator.h"
#include "shrResources.h"
#include "shrSceneManager.h"
#include "shrShader.h"
#include "shrMaterial.h"

#include <string>
#include <filesystem>

namespace shr
{
	void SceneInfo::Initialize()
	{

	}

	void SceneInfo::LoadResourcesInfo()
	{

		Resources::Load<Texture>(L"CoinTexture", L"UI\\Coin.png");
		Resources::Load<Texture>(L"MoneyPanelTexture", L"UI\\MoneyPanel.png");
		Resources::Load<Texture>(L"BuyUITexture", L"UI\\BuyUI.png");
		Resources::Load<Texture>(L"SellUITexture", L"UI\\SellUI.png");
		Resources::Load<Texture>(L"TempNumTexture", L"UI\\tempNum.png");

		//Monsters
		{
			//NightBorne /Column
			Resources::Load<Texture>(L"NightBorne_Atlas", L"Monsters\\NightBorne\\NightBorne.png");

			eUnitType::End;

			//FreeKight
			LoadTextureList(L"0_", L"Monsters\\FreeKnight\\");

			//Ball and Chain Bot
			LoadTextureList(L"1_", L"Monsters\\Ball and Chain Bot\\");

			//Biker
			LoadTextureList(L"2_", L"Monsters\\Cyberpunk\\Biker\\");

			//Ballman
			LoadTextureList(L"3_", L"Monsters\\Cyberpunk\\Ballman\\");

			//Demon_mage(sheet)
			LoadTextureList(L"6_", L"Monsters\\Demon_mage_creativekind\\Demon_mage-Sheet.png");

			//Necromancer(sheet)
			LoadTextureList(L"7_", L"Monsters\\Necromancer_creativekind-Sheet.png");
		}

		//FreeKight_v1  /Column
		
		//{
		//	eUnitType::FreeKnight;
		//	//////Colour1
		//	/// 1200x80/10							
		//	Resources::Load<Texture>(L"0_Attack", L"FreeKnight_v1\\Colour1\\_AttackComboNoMovement.png");
		//	/// 1200x80_10							
		//	Resources::Load<Texture>(L"0_Death", L"FreeKnight_v1\\Colour1\\_Death.png");
		//	/// 1200x80_10							
		//	//Resources::Load<Texture>(L"FreeKnightv1c1_DeathNoMovement", L"FreeKnight_v1\\Colour1\\_DeathNoMovement.png");
		//	/// 120x80_1							
		//	Resources::Load<Texture>(L"0_Hit", L"FreeKnight_v1\\Colour1\\_Hit.png");
		//	/// 1200x80_10							
		//	Resources::Load<Texture>(L"0_Idle", L"FreeKnight_v1\\Colour1\\_Idle.png");
		//	/// 1440x80_12							
		//	Resources::Load<Texture>(L"0_Skill", L"FreeKnight_v1\\Colour1\\_Roll.png");
		//	/// 1200x80_10							
		//	Resources::Load<Texture>(L"0_Run", L"FreeKnight_v1\\Colour1\\_Run.png");

		//	/////Colour2
		//	/// 1200x80/10							
		//	Resources::Load<Texture>(L"FreeKnightv1c2_Attack", L"FreeKnight_v1\\Colour2\\_AttackCombo.png");
		//	/// 1200x80_10							
		//	Resources::Load<Texture>(L"FreeKnightv1c2_Death", L"FreeKnight_v1\\Colour2\\_Death.png");
		//	/// 1200x80_10							
		//	//Resources::Load<Texture>(L"FreeKnightv1c2_DeathNoMovement", L"FreeKnight_v1\\Colour2\\_DeathNoMovement.png");
		//	/// 120x80_1							
		//	Resources::Load<Texture>(L"FreeKnightv1c2_Hit", L"FreeKnight_v1\\Colour2\\_Hit.png");
		//	/// 1200x80_10							
		//	Resources::Load<Texture>(L"FreeKnightv1c2_Idle", L"FreeKnight_v1\\Colour2\\_Idle.png");
		//	/// 1440x80_12							
		//	Resources::Load<Texture>(L"FreeKnightv1c2_Skill", L"FreeKnight_v1\\Colour2\\_Roll.png");
		//	/// 1200x80_10							
		//	Resources::Load<Texture>(L"FreeKnightv1c2_Run", L"FreeKnight_v1\\Colour2\\_Run.png");
		//}

		////Ball and Chain Bot /Row
		
		//{
		//	eUnitType::BallandChainBot;
		//	/// 126x195/5
		//	Resources::Load<Texture>(L"1_Idle", L"Monsters\\Ball and Chain Bot\\idle.png");
		//	/// 126x312/8
		//	Resources::Load<Texture>(L"1_Attack", L"Monsters\\Ball and Chain Bot\\attack.png");
		//	/// 126x156/4
		//	Resources::Load<Texture>(L"1_Charge", L"Monsters\\Ball and Chain Bot\\charge.png");
		//	/// 126x195/5
		//	Resources::Load<Texture>(L"1_Death", L"Monsters\\Ball and Chain Bot\\death.png");
		//	/// 126x78/2
		//	Resources::Load<Texture>(L"1_Hit", L"Monsters\\Ball and Chain Bot\\hit.png");
		//	/// 126x312/8
		//	Resources::Load<Texture>(L"1_Run", L"Monsters\\Ball and Chain Bot\\run.png");
		//	/// 126x78/2
		//	Resources::Load<Texture>(L"1_TransitionCharge", L"Monsters\\Ball and Chain Bot\\transition to charge.png");
		//}

		///////__________EFFECT__________

		//PSskillEffect Test 
		{
			//72x72/8
			Resources::Load<Texture>(L"Laser", L"Effect\\Skill\\Laser.png");
			Resources::Load<Texture>(L"Thorn", L"Effect\\Skill\\Thorn.png");
			Resources::Load<Texture>(L"Thorn2", L"Effect\\Skill\\Thorn2.png");
			//72x72/4
			Resources::Load<Texture>(L"FireArrow_Texture", L"Effect\\Skill\\FireArrow.png");
			Resources::Load<Texture>(L"FireArrow_Explosion_Texture", L"Effect\\Skill\\FireArrow_Explosion.png");
			//96x96/9
			Resources::Load<Texture>(L"bubble_large_blue"
				, L"Effect\\SPEffectsPack2\\fx2_bubble_large_blue_appear\\spritesheet.png");
			Resources::Load<Texture>(L"bubble_large_white"
				, L"Effect\\SPEffectsPack2\\fx2_bubble_large_white_appear\\spritesheet.png");
			//128 128/10
			Resources::Load<Texture>(L"explosion_large_red"
				, L"Effect\\SPEffectsPack2\\fx2_explosion_large_red\\spritesheet.png");
			//64 64/16
			Resources::Load<Texture>(L"fire_burst_large_orange"
				, L"Effect\\SPEffectsPack2\\fx2_fire_burst_large_orange\\spritesheet.png");
			Resources::Load<Texture>(L"ice_burst_large_white"
				, L"Effect\\SPEffectsPack2\\fx2_ice_burst_large_white\\spritesheet.png");
			//140 50/7
			Resources::Load<Texture>(L"impact_shock_large_brown"
				, L"Effect\\SPEffectsPack2\\fx2_impact_shock_large_brown\\spritesheet.png");
			Resources::Load<Texture>(L"impact_shock_large_orange"
				, L"Effect\\SPEffectsPack2\\fx2_impact_shock_large_orange\\spritesheet.png");
			//64 64/9
			Resources::Load<Texture>(L"slash_large_white"
				, L"Effect\\SPEffectsPack2\\fx2_slash_large_white\\spritesheet.png");
			Resources::Load<Texture>(L"slash_large_orange"
				, L"Effect\\SPEffectsPack2\\fx2_slash_large_orange\\spritesheet.png");
			//64 64/10
			Resources::Load<Texture>(L"splatter_large_black"
				, L"Effect\\SPEffectsPack2\\fx2_splatter_large_black\\spritesheet.png");
			Resources::Load<Texture>(L"splatter_large_orange"
				, L"Effect\\SPEffectsPack2\\fx2_splatter_large_orange\\spritesheet.png");
			Resources::Load<Texture>(L"splatter_large_white"
				, L"Effect\\SPEffectsPack2\\fx2_splatter_large_white\\spritesheet.png");
		}


		///////__________UI___________

		//Default
		{
			{
			std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"DefaultUI_Texture"
				, L"UI\\PNG\\Inventory and Stats\\Inventory Cell.png");
			std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
			uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
			uiMaterial->SetShader(uiShader);
			uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
			Resources::Insert<Material>(L"DefaultUI_Material", uiMaterial);
			}

			//WidgetUI
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"WidgetHorizontal_Texture"
					, L"UI\\UIs\\Widget\\WidgetHorizontal.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"WidgetHorizontal_Material", uiMaterial);
			}
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"WidgetHorizontal_Texture"
					, L"UI\\UIs\\Widget\\WidgetVertical.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"WidgetVertical_Material", uiMaterial);
			}
		}

		//Num Font
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

		//Button
		{
			//Start
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"StartButton_Texture"
					, L"UI\\PNG\\Main menu\\BTN PLAY.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"StartButton_Material", uiMaterial);
			}

			//Setting
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"SettingButton_Texture"
					, L"UI\\PNG\\Main menu\\BTN SETTINGS.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"SettingButton_Material", uiMaterial);
			}

			//Quit
			{
				std::shared_ptr <Texture> uiTexture = Resources::Load<Texture>(L"QuitButton_Texture"
					, L"UI\\PNG\\Main menu\\BTN Exit.png");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"QuitButton_Material", uiMaterial);
			}
		}

		LoadTextureList(L"Test_", L"Monster\\");

		Resources::Find<Texture>(L"Test_Attack3");
	}
	
	//Use Char* type
	/*void SceneInfo::LoadTextureList(const std::wstring& textureName, const std::wstring& path)
	{

		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring folderfullPath = parentPath.wstring() + L"\\Resources\\" + path;

		std::wstring folderPath = path;

		int	folderLength = folderPath.length();

		char	Directory[128] = {};

		int length = WideCharToMultiByte(CP_ACP, 0, path.c_str(), -1, NULL, 0, NULL, NULL);
		if (length <= 128) {
			WideCharToMultiByte(CP_ACP, 0, path.c_str(), -1, Directory, 128, NULL, NULL);
		}

		const char* TextureExtArray[5] = { ".BMP", ".JPG", ".PNG", ".TGA", ".DDS" };

		for (const auto& file : std::filesystem::recursive_directory_iterator(folderfullPath))
		{
			char	FileName[256] = {};
			char	FullPath[MAX_PATH] = {};
			char	Ext[_MAX_EXT] = {};
			char	FolderName[128] = {};

			strcpy_s(FullPath, file.path().generic_string().c_str());
			  
			int	Length = (int)strlen(FullPath);

			for (int i = Length; i >= 0; --i)
			{
				if (FullPath[i] == '/')
					FullPath[i] = '\\';
			}


			if (Length >= folderLength)
			{
				for (int i = Length - folderLength - 1; i >= 0; --i)
				{
					memcpy(FolderName, &FullPath[i], folderLength);

					if (strcmp(FolderName, Directory) == 0)
					{
						strcpy_s(FileName, &FullPath[i + folderLength]);
						break;
					}
				}
			}

			_splitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

			_strupr_s(Ext);

			bool	FileExt = false;

			for (int i = 0; i < 5; ++i)
			{
				if (strcmp(Ext, TextureExtArray[i]) == 0)
				{
					FileExt = true;
					break;
				}
			}

			if (!FileExt)
				continue;

			std::wstring FinalPath = folderPath;

			int length = MultiByteToWideChar(CP_ACP, 0, FileName, -1, NULL, 0);
			wchar_t* wideString = new wchar_t[length];
			MultiByteToWideChar(CP_ACP, 0, FileName, -1, wideString, length);

			std::wstring result(wideString);

			size_t len = wcslen(wideString);
			if (len >= 4) {
				wideString[len - 4] = L'\0';
			}

			std::wstring Name(wideString);

			delete[] wideString;

			Resources::Load<Texture>(textureName + Name, path + result);
		}
	}*/

	//Use wstring type
	void SceneInfo::LoadTextureList(const std::wstring& textureName, const std::wstring& path)
	{
		std::vector<std::wstring> fileNames;

		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring folderfullPath = parentPath.wstring() + L"\\Resources\\" + path;

		for (const auto& entry : std::filesystem::directory_iterator(folderfullPath)) 
		{
			if (entry.is_regular_file()) 
			{
				const std::wstring& filePath = entry.path().wstring();
				std::wstring extension = std::filesystem::path(filePath).extension().wstring();

				// Convert the extension to lowercase for comparison
				std::transform(extension.begin(), extension.end(), extension.begin(), ::towlower);

				// Check if the file has a JPG or PNG extension
				if (extension == L".jpg" || extension == L".png" || extension == L".jpeg")
				{
					std::wstring fileName = std::filesystem::path(filePath).filename().wstring();

					std::wstring texName;
					std::wstring texPath = path + fileName;
					
					size_t lastDotIndex = fileName.find_last_of(L".");
					if (lastDotIndex != std::wstring::npos) 
					{
						texName = textureName + fileName.substr(0, lastDotIndex);
					}

					Resources::Load<Texture>(texName, texPath);
				}
			}
		}
	}
}