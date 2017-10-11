/**
@class MnGameObjectComponent
@brief �޽� �����͸� ���ϴ� ���� ������Ʈ ������Ʈ Ŭ����
@author Akssus
@section ����
MnMesh �� �̸��� ��ġ���� ������Ʈ ������ ���Ǹ� ���� Mesh�� �̸��� ���. \n
*/

#pragma once
#include "MnGameObjectComponent.h"
#include "Render/MnMesh.h"
#include "Render/MnMeshData.h"
#include "Render/MnSkinnedMesh.h"
#include <memory>


namespace MNL
{
	class Mesh : public MnGameObjectComponent
	{
	public:
		Mesh();
		~Mesh();

		void SetMesh(const std::shared_ptr<MnMeshData>& meshData);

		/**
		@return �޽ð� ���õ��� �ʾ��� ��� nullptr ��ȯ
		*/
		const std::shared_ptr<MnMesh> GetMesh() const;

		/**
		@brief ���̷��� �����͸� ��ȯ�Ѵ�
		@return ���̷����� �������� �ʴ� ��� nullptr �� ��ȯ�Ѵ�
		*/
		const std::shared_ptr<MnSkeleton> GetSkeleton() const;

	private:
		std::shared_ptr<MnMesh> m_spMesh;
	};
}
