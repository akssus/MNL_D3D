/**
@class MNL::MnResourcePool
@section 주의사항
LoadModelFromFile 을 호출할때 쓰이는 버텍스 타입은 MnMeshVertexType 혹은 MnSkinnedMeshVertexType 둘중 하나로 쓰는걸 추천한다. \n
VertexType 내 모든 플래그에 대해 대응하는게 아니기 때문임.
*/

#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

namespace MNL
{
	template <class T>
	class MnResourcePool
	{

	public:
		MnResourcePool() :
			m_resourceCount(0)
		{
			m_memoryPointers.resize(10);
			m_serializedMemory.resize(10);
		};
		~MnResourcePool() 
		{
			m_memoryPointers.clear();
			m_serializedMemory.clear();
		};

		void AddResource(const std::wstring& GUID, std::shared_ptr<T> spResource)
		{
			int index = _AllocateIndex();
			m_resourceRegister[GUID] = index;
			m_serializedMemory[index] = *spResource;
			m_memoryPointers[index] = spResource;
		}

		std::shared_ptr<T> GetResource(const std::wstring& GUID)
		{
			if (m_resourceRegister.count(GUID) == 0)
			{
				return std::shared_ptr<T>(nullptr);
			}
			int index = m_resourceRegister.at(GUID);
			return m_memoryPointers[index];
		};

	private:
		int _AllocateIndex()
		{
			if (m_resourceCount >= m_serializedMemory.size())
			{
				m_serializedMemory.resize(m_serializedMemory.size() * 2);
				m_memoryPointers.resize(m_serializedMemory.size() * 2);
			}
			return m_resourceCount++;
		}

	private:
		int m_resourceCount;
		std::unordered_map<std::wstring, int> m_resourceRegister;
		std::vector<T> m_serializedMemory;
		std::vector<std::shared_ptr<T>> m_memoryPointers;
	};

}