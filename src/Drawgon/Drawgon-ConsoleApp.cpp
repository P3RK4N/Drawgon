#include <Tigraf/Tigraf.h>
#include "Layers/DrawgonLayer.h"

using namespace Tigraf;
using namespace Drawgon;

void TIGRAF_STARTUP(std::vector<Layer*>& layers)
{
	if(DrawgonLayer::s_DrawgonLayer)
	{
		DrawgonLayer::s_DrawgonLayer->shutdown();
		delete DrawgonLayer::s_DrawgonLayer;
	}
	DrawgonLayer::s_DrawgonLayer = new DrawgonLayer();
	layers.push_back(DrawgonLayer::s_DrawgonLayer);
}
const char* TIGRAF_APP_NAME = "Drawgon";