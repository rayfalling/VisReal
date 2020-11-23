#include "Entry.h"


#include <wrl.h>

#include "DirectX/DxWindowManager.h"
using namespace Microsoft;
using namespace Microsoft::WRL;
#include <dxgi1_6.h>
#include <DirectXMath.h>
using namespace DirectX;
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>

struct GRS_VERTEX {
	XMFLOAT3 position;
	XMFLOAT4 color;
};

int main() {
	Engine::InitEngine();

	return 0;
}
