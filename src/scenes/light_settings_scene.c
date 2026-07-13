#include <gui/modules/number_input.h>
#include <gui/modules/variable_item_list.h>

#include "light_settings_scene.h"
#include "../app_context.h"
#include "../tone_gen.h"

typedef enum {
    LightSettingsSelection_Bpm,
    LightSettingsSelection_Color,
} LightSettingsSelection;

static const LightColor color_option_values[] = {
    LIGHT_COLOR_RED,
    LIGHT_COLOR_GREEN,
    LIGHT_COLOR_BLUE,
    LIGHT_COLOR_ALL,
};
static const char* color_option_names[] = {"Red", "Green", "Blue", "All"};
static char* bpmStr;
static VariableItem* bpmItem;

static void light_settings_set_bpm_text(VariableItem* item, uint8_t bpm) {
    snprintf(bpmStr, 8, "%u", bpm);
    variable_item_set_current_value_text(item, bpmStr);
}

static void bpm_option_change(VariableItem* item) {
    UNUSED(item);
}

static void color_option_change(VariableItem* item) {
    struct AppContext_t* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, color_option_names[index]);
    ((struct ToneData_t*)app->additionalData)->lightColor = color_option_values[index];
}

static void bpm_number_input_callback(void* context, int32_t value) {
    struct AppContext_t* app = context;
    ((struct ToneData_t*)app->additionalData)->bpm = (uint8_t)value;
    light_settings_set_bpm_text(bpmItem, ((struct ToneData_t*)app->additionalData)->bpm);
    view_dispatcher_switch_to_view(app->view_dispatcher, ToneGenAppView_VariableItemList);
}

static void light_settings_enter_callback(void* context, uint32_t index) {
    if(index != LightSettingsSelection_Bpm) {
        return;
    }

    struct AppContext_t* app = context;
    struct View_t* numberInputView = app->activeViews[ToneGenAppView_NumberInput];
    NumberInput* numberInput = numberInputView->viewData;

    number_input_set_header_text(numberInput, "BPM");
    number_input_set_result_callback(
        numberInput,
        bpm_number_input_callback,
        app,
        ((struct ToneData_t*)app->additionalData)->bpm,
        1,
        200);

    view_dispatcher_switch_to_view(app->view_dispatcher, ToneGenAppView_NumberInput);
}

void scene_on_enter_light_settings_scene(void* context) {
    FURI_LOG_I(TAG, "scene_on_enter_light_settings_scene");
    struct AppContext_t* app = (struct AppContext_t*)context;
    struct View_t* variableItemListView = app->activeViews[ToneGenAppView_VariableItemList];
    struct ToneData_t* toneData = app->additionalData;

    variable_item_list_reset(variableItemListView->viewData);
    variable_item_list_set_enter_callback(
        variableItemListView->viewData, light_settings_enter_callback, app);

    VariableItem* item = variable_item_list_add(
        variableItemListView->viewData, "BPM", 1, bpm_option_change, app);
    variable_item_set_current_value_index(item, 0);
    bpmStr = calloc(8, sizeof(char));
    bpmItem = item;
    light_settings_set_bpm_text(item, toneData->bpm);

    item = variable_item_list_add(
        variableItemListView->viewData,
        "Colors",
        COUNT_OF(color_option_values),
        color_option_change,
        app);
    variable_item_set_current_value_index(item, toneData->lightColor);
    variable_item_set_current_value_text(item, color_option_names[toneData->lightColor]);

    view_dispatcher_switch_to_view(app->view_dispatcher, ToneGenAppView_VariableItemList);
}

bool scene_on_event_light_settings_scene(void* context, SceneManagerEvent event) {
    FURI_LOG_I(TAG, "scene_on_event_light_settings_scene");
    UNUSED(context);
    UNUSED(event);
    return false;
}

void scene_on_exit_light_settings_scene(void* context) {
    FURI_LOG_I(TAG, "scene_on_exit_light_settings_scene");
    UNUSED(context);
    free(bpmStr);
    bpmStr = NULL;
    bpmItem = NULL;
}
