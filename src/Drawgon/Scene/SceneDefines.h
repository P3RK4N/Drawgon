#pragma once

#ifdef DRAWGON_EXPORT

	#define DRAWGON_DEFAULT_SCENE_MODE SceneMode::Play

	#define DRAWGON_SCENE_CAMERA
	#define DRAWGON_UPDATE_SCENE_CAMERA
	#define DRAWGON_SCENE_VISIBILITY

#else

	#define DRAWGON_DEFAULT_SCENE_MODE SceneMode::Edit

	//Scene camera
	#define DRAWGON_SCENE_CAMERA																										\
		protected:																														\
			Ref<SceneCamera> m_SceneCamera = createRef<SceneCamera>(Application::s_Instance->getWindow()->getSize(), 0.1f, 1000.0f);

	#define DRAWGON_UPDATE_SCENE_CAMERA(timestep) \
		m_SceneCamera->onUpdate(timestep)

#endif