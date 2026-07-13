#include <furi_hal.h>

#include "playback_scene.h"
#include "../app_context.h"
#include "../tone_gen.h"
#include "../system/audio_helper.h"

#define SINE_WAVE(x, toneModelData) \
    (sin((x + toneDataModel->animationOffset) * 50) * 20 + (64 / 2))

#define SQUARE_WAVE(x, toneModelData) \
    ((sin((x + toneDataModel->animationOffset) * 50) > 0 ? 1 : -1) * 20 + (64 / 2))

#define LIGHT_UPDATE_INTERVAL_MS 20
#define LIGHT_MAX_BRIGHTNESS 255
#define LIGHT_TWO_PI 6.28318530718f

static void playback_set_light_color(LightColor lightColor, uint8_t value) {
    furi_hal_light_set(LightRed, 0);
    furi_hal_light_set(LightGreen, 0);
    furi_hal_light_set(LightBlue, 0);

    switch(lightColor) {
    case LIGHT_COLOR_RED:
        furi_hal_light_set(LightRed, value);
        break;
    case LIGHT_COLOR_GREEN:
        furi_hal_light_set(LightGreen, value);
        break;
    case LIGHT_COLOR_BLUE:
        furi_hal_light_set(LightBlue, value);
        break;
    case LIGHT_COLOR_ALL:
        furi_hal_light_set(LightRed, value);
        furi_hal_light_set(LightGreen, value);
        furi_hal_light_set(LightBlue, value);
        break;
    }
}

static uint32_t playback_blink_interval_ticks(uint8_t bpm) {
    UNUSED(bpm);
    return furi_ms_to_ticks(LIGHT_UPDATE_INTERVAL_MS);
}

static uint16_t playback_light_steps_per_beat(uint8_t bpm) {
    uint16_t beatMs = 60 * 1000 / bpm;
    uint16_t steps = beatMs / LIGHT_UPDATE_INTERVAL_MS;
    return steps > 0 ? steps : 1;
}

static uint8_t playback_light_brightness(struct ToneData_t* toneDataModel) {
    uint16_t stepsPerBeat = playback_light_steps_per_beat(toneDataModel->bpm);
    uint16_t step = toneDataModel->lightStep % stepsPerBeat;

    switch(toneDataModel->waveType) {
    case SINE: {
        float phase = ((float)step / (float)stepsPerBeat) * LIGHT_TWO_PI;
        return (uint8_t)((sinf(phase) + 1.0f) * 0.5f * LIGHT_MAX_BRIGHTNESS);
    }
    case SQUARE:
        return step < (stepsPerBeat / 2) ? LIGHT_MAX_BRIGHTNESS : 0;
    default:
        return 0;
    }
}

static void playback_light_timer_callback(void* context) {
    struct ToneData_t* toneDataModel = context;
    uint16_t stepsPerBeat = playback_light_steps_per_beat(toneDataModel->bpm);
    uint8_t brightness = playback_light_brightness(toneDataModel);
    playback_set_light_color(toneDataModel->lightColor, brightness);
    toneDataModel->lightStep = (toneDataModel->lightStep + 1) % stepsPerBeat;
    toneDataModel->ledState = brightness > 0;
}

// Renders the waveform
static void playback_view_draw_callback(Canvas* canvas, void* model) {
    UNUSED(model);

    struct ToneData_t* toneDataModel = (struct ToneData_t*)model;
    for(int x = 1; x < 128; x++) {
        int x1 = x - 1;
        int x2 = x;
        int y1 = 0;
        int y2 = 0;
        switch(toneDataModel->waveType) {
        case SINE:
            y1 = SINE_WAVE(x1, toneDataModel);
            y2 = SINE_WAVE(x2, toneDataModel);
            break;
        case SQUARE:
            y1 = SQUARE_WAVE(x1, toneDataModel);
            y2 = SQUARE_WAVE(x2, toneDataModel);
            break;
        default:
            y1 = 64 / 2;
            y2 = 64 / 2;
            break;
        }
        // Draw lines to connect the pieces of the wave.
        canvas_draw_line(canvas, x1, y1, x2, y2);
    }
    if(toneDataModel->animationOffset < 128) {
        toneDataModel->animationOffset += 2;
    } else {
        toneDataModel->animationOffset = 0;
    }
}

// Sets up the waveform to be displayed
void scene_on_enter_playback_scene(void* context) {
    FURI_LOG_I(TAG, "scene_on_enter_playback_scene");
    struct AppContext_t* app = (struct AppContext_t*)context;
    struct View_t* playbackView = app->activeViews[ToneGenAppView_PlaybackView];

    // Configure the custom view
    view_set_draw_callback(playbackView->viewData, playback_view_draw_callback);
    view_set_context(playbackView->viewData, context);

    FURI_LOG_I(TAG, "setting view model");
    struct ToneData_t* toneDataModel = (struct ToneData_t*)view_get_model(playbackView->viewData);
    toneDataModel->waveType = ((struct ToneData_t*)app->additionalData)->waveType;
    toneDataModel->frequency = ((struct ToneData_t*)app->additionalData)->frequency;
    toneDataModel->volume = ((struct ToneData_t*)app->additionalData)->volume;
    toneDataModel->bpm = ((struct ToneData_t*)app->additionalData)->bpm;
    toneDataModel->lightColor = ((struct ToneData_t*)app->additionalData)->lightColor;
    toneDataModel->ledState = false;
    toneDataModel->lightStep = 0;
    toneDataModel->lightTimer =
        furi_timer_alloc(playback_light_timer_callback, FuriTimerTypePeriodic, toneDataModel);
    furi_timer_start(toneDataModel->lightTimer, playback_blink_interval_ticks(toneDataModel->bpm));
    playback_light_timer_callback(toneDataModel);

    // Set the currently active view
    FURI_LOG_I(TAG, "setting active view");
    view_dispatcher_switch_to_view(app->view_dispatcher, ToneGenAppView_PlaybackView);

    if(initializeSpeaker()) {
        FURI_LOG_I(TAG, "Starting sound");
        startSound(toneDataModel);
    }
}

// Not actively used in this instance.
bool scene_on_event_playback_scene(void* context, SceneManagerEvent event) {
    FURI_LOG_I(TAG, "scene_on_event_playback_scene");
    UNUSED(context);
    UNUSED(event);
    return false;
}

// Not actively used in this instance.
void scene_on_exit_playback_scene(void* context) {
    FURI_LOG_I(TAG, "scene_on_exit_playback_scene");
    struct AppContext_t* app = (struct AppContext_t*)context;
    struct View_t* playbackView = app->activeViews[ToneGenAppView_PlaybackView];
    struct ToneData_t* toneDataModel = (struct ToneData_t*)view_get_model(playbackView->viewData);

    if(toneDataModel->lightTimer != NULL) {
        furi_timer_stop(toneDataModel->lightTimer);
        furi_timer_free(toneDataModel->lightTimer);
        toneDataModel->lightTimer = NULL;
    }
    toneDataModel->ledState = false;
    toneDataModel->lightStep = 0;
    playback_set_light_color(toneDataModel->lightColor, 0);

    stopSound();
    deinitializeSpeaker();
}
