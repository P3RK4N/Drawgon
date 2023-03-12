#pragma once

#ifndef DRAWGON_EXPORT

#include "Drawgon/GUI/GUI_GeneralDefines.h"

#include <Tigraf/Tigraf.h>
#include <Drawgon/Console/drawgon_console_sink.h>

using namespace Tigraf;

//TODO: Make some or all event logging a lower tier (from trace to debug) and hide it in editor

namespace Drawgon
{
    class Console
	{
        DRAWGON_DECLARE_ON_GUI_RENDER

        friend class DrawgonLayer;

    public:
        Console() { REPLACE_LOG_SINK(m_ConsoleSink); REPLACE_CORE_LOG_SINK(m_ConsoleSink); }

    private:
        Ref<drawgon_console_sink_mt> m_ConsoleSink = createRef<drawgon_console_sink_mt>(100);
	};
}

#endif