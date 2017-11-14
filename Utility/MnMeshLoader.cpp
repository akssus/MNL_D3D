#include "MnMeshLoader.h"
#include "Core/MnLog.h"
#include <algorithm>
#include <unordered_map>
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

	std::shared_ptr<MnMeshData> meshData = std::make_shared<MnMeshData>();

	const aiNode* currentNode = scene->mRootNode;

	std::shared_ptr<MnSkeleton> spSkeleton;
	bool modelHasBones = false;
	const aiNode* rootBoneNode = _FindRootBoneNode(scene);
	if (rootBoneNode != nullptr)
	{
		modelHasBones = true;
		_SkeletonBoneReferenceTable skeletonTable;
		HRESULT result = _EstablishSkeletonTable(skeletonTable, rootBoneNode);
		if (FAILED(result))
		{
			MnLog::MB_Failed(MN_FUNC_INFO(EstablishSkeletonData));
			return result;
		}
		spSkeleton = _CreateSkeleton(skeletonTable, scene);

		meshData->SetSkeleton(spSkeleton);
	}

	modelPackageOut.m_spMeshData = meshData;

	HRESULT result = _ReadMeshes(cpDevice, scene, currentNode, 0, meshData, vertexType);
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


	return S_OK;
}


const aiNode* MnMeshLoader::_FindAncestor(const aiScene* scene, const aiNode* currentNode)
{
	if ((currentNode == scene->mRootNode) || (currentNode->mParent == scene->mRootNode))
	{
		return currentNode;
	}
	return _FindAncestor(scene, currentNode->mParent);
}


/**
@return 루트본노드가 없을 경우 nullptr 반환
*/
const aiNode* MnMeshLoader::_FindRootBoneNode(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* pMesh = scene->mMeshes[i];
		if (pMesh->HasBones())
		{
			aiBone* pBone = pMesh->mBones[0];
			aiNode* pBoneNode = scene->mRootNode->FindNode(pBone->mName);
			const aiNode* pAncestor = _FindAncestor(scene, pBoneNode);
			return pAncestor;
		}
	}
	return nullptr;
}

HRESULT MnMeshLoader::_EstablishSkeletonTable(_SkeletonBoneReferenceTable& skeletonTable, const aiNode* rootBoneNode)
{
	skeletonTable.SetRootBoneName(rootBoneNode->mName.C_Str());
	_ProcessBoneNode(skeletonTable, rootBoneNode);
	return S_OK;
}

void MnMeshLoader::_ProcessBoneNode(_SkeletonBoneReferenceTable& skeletonTable, const aiNode* boneNode)
{
	std::string boneName = boneNode->mName.C_Str();
	std::string parentName = "";
	if (boneNode->mParent != nullptr)
	{
		parentName = boneNode->mParent->mName.C_Str();
	}
	skeletonTable.AddBoneName(boneName, parentName);

	for (int i = 0; i < boneNode->mNumChildren; ++i)
	{
		const aiNode* childNode = boneNode->mChildren[i];
		_ProcessBoneNode(skeletonTable, childNode);
	}
}

const aiBone* MnMeshLoader::_FindBoneByName(const std::string& targetBoneName, const aiScene* pScene)
{
	for (int i = 0; i < pScene->mNumMeshes; ++i)
	{
		aiMesh* pMesh = pScene->mMeshes[i];
		for (int boneIndex = 0; boneIndex < pMesh->mNumBones; ++boneIndex)
		{
			aiBone* pBone = pMesh->mBones[boneIndex];
			std::string boneName = pBone->mName.C_Str();
			if (boneName == targetBoneName)
			{
				return pBone;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<MnSkeleton> MnMeshLoader::_CreateSkeleton(_SkeletonBoneReferenceTable& skeletonTable, const aiScene* pScene)
{
	auto newSkeleton = std::make_shared<MnSkeleton>();
	newSkeleton->SetRootBoneName(skeletonTable.GetRootBoneName());
	
	for (int i = 0; i < skeletonTable.GetBoneCount(); ++i)
	{
		auto boneReference = skeletonTable.GetBoneReference(i);

		MnBone newBone;
		newBone.SetName(boneReference.name);
		newBone.SetParentName(boneReference.parentName);

		const aiBone* pBone = _FindBoneByName(boneReference.name, pScene);
		if (pBone == nullptr)
		{
			newBone.SetOffsetMatrix(Matrix::Identity);
			newBone.SetTransform(Matrix::Identity);
		}
		else
		{
			//여기서 오프셋 매트릭스는 메시 좌표계에서의 정점좌표를 본의 로컬좌표계로 바꿔주는 행렬이다.
			aiMatrix4x4 om = pBone->mOffsetMatrix;
			om.Transpose();
			newBone.SetOffsetMatrix(*(Matrix*)(&om));

			//오프셋 매트릭스의 역으로 초기화 하는 이유는 AddBone시 글로벌->본 좌표계 변환 행렬이 OffsetMatrix * Transform 인데 
			//오프셋 매트릭스의 역으로 할 경우 Identity가 되어서 원래 메시 좌표가 되기 때문
			aiMatrix4x4 initTransform = pBone->mOffsetMatrix;
			initTransform.Inverse().Transpose();
			newBone.SetTransform(*(Matrix*)(&initTransform));
		}

		newSkeleton->AddBone(newBone);
	}

	return newSkeleton;
}

HRESULT MnMeshLoader::_ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, std::shared_ptr<MnMeshData>& spMeshData, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	//ONE NODE ONE MESH
	std::shared_ptr<MnSubMeshData> subMeshData = nullptr;

	//get current Mesh data's index to set as parent index
	UINT currentMeshIndex = spMeshData->GetNumSubMeshes();

	//read only if node has meshes
	if (node->mNumMeshes != 0)
	{
		subMeshData = _ReadSingleMesh(cpDevice, scene, node, vertexType, spMeshData->GetSkeleton());
	}
	//add to package
	if (subMeshData != nullptr)
	{
		//root mesh's parent index is nullptr
		if (spMeshData->GetNumSubMeshes() > 0)
		{
			subMeshData->SetParentIndex(parentIndex);
		}
		//add to package
		spMeshData->AddSubMesh(subMeshData);
	}

	//recursively read mesh data;
	for (UINT i = 0; i < node->mNumChildren; ++i)
	{
		HRESULT result = _ReadMeshes(cpDevice, scene, node->mChildren[i], currentMeshIndex, spMeshData, vertexType);
		if (FAILED(result))
		{
			//error log
			return E_FAIL;
		}
	}
	return S_OK;
}
std::shared_ptr<MnSubMeshData> MnMeshLoader::_ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType,  std::shared_ptr<MnSkeleton>& spSkeleton)
{
	//ONE NODE ONE MESH
	std::shared_ptr<MnSubMeshData> subMeshData = std::make_shared<MnSubMeshData>();

	subMeshData->SetName(node->mName.C_Str());

	aiMatrix4x4 transform = node->mTransformation;
	subMeshData->SetTransform(DirectX::SimpleMath::Matrix((float*)&(transform.Transpose())));

	UINT totalVertexCount = _GetNodesTotalVertexCount(scene, node);
	UINT totalIndexCount = _GetNodesTotalIndexCount(scene, node);

	std::vector<_BoneData> boneData;
	_ReadBoneData(scene, node, vertexType, totalVertexCount, boneData, spSkeleton );

	std::vector<float> vertexArray;
	_ReadMeshVertices(scene, node, vertexType, totalVertexCount, vertexArray, boneData);

	std::vector<UINT> indexArray;
	_ReadMeshIndices(scene, node, subMeshData, totalIndexCount, indexArray);

	//init vertex and index buffer
	_InitBuffers(cpDevice, subMeshData, vertexType, vertexArray, totalVertexCount, indexArray, totalIndexCount);

	return subMeshData;
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


void MnMeshLoader::_ReadBoneData(const aiScene* scene, const aiNode* node, std::shared_ptr<MnCustomVertexType> vertexType, UINT numVertices, std::vector<_BoneData>& boneData, std::shared_ptr<MnSkeleton>& spSkeleton)
{
	//2017-11-13 수정필요
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
					
					std::string boneName = currentBone->mName.C_Str();
					UINT boneIndex = spSkeleton->GetBoneIndexByName(boneName);
					boneData[vertexIndex].boneIndex[boneCount] = static_cast<float>(boneIndex);
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
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneIndex[0];
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneIndex[1];
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneIndex[2];
					vertexArray[vertexOffset + currentOffset++] = boneData[j].boneIndex[3];
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
void MnMeshLoader::_ReadMeshIndices(const aiScene* scene, const aiNode* node, std::shared_ptr<MnSubMeshData>& meshData, UINT numIndices, std::vector<UINT>& indexArray)
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
		MnSubMeshFragment submeshFragment = _CreateSubMeshFragment(mesh, indexBase);
		//update base offset of submesh indices
		indexBase += submeshFragment.indexCount;
		//add to mesh data
		meshData->AddSubMeshFragment(submeshFragment);
	}
}
MnSubMeshFragment MnMeshLoader::_CreateSubMeshFragment(const aiMesh* mesh, UINT indexBase)
{
	MnSubMeshFragment submesh;
	//set submesh name and offset
	submesh.subMeshName = mesh->mName.C_Str();
	submesh.indexOffset = indexBase;
	int numFaces = mesh->mNumFaces;
	submesh.indexCount = numFaces * 3;

	return submesh;
}

HRESULT MnMeshLoader::_InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnSubMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray, UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount)
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