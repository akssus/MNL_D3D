#include "MnResourcePool.h"
#include "Core/MnLog.h"
#include <algorithm>
#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnResourcePool::MnResourcePool()
{
	m_modelPackages["default"] = _ModelPackage();
}

MnResourcePool::~MnResourcePool()
{
}

HRESULT MnResourcePool::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_LimitBoneWeights);
	if (!scene)
	{
		MnLog::MB_Failed(MN_FUNC_INFO(importer.ReadFile));
		return E_FAIL;
	}
	_ModelPackage package;
	package.m_packageName = fileName;

	//first node is root node
	const aiNode* currentNode = scene->mRootNode;
	HRESULT result = _ReadMeshes(cpDevice, scene, currentNode, 0, package, vertexType);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(_ReadMeshes));
		return result;
	}

	result = _ReadAnimations(scene, package);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(_ReadAnimations));
		return result;
	}

	//mapping to table
	m_modelPackages[fileName] = package;

	return S_OK;
}
HRESULT MnResourcePool::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName)
{
	if (m_modelPackages.count(fileName) == 0)
	{
		m_modelPackages[fileName] = _ModelPackage();
	}
	Assimp::Importer importer;
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
	m_modelPackages[fileName].m_lstSpMeshes.push_back(meshData);

	return S_OK;
}

HRESULT MnResourcePool::_LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName)
{
	return S_OK;
}
HRESULT MnResourcePool::_ReadFromAssimpScene(const aiScene* scene)
{
	return S_OK;
}

HRESULT MnResourcePool::_ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, _ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType)
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
std::shared_ptr<MnMeshData> MnResourcePool::_ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType)
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
UINT MnResourcePool::_GetNodesTotalVertexCount(const aiScene* scene, const aiNode* node)
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
UINT MnResourcePool::_GetNodesTotalIndexCount(const aiScene* scene, const aiNode* node)
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

std::shared_ptr<MnSkeleton> MnResourcePool::_CreateSkeleton(const aiScene* scene, const aiNode* node)
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

				aiMatrix4x4 om = currentBone->mOffsetMatrix;
				om.Transpose();
				newBone.SetOffsetMatrix(*(Matrix*)(&om));

				aiMatrix4x4 initTransform = currentBone->mOffsetMatrix;
				initTransform.Inverse().Transpose();
				newBone.SetTransform(*(Matrix*)(&initTransform));

				skeleton->AddBone(newBone);
			}
		}
	}
	return skeleton;
}
const aiNode* MnResourcePool::_FindRootBoneNode(const aiScene* scene, const aiNode* currentMeshNode, const aiBone* bone)
{
	auto& boneName = bone->mName;
	const aiNode* boneNode = scene->mRootNode->FindNode(boneName);
	while ((boneNode->mParent != currentMeshNode->mParent) && (boneNode->mParent != currentMeshNode) && (boneNode->mParent != scene->mRootNode))
	{
		boneNode = boneNode->mParent;
	}
	return boneNode;
}
void MnResourcePool::_ReadBoneData(const aiScene* scene, const aiNode* node, std::shared_ptr<MnCustomVertexType> vertexType, UINT numVertices, std::vector<_BoneData>& boneData)
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
					boneData[vertexIndex].boneIndex[boneCount] = j+1;
					boneData[vertexIndex].boneWeight[boneCount] = boneWeight;
					boneDataCounter[vertexIndex] += 1;
				}
			}
		}
	}
}
void MnResourcePool::_ReadMeshVertices(const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType, UINT numVertices, std::vector<float>& vertexArray, const std::vector<_BoneData>& boneData)
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
void MnResourcePool::_ReadMeshIndices(const aiScene* scene,const aiNode* node, std::shared_ptr<MnMeshData>& meshData, UINT numIndices, std::vector<UINT>& indexArray)
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
MnSubMesh MnResourcePool::_CreateSubMesh(const aiMesh* mesh, UINT indexBase)
{
	MnSubMesh submesh;
	//set submesh name and offset
	submesh.subMeshName = mesh->mName.C_Str();
	submesh.indexOffset = indexBase;
	int numFaces = mesh->mNumFaces;
	submesh.indexCount = numFaces * 3;

	return submesh;
}

HRESULT MnResourcePool::_InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray,UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount )
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
HRESULT MnResourcePool::_ReadAnimations(const aiScene* scene, _ModelPackage& modelPackage)
{
	if (scene->HasAnimations())
	{
		for (int i = 0; i < scene->mNumAnimations; ++i)
		{
			const aiAnimation* anim = scene->mAnimations[i];
			MnBoneAnimation newAnim;
			newAnim.SetName(anim->mName.C_Str());
			newAnim.SetTotalDuration(anim->mDuration);

			for (int boneIndex = 0; boneIndex < anim->mNumChannels; ++boneIndex)
			{
				const aiNodeAnim* animNode = anim->mChannels[boneIndex];
				MnBoneAnimationElement newAnimElement;
				newAnimElement.SetAffectingBoneName(animNode->mNodeName.C_Str());
				newAnimElement.SetDuration(anim->mDuration);

				for (int keyFrameIndex = 0; keyFrameIndex < animNode->mNumPositionKeys; ++keyFrameIndex)
				{
					MnBoneAnimationKeyFrame newKeyFrame;

					const aiVectorKey& keyPos = animNode->mPositionKeys[keyFrameIndex];
					const aiQuatKey& keyRot = animNode->mRotationKeys[keyFrameIndex];
					const aiVectorKey& keyScale = animNode->mScalingKeys[keyFrameIndex];

					newKeyFrame.keyPosition = Vector3(keyPos.mValue.x, keyPos.mValue.y, keyPos.mValue.z);
					newKeyFrame.keyRotation = Quaternion(keyRot.mValue.x, keyRot.mValue.y, keyRot.mValue.z, keyRot.mValue.w);
					newKeyFrame.keyScale = Vector3(keyScale.mValue.x, keyScale.mValue.y, keyScale.mValue.z);

					newKeyFrame.keyTime = keyPos.mTime;

					newAnimElement.AddKeyFrame(newKeyFrame);
				}
				newAnim.AddElement(newAnimElement);
			}
			modelPackage.m_lstAnimations.push_back(newAnim);
		}
	}
	return S_OK;
}

std::shared_ptr<MnMeshData> MnResourcePool::GetMeshData(const std::string& modelPackageName, const std::string& meshName) const
{
	if (m_modelPackages.count(modelPackageName) == 0)
	{
		//model package not found
		return nullptr;
	}
	auto& lstMeshes = m_modelPackages.at(modelPackageName).m_lstSpMeshes;
	//find matched mesh data
	auto it = std::find_if(lstMeshes.begin(),lstMeshes.end(),
		[&](const std::shared_ptr<MnMeshData>& meshData)
	{
		if (meshData->GetName() == meshName) return true;
		return false;
	});
	if (it == lstMeshes.end())
	{
		//find failed
		return nullptr;
	}
	return *it;
}

MnBoneAnimation MnResourcePool::GetBoneAnimation(const std::string& modelPackageName, const std::string& animationName) const
{
	if (m_modelPackages.count(modelPackageName) == 0)
	{
		//model package not found
		return MnBoneAnimation();
	}
	auto& lstAnimations = m_modelPackages.at(modelPackageName).m_lstAnimations;
	auto it = std::find_if(lstAnimations.begin(), lstAnimations.end(),
		[&](const MnBoneAnimation& anim)
	{
		if (anim.GetName() == animationName) return true;
		return false;
	});
	if (it == lstAnimations.end())
	{
		return MnBoneAnimation();
	}
	return *it;
}

MnBoneAnimation MnResourcePool::GetBoneAnimation(const std::string& modelPackageName, UINT index) const
{
	if (m_modelPackages.count(modelPackageName) == 0)
	{
		//model package not found
		return MnBoneAnimation();
	}
	return m_modelPackages.at(modelPackageName).m_lstAnimations[index];
}