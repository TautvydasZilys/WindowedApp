#include "PrecompiledHeader.h"
#include "D3D11Context.h"
#include "DXGIMisc.h"
#include "Utils/Log.h"

static inline void OutputAdapterInfo(IDXGIAdapter1* adapter, D3D_FEATURE_LEVEL featureLevel);

D3D11Context::D3D11Context()
{
	CreateDevice();

	m_SupportsTearing = false;

	WRL::ComPtr<IDXGIFactory5> dxgiFactory5;
	auto hr = m_DxgiFactory.As(&dxgiFactory5);
	
	if (SUCCEEDED(hr))
	{
		BOOL supportsTearing;
		hr = dxgiFactory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &supportsTearing, sizeof(supportsTearing));
		m_SupportsTearing = SUCCEEDED(hr) && supportsTearing;
	}
}

D3D11Context::~D3D11Context()
{
}

void D3D11Context::CreateDevice()
{
	UINT dxgiFactoryCreationFlags = 0;
	UINT deviceCreationFlags = D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if _DEBUG
	dxgiFactoryCreationFlags |= DXGI_CREATE_FACTORY_DEBUG;
	deviceCreationFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	auto hr = CreateDXGIFactory2(dxgiFactoryCreationFlags, __uuidof(IDXGIFactory2), &m_DxgiFactory);
	Assert(SUCCEEDED(hr));

	WRL::ComPtr<IDXGIAdapter1> dxgiAdapter;
	hr = m_DxgiFactory->EnumAdapters1(0, &dxgiAdapter);
	Assert(SUCCEEDED(hr));

	const D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
		// Screw 9.x
	};

	D3D_FEATURE_LEVEL actualFeatureLevel;

#if _DEBUG
DoCreateDevice:
#endif
	hr = D3D11CreateDevice(dxgiAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, deviceCreationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_Device, &actualFeatureLevel, &m_DeviceContext);

#if _DEBUG
	if (FAILED(hr))
	{
		deviceCreationFlags &= ~D3D11_CREATE_DEVICE_DEBUG;
		goto DoCreateDevice;
	}
#endif

	Assert(SUCCEEDED(hr));

	OutputAdapterInfo(dxgiAdapter.Get(), actualFeatureLevel);
}

static inline void OutputAdapterInfo(IDXGIAdapter1* adapter, D3D_FEATURE_LEVEL featureLevel)
{
	WRL::ComPtr<IDXGIAdapter2> adapter2;
	DXGI_ADAPTER_DESC2 description;
	bool hasNoGranularity;

	auto hr = adapter->QueryInterface(adapter2.ReleaseAndGetAddressOf());

	if (SUCCEEDED(hr))
	{
		adapter2->GetDesc2(&description);
		hasNoGranularity = false;
	}
	else
	{
		hr = adapter->GetDesc1(reinterpret_cast<DXGI_ADAPTER_DESC1*>(&description));
		Assert(SUCCEEDED(hr));

		hasNoGranularity = true;
	}

	Log(Logging::EndLine);

	Log("GPU name: ");
	Log(description.Description);
	Log(Logging::EndLine);

	Log("Dedicated memory: ");
	Log(std::to_string(description.DedicatedVideoMemory / 1024 / 1024).c_str());
	Log(" MB");
	Log(Logging::EndLine);

	Log("Adapter flags: ");

	switch (description.Flags)
	{
	case DXGI_ADAPTER_FLAG_NONE:
		Log("None");
		break;

	case DXGI_ADAPTER_FLAG_REMOTE:
		Log("Remote");
		break;

	case DXGI_ADAPTER_FLAG_SOFTWARE:
		Log("Software");
		break;

	default:
		AssertFail();
		Log("Unknown");
		break;
	}

	Log(Logging::EndLine);


	if (!hasNoGranularity)
	{
		Log("Graphics preemption granularity: ");

		switch (description.GraphicsPreemptionGranularity)
		{
		case DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY:
			Log("DMA buffer boundary");
			break;

		case DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY:
			Log("Primitive boundary");
			break;

		case DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY:
			Log("Triangle boundary");
			break;

		case DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY:
			Log("Pixel boundary");
			break;

		case DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY:
			Log("Instruction boundary");
			break;

		default:
			AssertFail();
			Log("Unknown");
			break;
		}

		Log(Logging::EndLine);

		Log("Compute preemption granularity: ");

		switch (description.ComputePreemptionGranularity)
		{
		case DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY:
			Log("DMA buffer boundary");
			break;

		case DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY:
			Log("Dispatch boundary");
			break;

		case DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY:
			Log("Thread group boundary");
			break;

		case DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY:
			Log("Thread boundary");
			break;

		case DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY:
			Log("Instruction boundary");
			break;

		default:
			AssertFail();
			Log("Unknown");
			break;
		}

		Log(Logging::EndLine);
	}
	else
	{
		Log("Graphics preemption granularity: Unknown");
		Log(Logging::EndLine);

		Log("Compute preemption granularity: Unknown");
		Log(Logging::EndLine);
	}

	Log("D3D11 Feature level: ");

	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_9_1:
		Log("9.1");
		break;

	case D3D_FEATURE_LEVEL_9_2:
		Log("9.2");
		break;

	case D3D_FEATURE_LEVEL_9_3:
		Log("9.3");
		break;

	case D3D_FEATURE_LEVEL_10_0:
		Log("10.0");
		break;

	case D3D_FEATURE_LEVEL_10_1:
		Log("10.1");
		break;

	case D3D_FEATURE_LEVEL_11_0:
		Log("11.0");
		break;
	
	case D3D_FEATURE_LEVEL_11_1:
		Log("11.1");
		break;

	default:
		Log("Unknown");
		break;
	}

	Log(Logging::EndLine);
	Log(Logging::EndLine);
}

D3D11BackBuffer* D3D11Context::CreateBackBuffer(void* windowHandle, uint32_t width, uint32_t height) const
{
	const DXGI_FORMAT kBackBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	DXGI_SWAP_CHAIN_DESC1 swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));

	swapChainDescription.Width = width;
	swapChainDescription.Height = height;
	swapChainDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDescription.Stereo = FALSE;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount = 2;
	swapChainDescription.Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
	
	if (m_SupportsTearing)
		swapChainDescription.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	WRL::ComPtr<IDXGISwapChain1> swapChain1;	
	auto hr = m_DxgiFactory->CreateSwapChainForHwnd(m_Device.Get(), static_cast<HWND>(windowHandle), &swapChainDescription, nullptr, nullptr, &swapChain1);
	Assert(SUCCEEDED(hr));

	WRL::ComPtr<IDXGISwapChain2> swapChain2;
	hr = swapChain1.As(&swapChain2);
	Assert(SUCCEEDED(hr));

	return new D3D11BackBuffer(m_Device.Get(), std::move(swapChain2), kBackBufferFormat, m_SupportsTearing);
}

VertexShader* D3D11Context::CreateVertexShader(const uint8_t* byteCode, size_t length) const
{
	ID3D11VertexShader* shader;
	auto hr = m_Device->CreateVertexShader(byteCode, length, nullptr, &shader);
	Assert(SUCCEEDED(hr));
	return shader;
}

PixelShader* D3D11Context::CreatePixelShader(const uint8_t* byteCode, size_t length) const
{
	ID3D11PixelShader* shader;
	auto hr = m_Device->CreatePixelShader(byteCode, length, nullptr, &shader);
	Assert(SUCCEEDED(hr));
	return shader;
}

void D3D11Context::SetActiveVertexShader(VertexShader* vertexShader) const
{
	m_DeviceContext->VSSetShader(static_cast<ID3D11VertexShader*>(vertexShader), nullptr, 0);
}

void D3D11Context::SetActivePixelShader(PixelShader* pixelShader) const
{
	m_DeviceContext->PSSetShader(static_cast<ID3D11PixelShader*>(pixelShader), nullptr, 0);
}

void D3D11Context::BindTextures(ShaderStage shaderStage, const Texture* const* textures, uint32_t startingSlot, uint32_t textureCount) const
{
	auto views = static_cast<ID3D11ShaderResourceView**>(alloca(sizeof(ID3D11ShaderResourceView*) * textureCount));

	for (uint32_t i = 0; i < textureCount; i++)
		views[i] = static_cast<const D3D11Texture*>(textures[i])->GetShaderResourceView();

	switch (shaderStage)
	{
	case ShaderStage::Vertex:
		m_DeviceContext->VSSetShaderResources(startingSlot, textureCount, views);
		break;

	case ShaderStage::Geometry:
		m_DeviceContext->GSSetShaderResources(startingSlot, textureCount, views);
		break;

	case ShaderStage::Pixel:
		m_DeviceContext->PSSetShaderResources(startingSlot, textureCount, views);
		break;

	default:
		AssertFail();
		break;
	}
}

void D3D11Context::ClearRenderTarget(const RenderTarget* renderTarget, float r, float g, float b) const
{
	auto d3d11RenderTarget = static_cast<const D3D11RenderTarget*>(renderTarget);

	float clearColor[] = { r, g, b, 0.0f };
	m_DeviceContext->ClearRenderTargetView(d3d11RenderTarget->GetRenderTargetView(), clearColor);

	if (d3d11RenderTarget->GetShaderResourceView() != nullptr)
		m_DeviceContext->ClearDepthStencilView(d3d11RenderTarget->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3D11Context::SetRenderTarget(const RenderTarget* renderTarget) const
{
	(void)renderTarget;
	AssertFail();
}
