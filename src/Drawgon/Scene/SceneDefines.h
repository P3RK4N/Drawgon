#pragma once

#ifdef DRAWGON_EXPORT

	#define DRAWGON_DEFAULT_SCENE_MODE SceneMode::Play

	#define DRAWGON_SCENE_CAMERA

#else

	#define DRAWGON_DEFAULT_SCENE_MODE SceneMode::Edit

	#define DRAWGON_SCENE_CAMERA

#endif