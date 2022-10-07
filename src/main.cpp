// Framework3D.cpp : Defines the entry point for the application.
//

#include "Framework3D.h"
#include <wrl.h>
#include "d3d12.h"
#include "dxgi1_6.h"

#include <iostream>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace F3D
{
	void LogAdapters(IDXGIFactory1* dxgiFactory)
	{
		UINT i = 0;
		IDXGIAdapter* adapter = nullptr;
		std::vector<IDXGIAdapter*> adapterList;
		while (dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);
			std::wstring text = L"***Adapter: ";
			text += desc.Description;
			text += L"\n";
			OutputDebugString(text.c_str());
			adapterList.push_back(adapter);
			++i;
		}
		for (size_t i = 0; i < adapterList.size(); ++i)
		{
			//LogAdapterOutputs(adapterList[i]);
			adapterList[i]->Release();
		}
	}
}

int main()
{
	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	if (SUCCEEDED(hr))
	{
		F3D::LogAdapters(dxgiFactory.Get());
	}

	return 0;
}
