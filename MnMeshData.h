#pragma once
#include <vector>
#include <string>
#include "MnGenericVertexStruct.h"
namespace MNL
{
	/*
	The indexOffset is base offset from the vertex array
	*/
	struct MnSubMeshData
	{
		std::string subMeshName;
		std::vector<UINT> lstIndices;
		UINT indexOffset;
		std::string materialName;
	};
	/*
	A mesh data doesn't contain indices, only vertices. 
	Each sub mesh contains index references the vertex array in mesh data.
	*/
	class MnMeshData
	{
	public:
		MnMeshData();
		~MnMeshData();

		void AddVertex(const MnGenericVertexStruct& vertex);
		void AddSubMesh(const MnSubMeshData& submesh);

		void SetParent(const MnMeshData* pParent);
		void SetName(const std::string& name);

		MnMeshData* GetParent();
		bool HasBone() const;
		void SetName(const std::string& name);
		const std::string& GetName() const;
		UINT GetNumSubMeshes() const;
		const MnSubMeshData& GetSubMesh(UINT index) const;

	private:
		MnMeshData* m_pParent;
		bool m_hasBone;
		std::string m_meshName;
		std::vector<MnGenericVertexStruct> m_lstVertices;
		std::vector<MnSubMeshData> m_lstSubMeshes;
		//material
	};
}