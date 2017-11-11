#include "MnMeshLoader.h"
#include "Core/MnLog.h"
#include <algorithm>
#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"
#include "fbxsdk.h"


using namespace MNL;
using namespace DirectX::SimpleMath;

MnMeshLoader::MnMeshLoader()
{
}


MnMeshLoader::~MnMeshLoader()
{
}


HRESULT MnMeshLoader::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& wFileName, const std::shared_ptr<MnCustomVertexType>& vertexType, ModelPackage& modelPackageOut)
{
	Assimp::Importer importer;

	std::string fileName;
	fileName.assign(wFileName.begin(), wFileName.end());
	//assimp가 wstring을 지원 안한다. 잣됬다.
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_LimitBoneWeights);
	if (!scene)
	{
		MnLog::MB_Failed(MN_FUNC_INFO(importer.ReadFile));
		return E_FAIL;
	}
	
	modelPackageOut.m_packageName = wFileName;

	//first node is root node
	const aiNode* currentNode = scene->mRootNode;
	HRESULT result = _ReadMeshes(cpDevice, scene, currentNode, 0, modelPackageOut, vertexType);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(_ReadMeshes));
		return result;
	}

	result = _ReadAnimations(scene, modelPackageOut);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(_ReadAnimations));
		return result;
	}

	/////////////////////////////////////////

	return S_OK;
}
HRESULT MnMeshLoader::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& wFileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName, std::shared_ptr<MnMeshData>& meshDataOut)
{
	Assimp::Importer importer;

	//호러블한 형변환...
	std::string fileName;
	fileName.assign(wFileName.begin(), wFileName.end());
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		//error log
		return E_FAIL;
	}

	const aiNode* findingNode = scene->mRootNode->FindNode(meshName.c_str());
	if (findingNode == nullptr)
	{
		//node not found
		return E_FAIL;
	}
	auto meshData = _ReadSingleMesh(cpDevice, scene, findingNode, vertexType);
	
	if (meshData == nullptr)
	{
		MnLog::MB_Failed(MN_FUNC_INFO(_ReadSingleMesh));
		return E_FAIL;
	}

	meshDataOut = meshData;

	return S_OK;
}

HRESULT MnMeshLoader::_ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	//ONE NODE ONE MESH
	std::shared_ptr<MnMeshData> meshData = nullptr;

	//get current Mesh data's index to set as parent index
	UINT currentMeshIndex = modelPackage.m_lstSpMeshes.size();

	//read only if node has meshes
	if (node->mNumMeshes != 0)
	{
		meshData = _ReadSingleMesh(cpDevice, scene, node, vertexType);
	}
	//add to package
	if (meshData != nullptr)
	{
		//root mesh's parent index is nullptr
		if (modelPackage.m_lstSpMeshes.size() > 0)
		{
			meshData->SetParentIndex(parentIndex);
		}
		//add to package
		modelPackage.m_lstSpMeshes.push_back(meshData);
	}

	//recursively read mesh data;
	for (UINT i = 0; i < node->mNumChildren; ++i)
	{
		HRESULT result = _ReadMeshes(cpDevice, scene, node->mChildren[i], currentMeshIndex, modelPackage, vertexType);
		if (FAILED(result))
		{
			//error log
			return E_FAIL;
		}
	}
	return S_OK;
}
std::shared_ptr<MnMeshData> MnMeshLoader::_ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	//ONE NODE ONE MESH
	std::shared_ptr<MnMeshData> meshData = nullptr;

	meshData = std::make_shared<MnMeshData>();

	meshData->SetName(node->mName.C_Str());

	aiMatrix4x4 transform = node->mTransformation;
	meshData->SetTransform(DirectX::SimpleMath::Matrix((float*)&(transform.Transpose())));

	UINT totalVertexCount = _GetNodesTotalVertexCount(scene, node);
	UINT totalIndexCount = _GetNodesTotalIndexCount(scene, node);

	auto skeleton = _CreateSkeleton(scene, node);
	meshData->SetSkeleton(skeleton);

	std::vector<_BoneData> boneData;
	_ReadBoneData(scene, node, vertexType, totalVertexCount, boneData);

	std::vector<float> vertexArray;
	_ReadMeshVertices(scene, node, vertexType, totalVertexCount, vertexArray, boneData);

	std::vector<UINT> indexArray;
	_ReadMeshIndices(scene, node, meshData, totalIndexCount, indexArray);

	//init vertex and index buffer
	_InitBuffers(cpDevice, meshData, vertexType, vertexArray, totalVertexCount, indexArray, totalIndexCount);

	return meshData;
}
UINT MnMeshLoader::_GetNodesTotalVertexCount(const aiScene* scene, const aiNode* node)
{
	UINT totalVertexCount = 0;
	for (UINT i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		UINT numVerts = scene->mMeshes[meshIndex]->mNumVertices;
		totalVertexCount += numVerts;
	}
	return totalVertexCount;
}
UINT MnMeshLoader::_GetNodesTotalIndexCount(const aiScene* scene, const aiNode* node)
{
	UINT totalIndexCount = 0;
	for (UINT i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		int numFaces = scene->mMeshes[meshIndex]->mNumFaces;
		totalIndexCount += numFaces * 3;
	}
	return totalIndexCount;
}

std::shared_ptr<MnSkeleton> MnMeshLoader::_CreateSkeleton(const aiScene* scene, const aiNode* node)
{
	auto skeleton = std::make_shared<MnSkeleton>();

	for (UINT i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		const aiMesh* mesh = scene->mMeshes[meshIndex];
		//read bones
		if (mesh->HasBones())
		{
			const aiNode* rootBoneNode = _FindRootBoneNode(scene, node, mesh->mBones[0]);
			skeleton->SetRootBoneName(rootBoneNode->mName.C_Str());

			MnBone rootBone;
			rootBone.SetName(rootBoneNode->mName.C_Str());

			aiMatrix4x4 rootBoneTransform = rootBoneNode->mTransformation;
			rootBoneTransform.Transpose();
			rootBone.SetTransform(*(Matrix*)(&rootBoneTransform));

			rootBone.SetOffsetMatrix(Matrix::Identity);
			skeleton->AddBone(rootBone);
			
			
			for (UINT j = 0; j < mesh->mNumBones; ++j)
			{
				const aiBone* currentBone = mesh->mBones[j];
				MnBone newBone;
				newBone.SetName(currentBone->mName.C_Str());

				const aiNode* boneNode = scene->mRootNode->FindNode(currentBone->mName);
				newBone.SetParentName(boneNode->mParent->mName.C_Str());

				//여기서 오프셋 매트릭스는 메시 좌표계에서의 정점좌표를 본의 로컬좌표계로 바꿔주는 행렬이다.
				aiMatrix4x4 om = currentBone->mOffsetMatrix;
				om.Transpose();
				newBone.SetOffsetMatrix(*(Matrix*)(&om));

				//오프셋 매트릭스의 역으로 초기화 하는 이유는 AddBone시 글로벌->본 좌표계 변환 행렬이 OffsetMatrix * Transform 인데 
				//오프셋 매트릭스의 역으로 할 경우 Identity가 되어서 원래 메시 좌표가 되기 때문
				aiMatrix4x4 initTransform = currentBone->mOffsetMatrix;
				initTransform.Inverse().Transpose();
				newBone.SetTransform(*(Matrix*)(&initTransform));

				skeleton->AddBone(newBone);
			}
		}
	}
	return skeleton;
}
const aiNode* MnMeshLoader::_FindRootBoneNode(const aiScene* scene, const aiNode* currentMeshNode, const aiBone* bone)
{
	auto& boneName = bone->mName;
	const aiNode* boneNode = scene->mRootNode->FindNode(boneName);
	while ((boneNode->mParent != currentMeshNode->mParent) && (boneNode->mParent != currentMeshNode) && (boneNode->mParent != scene->mRootNode))
	{
		boneNode = boneNode->mParent;
	}
	return boneNode;
}
void MnMeshLoader::_ReadBoneData(const aiScene* scene, const aiNode* node, std::shared_ptr<MnCustomVertexType> vertexType, UINT numVertices, std::vector<_BoneData>& boneData)
{
	std::vector<UINT> boneDataCounter;
	if (vertexType->GetFlags() & MN_CVF_BONE_INDEX
		&& vertexType->GetFlags() & MN_CVF_BONE_WEIGHT)
	{
		boneData.resize(numVertices);
		boneDataCounter.resize(numVertices);
		for (UINT i = 0; i < node->mNumMeshes; ++i)
		{
			UINT meshIndex = node->mMeshes[i];
			const aiMesh* mesh = scene->mMeshes[meshIndex];
			//read bones
			for (UINT j = 0; j < mesh->mNumBones; ++j)
			{
				const aiBone* currentBone = mesh->mBones[j];
				UINT numWeights = currentBone->mNumWeights;
				for (UINT weightIndex = 0; weightIndex < numWeights; weightIndex++)
				{
					aiVertexWeight& vertexWeight = currentBone->mWeights[weightIndex];
					UINT vertexIndex = vertexWeight.mVertexId;
					UINT boneCount = boneDataCounter[vertexIndex];
					float boneWeight = vertexWeight.mWeight;
					//index + 1 because index 0 is for the root bone
					boneData[vertexIndex].boneIndex[boneCount] = j + 1;
					boneData[vertexIndex].boneWeight[boneCount] = boneWeight;
					boneDataCounter[vertexIndex] += 1;
				}
			}
		}
	}
}
void MnMeshLoader::_ReadMeshVertices(const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType, UINT numVertices, std::vector<float>& vertexArray, const std::vector<_BoneData>& boneData)
{
	//prepare vertex array
	UINT vertexStride = vertexType->TotalByteSize();
	UINT numFloats = vertexStride / 4;
	vertexArray.resize(numVertices * (numFloats));
	UINT16 flags = vertexType->GetFlags();

	//read every mesh's vertices with serialization
	UINT vertexBase = 0;
	for (UINT i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		//read vertices
		UINT numVerts = mesh->mNumVertices;
		for (UINT j = 0; j < numVerts; ++j)
		{
			UINT vertexOffset = vertexBase + (j * numFloats);
			UINT currentOffset = 0;
			//read positions
			if (flags & MN_CVF_POSITION0)
			{
				vertexArray[vertexOffset + currentOffset++] = mesh->mVertices[j].x;
				vertexArray[vertexOffset + currentOffset++] = mesh->mVertices[j].y;
				vertexArray[vertexOffset + currentOffset++] = mesh->mVertices[j].z;
			}
			//read normals
			if (mesh->HasNormals())
			{
				if (flags & MN_CVF_NORMAL0)
				{
					vertexArray[vertexOffset + currentOffset++] = mesh->mNormals[j].x;
					vertexArray[vertexOffset + currentOffset++] = mesh->mNormals[j].y;
					vertexArray[vertexOffset + currentOffset++] = mesh->mNormals[j].z;
				}
			}
			else //default normal
			{
				if (flags & MN_CVF_NORMAL0)
				{
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
				}
			}

			//read texcoords
			int texCoordIndex = 0;
			if (mesh->mTextureCoords[texCoordIndex] != nullptr)
			{
				if (flags & MN_CVF_TEXCOORD0)
				{
					vertexArray[vertexOffset + currentOffset++] = mesh->mTextureCoords[texCoordIndex][j].x;
					vertexArray[vertexOffset + currentOffset++] = mesh->mTextureCoords[texCoordIndex][j].y;
				}
			}
			else //default texcoord
			{
				if (flags & MN_CVF_TEXCOORD0)
				{
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
				}
			}
			if (mesh->HasBones())
			{
				if (flags & MN_CVF_BONE_INDEX)
				{
					vertexArray[vertexOffset + currentOffset++] = (float)boneData[j].boneIndex[0];
					vertexArray[vertexOffset + currentOffset++] = (float)boneData[j].boneIndex[1];
					vertexArray[vertexOffset + currentOffset++] = (float)boneData[j].boneIndex[2];
					vertexArray[vertexOffset + currentOffset++] = (float)boneData[j].boneIndex[3];
				}
				if (flags & MN_CVF_BONE_WEIGHT)
				{
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneWeight[0];
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneWeight[1];
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneWeight[2];
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneWeight[3];
				}
			}
			else //default bone index
			{
				if (flags & MN_CVF_BONE_INDEX)
				{
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
				}
				if (flags & MN_CVF_BONE_WEIGHT)
				{
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
					vertexArray[vertexOffset + currentOffset++] = 0.0f;
				}
			}
		}
		//rebase vertex
		vertexBase += numVerts * numFloats;
	}
}
void MnMeshLoader::_ReadMeshIndices(const aiScene* scene, const aiNode* node, std::shared_ptr<MnMeshData>& meshData, UINT numIndices, std::vector<UINT>& indexArray)
{
	indexArray.resize(numIndices);

	UINT indexBase = 0;
	for (UINT i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		//read indices of all submeshes with serializing
		int numFaces = mesh->mNumFaces;
		for (int j = 0; j < numFaces; ++j)
		{
			UINT indexOffset = j * 3;
			aiFace& face = mesh->mFaces[j];
			for (UINT faceIndex = 0; faceIndex < face.mNumIndices; ++faceIndex)
			{
				indexArray[indexBase + indexOffset + faceIndex] = face.mIndices[faceIndex];
			}
		}
		//create submesh
		MnSubMesh submesh = _CreateSubMesh(mesh, indexBase);
		//update base offset of submesh indices
		indexBase += submesh.indexCount;
		//add to mesh data
		meshData->AddSubMesh(submesh);
	}
}
MnSubMesh MnMeshLoader::_CreateSubMesh(const aiMesh* mesh, UINT indexBase)
{
	MnSubMesh submesh;
	//set submesh name and offset
	submesh.subMeshName = mesh->mName.C_Str();
	submesh.indexOffset = indexBase;
	int numFaces = mesh->mNumFaces;
	submesh.indexCount = numFaces * 3;

	return submesh;
}

HRESULT MnMeshLoader::_InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray, UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount)
{
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertexArray.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indexArray.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//create buffers
	auto vertexBuffer = std::make_shared<MnVertexBuffer>();
	HRESULT result = vertexBuffer->Init(cpDevice, vertexType, vertexCount, &vertexData, false);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	auto indexBuffer = std::make_shared<MnIndexBuffer>();
	result = indexBuffer->Init(cpDevice, indexCount, &indexData);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	meshData->SetVertexBuffer(vertexBuffer);
	meshData->SetIndexBuffer(indexBuffer);

	return S_OK;
}
HRESULT MnMeshLoader::_ReadAnimations(const aiScene* scene, ModelPackage& modelPackage)
{
	if (scene->HasAnimations())
	{
		for (int i = 0; i < scene->mNumAnimations; ++i)
		{
			const aiAnimation* anim = scene->mAnimations[i];
			std::shared_ptr<MnBoneAnimation> newAnim = std::make_shared<MnBoneAnimation>();
			newAnim->SetName(anim->mName.C_Str());
			newAnim->SetTotalDuration(anim->mDuration);

			//MnBoneAnimationElement 는 하나의 본의 모든 키프레임 묶음으로 보면 됨
			for (int boneIndex = 0; boneIndex < anim->mNumChannels; ++boneIndex)
			{
				const aiNodeAnim* animNode = anim->mChannels[boneIndex];
				MnBoneAnimationElement newAnimElement;
				newAnimElement.SetAffectingBoneName(animNode->mNodeName.C_Str());
				newAnimElement.SetDuration(anim->mDuration);

				for (int keyFrameIndex = 0; keyFrameIndex < animNode->mNumPositionKeys; ++keyFrameIndex)
				{
					MnBoneAnimationChannelKey<KeyPosition> newKeyFrame;

					const aiVectorKey& keyPos = animNode->mPositionKeys[keyFrameIndex];

					newKeyFrame.keyValue = Vector3(keyPos.mValue.x, keyPos.mValue.y, keyPos.mValue.z);
					newKeyFrame.keyTime = keyPos.mTime;

					newAnimElement.AddKeyFrameT(newKeyFrame);
				}
				
				for (int keyFrameIndex = 0; keyFrameIndex < animNode->mNumRotationKeys; ++keyFrameIndex)
				{
					MnBoneAnimationChannelKey<KeyRotation> newKeyFrame;

					const aiQuatKey& keyRot = animNode->mRotationKeys[keyFrameIndex];

					newKeyFrame.keyValue = Quaternion(keyRot.mValue.x, keyRot.mValue.y, keyRot.mValue.z, keyRot.mValue.w);
					newKeyFrame.keyTime = keyRot.mTime;

					newAnimElement.AddKeyFrameQ(newKeyFrame);
				}

				for (int keyFrameIndex = 0; keyFrameIndex < animNode->mNumScalingKeys; ++keyFrameIndex)
				{
					MnBoneAnimationChannelKey<KeyScale> newKeyFrame;

					const aiVectorKey& keyScale = animNode->mScalingKeys[keyFrameIndex];

					newKeyFrame.keyValue = Vector3(keyScale.mValue.x, keyScale.mValue.y, keyScale.mValue.z);
					newKeyFrame.keyTime = keyScale.mTime;

					newAnimElement.AddKeyFrameS(newKeyFrame);
				}

				newAnim->AddElement(newAnimElement);
			}
			modelPackage.m_lstSpAnimations.push_back(newAnim);
		}
	}
	return S_OK;
}