#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include "../Core\MnGpuBuffer.h"
#include "../Core\MnVertexShader.h"
#include "../Core\MnPixelShader.h"
#include "../Core\MnInputLayout.h"
#include "../Core\MnCustomVertexType.h"
#include "../Core\MnConstantBufferType.h"
#include "../Core\MnConstantBuffer.h"

namespace MNL
{
	/*
	It can use AddConstantBuffer and GetConstantBuffer to manage constant buffers dynamically with unique ID (index).
	Or just fixed implementating particular constant buffers after inheritance.
	All up to users.
	*/
	/*
	This class is used as interface. It need to inherit to specify.
	How to design constant buffers, up to the user
	*/
	class MnShaderPath
	{
	public:
		MnShaderPath();
		~MnShaderPath();

		/*
		Parameters are pointers for supporting inherited shaders and vertex types
		*/
		//initializing function may not necessary. just replace it with Setter functions
		//virtual HRESULT Init(const CPD3DDevice& cpDevice,const std::shared_ptr<MnVertexShader> spVertexShader, const std::shared_ptr<MnPixelShader> spPixelShader);
		
	protected:
		void SetVertexShader(const std::shared_ptr<MnVertexShader>& spVertexShader);
		void SetPixelShader(const std::shared_ptr<MnPixelShader>& spPixelShader);
		void SetInputLayout(const std::shared_ptr<MnInputLayout>& spInputLayout);
		const std::shared_ptr<MnVertexShader> GetMnVertexShader() const;

	public:
		const CPD3DVertexShader GetVertexShader() const;
		const CPD3DPixelShader GetPixelShader() const;
		const CPD3DInputLayout GetInputLayout() const;
		
	private:
		std::shared_ptr<MnVertexShader> m_spVertexShader;
		std::shared_ptr<MnPixelShader> m_spPixelShader;
		std::shared_ptr<MnInputLayout> m_spInputLayout;
	};

}