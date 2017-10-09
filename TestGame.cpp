#include "TestGame.h"
#include "SkinnedMeshShaderPath.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

TestGame::TestGame()
{
}


TestGame::~TestGame()
{
}

HRESULT TestGame::OnInit()
{
	//��Ų�� �޽ÿ� ���ؽ�Ÿ��
	auto vertexType = std::make_shared<MnSkinnedMeshVertexType>();

	//������ �ʱ�ȭ
	m_spSkinnedMeshRenderer = std::make_shared<MnSkinnedMeshRenderer>();
	HRESULT result = m_spSkinnedMeshRenderer->Init(GetD3DDevice(), vertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(TestGame::m_spSkinnedMeshRenderer));
		return result;
	}

	//���̴��н� �ʱ�ȭ
	auto shaderPath = std::make_shared<SkinnedMeshShaderPath>();
	result = shaderPath->Init(GetD3DDevice(), vertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(shaderPath));
		return result;
	}
	m_spSkinnedMeshRenderer->AddShaderPathInstance(shaderPath);

	//�ؽ��� �ε� �� �ʱ�ȭ
	auto textureComb = std::make_shared<MnMeshTextureCombination>();
	auto texture = std::make_shared<MnMeshTexture>();
	result = texture->LoadFromFile(GetD3DDevice(), L"rico_uv.png");
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_VAR_INFO(texture->LoadFromFile));
		return result;
	}

	textureComb->AddMeshTexture(texture);
	m_spSkinnedMeshRenderer->SetTextureCombination(textureComb);

	//���������ο� ���ε�
	SetRenderer(m_spSkinnedMeshRenderer);

	//ī�޶� �ʱ�ȭ
	m_camera.SetFOV(3.14f / 5.0f);
	m_camera.SetNearDistance(0.1f);
	m_camera.SetFarDistance(10000.0f);
	m_camera.SetAspectRatio((float)GetScreenWidth() / (float)GetScreenHeight());
	m_camera.SetPosition(Vector3(0, 0, 1000.0f));
	m_camera.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));

	//�޽ø� ���ν�Ǯ�� �ε�
	result = m_resourcePool.LoadModelFromFile(GetD3DDevice(), "rico_anim2.fbx", vertexType);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_VAR_INFO(TestGame::m_resourcePool.LoadModelFromFile));
		return result;
	}

	//�޽� �����͸� ���� �ν��Ͻ�ȭ
	auto mesh = std::make_shared<MnSkinnedMesh>();
	auto meshData = m_resourcePool.GetMeshData("rico_anim2.fbx", "Rico");
	if (meshData == nullptr)
	{
		MnLog::MB_IsNull(MN_VAR_INFO(meshData));
		return E_FAIL;
	}
	result = mesh->Init(GetD3DDevice(), meshData);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(mesh));
		return result;
	}
	m_lstMeshes.push_back(mesh);

	//�׽�Ʈ�� ����
	auto light = std::make_shared<MnLightSource>();
	light->SetPosition(0.0f, 0.0f, 0.0f);
	light->SetDirection(-0.5f, 0.0f, -1.0f);
	light->SetLightType(MN_LIGHT_DIRECTIONAL);
	m_lstLights.push_back(light);

	//�׽�Ʈ�� ����
	auto material = std::make_shared<MnMaterial>();
	material->ambient = Vector4(0.1f, 0.1f, 0.1f, 0.1f);
	material->diffuse = Vector4(0.55f, 0.55f, 0.55f, 1.0f);
	material->specular = Vector4(0.7f, 0.7f, 0.7f, 1.0f);
	material->specularPower = 32.0f;
	m_lstMaterials.push_back(material);

	//�׽�Ʈ�� �ִϸ��̼�
	auto testAnim = m_resourcePool.GetBoneAnimation("rico_anim2.fbx", 0);

	//�׽�Ʈ�� �ִϸ��̼� �����
	result = m_boneAnimTracker.Init(mesh->GetSkeleton(), testAnim);
	if (FAILED(result))
	{
		//error msg
		return result;
	}

	//Ÿ�̸� ��ŸƮ
	m_timer.Start();

	return S_OK;
}
bool TestGame::OnUpdate()
{
	ClearBackBuffer();

	MnTime elapsedTime = m_timer.GetElapsedTime();
	
	m_boneAnimTracker.UpdateAnimation(elapsedTime.GenuineTime());

	static float rad = 0.0f;
	rad += 0.01f;

	//matWorld = mesh->GetTransform();
	Matrix matWorld = Matrix::Identity;
	matWorld = matWorld * Matrix::CreateRotationY(rad);
	matWorld = matWorld * Matrix::CreateTranslation(0.0f, -200.0f, 0.0f);

	m_spSkinnedMeshRenderer->SetViewProjectionBuffer(GetD3DDeviceContext(), m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	//�Ʒ� �μ����� ���� �޽ø� ���� ������Ʈ Ŭ������ ������ �־�� ��.
	m_spSkinnedMeshRenderer->SetWorldBuffer(GetD3DDeviceContext(), matWorld);
	m_spSkinnedMeshRenderer->SetLightBuffer(GetD3DDeviceContext(), m_lstLights[0]);
	m_spSkinnedMeshRenderer->SetMaterial(GetD3DDeviceContext(), m_lstMaterials[0]);
	m_spSkinnedMeshRenderer->SetBonePalette(GetD3DDeviceContext(), dynamic_cast<MnSkinnedMesh*>(m_lstMeshes[0].get())->GetSkeleton());

	RenderMesh(m_spSkinnedMeshRenderer, m_lstMeshes[0]);

	SwapBuffers();
	return true;
}