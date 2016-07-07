#pragma once

#ifndef __dxgi1_4_h__

MIDL_INTERFACE("1bc6ea02-ef36-464f-bf0c-21ca39e5168a")
IDXGIFactory4 : public IDXGIFactory3
{
public:
	virtual HRESULT STDMETHODCALLTYPE EnumAdapterByLuid(
		/* [annotation] */
		_In_  LUID AdapterLuid,
		/* [annotation] */
		_In_  REFIID riid,
		/* [annotation] */
		_COM_Outptr_  void **ppvAdapter) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumWarpAdapter(
		/* [annotation] */
		_In_  REFIID riid,
		/* [annotation] */
		_COM_Outptr_  void **ppvAdapter) = 0;

};

#endif

#ifndef __dxgi1_5_h__

typedef enum DXGI_FEATURE
{
	DXGI_FEATURE_PRESENT_ALLOW_TEARING = 0
} DXGI_FEATURE;

MIDL_INTERFACE("7632e1f5-ee65-4dca-87fd-84cd75f8838d")
IDXGIFactory5 : public IDXGIFactory4
{
public:
	virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(
		DXGI_FEATURE Feature,
		_Inout_updates_bytes_(FeatureSupportDataSize) void *pFeatureSupportData,
		UINT FeatureSupportDataSize) = 0;
};

#define DXGI_PRESENT_ALLOW_TEARING 0x00000200UL
#define DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING 2048

#endif