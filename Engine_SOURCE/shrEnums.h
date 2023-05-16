#pragma once

namespace shr::enums
{
	enum class eSceneType
	{
		Background,
		Test,
		Title,
		Play,
		Store,
		Battle,
		Setting,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Background,
		Monster,
		Monster2,
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

		MeshRenderer,
		SpriteRenderer,
		Animator,

		Collider,
		Collider2,

		ParticleSystem,
		Light,
		UI,

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
		End,
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

	enum class ePlayerType
	{
		None,
		Player,
		Store,
		Enemy,
	};

	enum class eUnitType
	{
		None = -1,
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