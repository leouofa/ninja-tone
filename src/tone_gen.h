#ifndef _TONE_GEN_H_

#define _TONE_GEN_H_

#define TAG "tone-gen"

#include <furi.h>

// ids for all scenes used by the app
typedef enum {
    ToneGenAppScene_Starting,
    ToneGenAppScene_Playback,
    ToneGenAppScene_Settings,
    ToneGenAppScene_Instructions,
    ToneGenAppScene_count
} ToneGenAppScene;

// ids for the 2 types of view used by the app
typedef enum {
    ToneGenAppView_SharedMenu,
    ToneGenAppView_Submenu,
    ToneGenAppView_VariableItemList,
    ToneGenAppView_NumberInput,
    ToneGenAppView_PlaybackView,
    ToneGenAppView_BlankView,
    ToneGenAppView_Popup,
    ToneGenAppView_count
} ToneGenAppView;

typedef enum { SINE, SQUARE } ToneWaveType;
typedef enum { LIGHT_COLOR_RED, LIGHT_COLOR_GREEN, LIGHT_COLOR_BLUE, LIGHT_COLOR_ALL } LightColor;

struct ToneData_t {
    int animationOffset;
    ToneWaveType waveType;
    uint16_t frequency;
    float volume;
    uint8_t bpm;
    LightColor lightColor;
    bool ledState;
    uint16_t lightStep;
    FuriTimer* lightTimer;
};

#endif
