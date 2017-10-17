#include "TestGame.h"
#include "SkinnedMeshShaderPath.h"
#include "Core/MnLog.h"
#include "GameWorldComponents.h"
#include "GameObjectComponents.h"
#include "Framework\ForwardShader.h"

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
	HRESULT result = E_FAIL;

	m_gameWorld.SetScreenSize(GetRenderWindow().GetWindowWidth(), GetRenderWindow().GetWindowHeight());
	m_gameWorld.AddComponent(std::make_shared<CameraList>());
	m_gameWorld.AddComponent(std::make_shared<ShaderList>());
	m_gameWorld.AddComponent(std::make_shared<LightList>());
	m_gameWorld.AddComponent(std::make_shared<Renderer>());

	//���� : �� �ε��� ���ؽ� Ÿ���� MnSkinnedMeshVertexType ���� �����ϴ� ���� ����.
	auto vertexType = std::make_shared<MnSkinnedMeshVertexType>();

	//�޽ø� ���ν�Ǯ�� �ε�
	result = m_resourcePool.LoadModelFromFile(renderAPI.GetD3DDevice(), "rico_anim3.fbx", vertexType);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(m_resourcePool.LoadModelFromFile));
		return result;
	}

	//�޽� �����͸� ���� �ν��Ͻ�ȭ
	auto mesh = std::make_shared<MnSkinnedMesh>();
	auto meshData = m_resourcePool.GetMeshData("rico_anim3.fbx", "Rico");
	if (meshData == nullptr)
	{
		MnLog::MB_IsNull(MN_VAR_INFO(meshData));
		return E_FAIL;
	}
	

	//�׽�Ʈ�� ���� ������Ʈ ����. ���丮 ���� �ʿ�
	auto gameObject = std::make_shared<MnGameObject>();

	gameObject->AddComponent(std::make_shared<Transform>());
	gameObject->AddComponent(std::make_shared<Mesh>());
	gameObject->AddComponent(std::make_shared<MeshAnimationController>());
	gameObject->AddComponent(std::make_shared<Texture>());
	gameObject->AddComponent(std::make_shared<Material>());

	gameObject->GetComponent<Mesh>()->SetMesh(meshData);

	auto testTexture = std::make_shared<MnMeshTexture>();
	testTexture->LoadFromFile(renderAPI.GetD3DDevice(), L"rico_uv.png");
	gameObject->GetComponent<Texture>()->SetTexture(testTexture, MN_TEXTURE_DIFFUSE);

	auto testMaterial = std::make_shared<MnMaterial>();
	testMaterial->ambient = Vector4(0.1f, 0.1f, 0.1f, 0.1f);
	testMaterial->diffuse = Vector4(0.55f, 0.55f, 0.55f, 1.0f);
	testMaterial->specular = Vector4(0.7f, 0.7f, 0.7f, 1.0f);
	testMaterial->specularPower = 32.0f;
	gameObject->GetComponent<Material>()->SetMaterial(testMaterial);
	
	//�׽�Ʈ�� �ִϸ��̼�
	auto testAnim = m_resourcePool.GetBoneAnimation("rico_anim3.fbx", 0);
	gameObject->GetComponent<MeshAnimationController>()->AddAnimation("walk", testAnim);
	gameObject->GetComponent<MeshAnimationController>()->SetAnimation("walk");
	gameObject->GetComponent<MeshAnimationController>()->SetLoop(true);

	
	m_gameWorld.AddGameObject(gameObject);


	auto light = std::make_shared<MnLightSource>();
	light->SetPosition(0.0f, 0.0f, 0.0f);
	light->SetDirection(-0.5f, 0.0f, -1.0f);
	light->SetLightType(MN_LIGHT_DIRECTIONAL);
	m_gameWorld.GetComponent<LightList>()->AddLight(light);


	auto shader = std::make_shared<ForwardShader>();
	m_gameWorld.GetComponent<ShaderList>()->AddShader(shader);

	auto camera = std::make_shared<MnCamera>();
	camera->SetFOV(3.14f / 5.0f);
	camera->SetNearDistance(0.1f);
	camera->SetFarDistance(10000.0f);
	camera->SetAspectRatio(1024.0f / 768.0f);
	//camera.SetPosition(Vector3(0, 0, -1000.0f));
	camera->SetPosition(Vector3(0.0f, 0.0f, 1000.0f));
	camera->LookAt(Vector3(0, 500.0f, 0), Vector3(0, 1, 0));

	m_gameWorld.GetComponent<CameraList>()->AddCamera(camera);
	m_gameWorld.SetMainCamera(camera);


	return S_OK;
}
bool TestGame::OnUpdate()
{
	ClearBackBuffer();

	m_gameWorld.Update();
	
	auto renderer = m_gameWorld.GetComponent<Renderer>();
	renderer->Render(GetRenderWindow());

	SwapBuffers();
	return true;
}