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
	//스킨드 메시용 버텍스타입
	auto vertexType = std::make_shared<MnSkinnedMeshVertexType>();

	//렌더러 초기화
	m_spSkinnedMeshRenderer = std::make_shared<MnSkinnedMeshRenderer>();
	HRESULT result = m_spSkinnedMeshRenderer->Init(GetD3DDevice(), vertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(TestGame::m_spSkinnedMeshRenderer));
		return result;
	}

	//셰이더패스 초기화
	auto shaderPath = std::make_shared<SkinnedMeshShaderPath>();
	result = shaderPath->Init(GetD3DDevice(), vertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(shaderPath));
		return result;
	}
	m_spSkinnedMeshRenderer->AddShaderPathInstance(shaderPath);

	//텍스쳐 로딩 및 초기화
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

	//파이프라인에 바인딩
	SetRenderer(m_spSkinnedMeshRenderer);

	//카메라 초기화
	m_camera.SetFOV(3.14f / 5.0f);
	m_camera.SetNearDistance(0.1f);
	m_camera.SetFarDistance(10000.0f);
	m_camera.SetAspectRatio((float)GetScreenWidth() / (float)GetScreenHeight());
	m_camera.SetPosition(Vector3(0, 0, 1000.0f));
	m_camera.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));

	//메시를 리로스풀로 로딩
	result = m_resourcePool.LoadModelFromFile(GetD3DDevice(), "rico_anim2.fbx", vertexType);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_VAR_INFO(TestGame::m_resourcePool.LoadModelFromFile));
		return result;
	}

	//메시 데이터를 얻어와 인스턴스화
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

	//테스트용 광원
	auto light = std::make_shared<MnLightSource>();
	light->SetPosition(0.0f, 0.0f, 0.0f);
	light->SetDirection(-0.5f, 0.0f, -1.0f);
	light->SetLightType(MN_LIGHT_DIRECTIONAL);
	m_lstLights.push_back(light);

	//테스트용 재질
	auto material = std::make_shared<MnMaterial>();
	material->ambient = Vector4(0.1f, 0.1f, 0.1f, 0.1f);
	material->diffuse = Vector4(0.55f, 0.55f, 0.55f, 1.0f);
	material->specular = Vector4(0.7f, 0.7f, 0.7f, 1.0f);
	material->specularPower = 32.0f;
	m_lstMaterials.push_back(material);

	//테스트용 애니메이션
	auto testAnim = m_resourcePool.GetBoneAnimation("rico_anim2.fbx", 0);

	//테스트용 애니메이션 재생기
	result = m_boneAnimTracker.Init(mesh->GetSkeleton(), testAnim);
	if (FAILED(result))
	{
		//error msg
		return result;
	}

	//타이머 스타트
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
	//아래 인수들은 전부 메시를 가진 오브젝트 클래스가 가지고 있어야 함.
	m_spSkinnedMeshRenderer->SetWorldBuffer(GetD3DDeviceContext(), matWorld);
	m_spSkinnedMeshRenderer->SetLightBuffer(GetD3DDeviceContext(), m_lstLights[0]);
	m_spSkinnedMeshRenderer->SetMaterial(GetD3DDeviceContext(), m_lstMaterials[0]);
	m_spSkinnedMeshRenderer->SetBonePalette(GetD3DDeviceContext(), dynamic_cast<MnSkinnedMesh*>(m_lstMeshes[0].get())->GetSkeleton());

	RenderMesh(m_spSkinnedMeshRenderer, m_lstMeshes[0]);

	SwapBuffers();
	return true;
}