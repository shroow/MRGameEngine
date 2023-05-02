#pragma once

namespace shr::enums
{
	enum class eSceneType
	{
		Test,
		Title,
		Play,
		Store,
		Battle,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Background,
		Monster,
		Player,
		Particle,
		Mouse,
		UI,
		SystemUI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,

		Collider2,
		MeshRenderer,
		SpriteRenderer,
		ParticleSystem,
		Animator,

		Light,
		UI,
		Status,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		//Font,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Point,
		Line,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum eUnitState
	{
		Idle = 0,
		Run,
		Attack,
		Attack2,
		Skill,
		Skill2,
		Hit,
		Death,
		End = 16,
	};

	enum class eBuffType
	{
		None,
		StatBuff,
		StatDebuff,
		Stun,
		End = 16,
	};


	enum class eMoveType
	{
		Ground,
		Fly,
		Building,
	};

	enum class eAtlasType
	{
		Row,
		Column,
		Compound,
	};

	enum class eScriptType
	{
		None,
		UnitScript,
		ObjectScript,
		End,
	};
	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

	enum class ePlayerState
	{
		Pause,
		Store,
		Battle,
		Dead,
	};

	enum class eUnitType
	{
		None,
		FreeKnight,
		BallandChainBot,
		
		End,
	};

	enum class eHeroType
	{
		None,
		Knight,
		Hunter,
		Chef,
		Dealer,
		End,
	};
}