#pragma once
#include <vector>
#include <string>
#include <memory>
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

		void SetParentIndex(UINT index);
		void SetName(const std::string& name);

		bool					HasBone() const;
		const MnGenericVertexStruct&  GetVertex(UINT index) const;
		UINT					GetNumVertices() const;
		std::shared_ptr<UINT>	GetParentIndex() const;
		const std::string&		GetName() const;
		UINT					GetNumSubMeshes() const;
		const MnSubMeshData&	GetSubMesh(UINT index) const;

	private:
		std::shared_ptr<UINT> m_spParentIndex;
		bool m_hasBone;
		std::string m_meshName;
		std::vector<MnGenericVertexStruct> m_lstVertices;
		std::vector<MnSubMeshData> m_lstSubMeshes;
		//material
	};
}