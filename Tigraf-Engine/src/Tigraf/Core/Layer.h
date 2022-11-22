#pragma once
#include "Application.h"

namespace Tigraf
{

#define DECLARE_LAYER									\
	public: 											\
		virtual void init() override; 					\
		virtual void onUpdate(TimeStep ts) override; 	\
		virtual void onDraw() override; 				\
		virtual void shutdown() override;				\
		virtual void onEvent(Event& event) override;

	class Layer
	{
	public:
		Layer() {}
		virtual ~Layer() {}

		virtual void init() = 0;
		virtual void onUpdate(TimeStep ts) = 0;
		virtual void onDraw() = 0;
		virtual void shutdown() = 0;
		virtual void onEvent(Event& event) = 0;
	};
}
