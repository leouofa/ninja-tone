#ifndef _INSTRUCTIONS_SCENE_H_

#define _INSTRUCTIONS_SCENE_H_

#include <gui/scene_manager.h>

void scene_on_enter_instructions_scene(void* context);
bool scene_on_event_instructions_scene(void* context, SceneManagerEvent event);
void scene_on_exit_instructions_scene(void* context);

#endif
