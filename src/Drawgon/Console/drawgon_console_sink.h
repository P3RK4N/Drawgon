#pragma once
#include <spdlog/sinks/base_sink.h>
#include <imgui.h>

#include <deque>

namespace Drawgon
{
    typedef enum
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
    } Drawgon_Message_level;

    static ImVec4 ConsoleMessageLevelToColor[6]
    {
	    ImVec4{1.0f,1.0f,1.0f,1.0f},	//Trace
	    ImVec4(1.0f,1.0f,0.5f,1.0f),	//Debug
	    ImVec4(0.0f,1.0f,0.0f,1.0f),	//Info
	    ImVec4(1.0f,1.0f,0.0f,1.0f),	//Warn
	    ImVec4(1.0f,0.5f,0.0f,1.0f),	//Err
	    ImVec4(1.0f,0.0f,0.0f,1.0f),	//Critical
    };

    //TODO: Make more compatible with SPDLOG and its style and formatting
    template<typename Mutex>
    class drawgon_console_sink final : public spdlog::sinks::base_sink<Mutex>
    {
    public:
        drawgon_console_sink(uint32_t capacity = 100U) : m_Capacity(capacity) {}
        drawgon_console_sink(const drawgon_console_sink &) = delete;
        drawgon_console_sink &operator=(const drawgon_console_sink &) = delete;

        void setCapacity(uint32_t capacity) { m_Capacity = capacity; }

        void drawToConsole()
        {
            std::lock_guard<Mutex> lock(this->mutex_);
            for(const auto& [level, text] : m_MessageDeque)
            {
                ImGui::TextColored
                (
                    ConsoleMessageLevelToColor[(uint32_t)level],
                    text.c_str()
                );
            }

            if(m_NewMessages) 
            {
                m_NewMessages = false;
                ImGui::SetScrollHereY();
            }
        }

    protected:
        void sink_it_(const spdlog::details::log_msg &msg) override
        {
            spdlog::memory_buf_t formatted;
            spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
            std::string text(formatted.data(), formatted.size());
            m_MessageDeque.push_back({(Drawgon_Message_level)msg.level, text});
            if(m_MessageDeque.size() > m_Capacity) m_MessageDeque.pop_front();
            m_NewMessages = true;
        }

        void flush_() override
        {
            m_MessageDeque.clear();
        }

        std::deque<std::pair<Drawgon_Message_level, std::string>> m_MessageDeque{};
        uint32_t m_Capacity;
        bool m_NewMessages = false;
    };

    using drawgon_console_sink_mt = drawgon_console_sink<std::mutex>;
    using drawgon_console_sink_st = drawgon_console_sink<spdlog::details::null_mutex>;
}