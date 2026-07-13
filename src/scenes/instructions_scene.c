#include "instructions_scene.h"
#include "../app_context.h"
#include "../tone_gen.h"

void scene_on_enter_instructions_scene(void* context) {
    FURI_LOG_I(TAG, "scene_on_enter_instructions_scene");
    struct AppContext_t* app = (struct AppContext_t*)context;
    view_dispatcher_switch_to_view(app->view_dispatcher, ToneGenAppView_BlankView);
}

bool scene_on_event_instructions_scene(void* context, SceneManagerEvent event) {
    FURI_LOG_I(TAG, "scene_on_event_instructions_scene");
    UNUSED(context);
    UNUSED(event);
    return false;
}

void scene_on_exit_instructions_scene(void* context) {
    FURI_LOG_I(TAG, "scene_on_exit_instructions_scene");
    UNUSED(context);
}
