#pragma once

namespace shr::enums
{
	enum class eSceneType
	{
		Test,
		Title,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Mouse,
		Grid,
		Background,
		Monster,
		Player,
		Particle,
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

	enum class eUnitState
	{
		None = 0,
		Idle,
		Move,
		Attack,
		Skill,
		Buff,
		Debuff,
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

	enum class eCharState
	{
		None,
		Idle,
		Run,
		Attack,
		Attack2,
		Skill,
		Skill2,
		Hit,
		Death,
		End
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

	enum class eUnitType
	{
		FreeKnight,
		BallandChainBot,

		End,
	};

	struct Status
	{
		float maxHP;
		float HP;
		float maxMP;
		float MP;

		float attackDmg;
		float attackSpeed;
		float attackRange;

		float moveSpeed;
		eMoveType moveType;

		//Skill needed

		std::vector<float> buffVec[(UINT)eBuffType::End];

		Status() : maxHP{ 100.f }, HP{ 100.f }, maxMP{ 100.f }, MP{ 20.f }
			, attackDmg{ 10.f }, attackSpeed{ 1.f }, attackRange{ 10.f }
			, moveSpeed{ 10.f }, moveType{ eMoveType::Ground }, buffVec{} {}

		Status(float hp, float MaxHP, float mp, float MaxMP, float AttackDmg, float AttackSpeed
			, float AttackRange, float MoveSpeed, eMoveType MoveType)
			: maxHP{ MaxHP }, HP{ hp }, maxMP{ MaxMP }, MP{ mp }
			, attackDmg{ AttackDmg }, attackSpeed{ AttackSpeed }, attackRange{ AttackRange }
			, moveSpeed{ MoveSpeed }, moveType{ MoveType }, buffVec{} {}


		Status(const Status&) = default;
		Status& operator=(const Status&) = default;
	};
}