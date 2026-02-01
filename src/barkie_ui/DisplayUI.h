#pragma once

#include "lvgl.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

class DisplayUI {
public:
    // Callback type for state changes (using raw pointer context for C compatibility)
    typedef void (*StateChangeCallback)(bool newState, void* userData);

    DisplayUI();

    void init();
    void showSplash();
    void showMain();
    
    void updateWiFiStatus(bool connected);
    void updateSensorData(float ax, float ay, float az, float gx, float gy, float gz);
    void setDetectionState(bool state);
    
    // Register a callback to be notified when the user clicks the button
    void setStateChangeCallback(StateChangeCallback cb, void* data);

    // Current state getter
    bool getDetectionState() const { return isReporting; }

private:
    // UI Logic Variables
    bool isReporting = false;

    // Callbacks
    StateChangeCallback onStateChange = nullptr;
    void* callbackData = nullptr;

    // LVGL Widgets
    lv_obj_t* labelWifiStatus = nullptr;
    lv_obj_t* btnAction = nullptr;
    lv_obj_t* labelAction = nullptr;
    lv_obj_t* labelSensorData = nullptr;

    // Internal Helpers
    static void btn_event_handler(lv_event_t * e);
    void format_sensor_val(char* buf, float val);
};
