#include "shrParticleSystem.h"
#include "shrResources.h"
#include "shrGameObject.h"
#include "shrStructedBuffer.h"

namespace shr
{
	ParticleSystem::ParticleSystem()
		: BaseRenderer(eComponentType::ParticleSystem)
		, mCount(0)
		, mStartSize(Vector4::Zero)
		, mEndtSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.f)
	{
		std::shared_ptr<Mesh> rect = Resources::Find<Mesh>(L"RectMesh");
		SetMesh(rect);

		//Material
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		Particle particles[1000] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);
		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 16; x++)
			{
				particles[16 * y + x].position = startPos
					+ Vector4(x * 100.0f, y * 100.0f, 0.0f, 0.0f);
			}
		}

		mCount = 144;
		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::None, particles);

	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}

	void ParticleSystem::Initialize()
	{
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FixedUpdate()
	{
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mBuffer->Bind(eShaderStage::VS, 15);
		mBuffer->Bind(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);
	}
}
