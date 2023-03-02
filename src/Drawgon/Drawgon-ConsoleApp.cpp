#include <Tigraf/Tigraf.h>
#include "Layers/DrawgonLayer.h"

using namespace Tigraf;

void TIGRAF_STARTUP(std::vector<Layer*>& layers)
{
	Drawgon::DrawgonLayer* dl = new Drawgon::DrawgonLayer();
	layers.push_back(dl);
}
const char* TIGRAF_APP_NAME = "Drawgon";