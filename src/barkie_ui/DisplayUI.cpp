#include "DisplayUI.h"

// Font declaration
LV_FONT_DECLARE(lv_font_montserrat_28);

DisplayUI::DisplayUI() : isReporting(false), onStateChange(nullptr), callbackData(nullptr) {}

void DisplayUI::init() {
    // Any one-time style initialization could go here
}

void DisplayUI::setStateChangeCallback(StateChangeCallback cb, void* data) {
    onStateChange = cb;
    callbackData = data;
}

void DisplayUI::showSplash() {
    lv_obj_clean(lv_scr_act());
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Connecting to WiFi...");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void DisplayUI::btn_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        DisplayUI* ui = (DisplayUI*)lv_event_get_user_data(e);

        // Toggle Internal State
        bool newState = !ui->isReporting;
        ui->setDetectionState(newState);

        // Notify Listener
        if (ui->onStateChange) {
            ui->onStateChange(newState, ui->callbackData);
        }
    }
}

void DisplayUI::setDetectionState(bool state) {
    isReporting = state;
    if (labelAction) {
        if (isReporting) {
             lv_label_set_text(labelAction, "DETECTING...");
        } else {
             lv_label_set_text(labelAction, "START");
        }
    }
}

void DisplayUI::showMain() {
    lv_obj_clean(lv_scr_act());

    // Set Dark Background
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_white(), LV_PART_MAIN);

    // Wifi Status
    labelWifiStatus = lv_label_create(lv_scr_act());
    lv_label_set_text(labelWifiStatus, "WiFi: --");
    lv_obj_set_style_text_color(labelWifiStatus, lv_color_white(), 0);
    lv_obj_set_style_text_font(labelWifiStatus, &lv_font_montserrat_28, 0);
    lv_obj_align(labelWifiStatus, LV_ALIGN_TOP_RIGHT, -10, 10);

    // Start/Stop Button
    btnAction = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btnAction, 240, 80); // Width 240 as per fix
    lv_obj_align(btnAction, LV_ALIGN_CENTER, 0, -20);
    // User data is 'this' instance of DisplayUI
    lv_obj_add_event_cb(btnAction, btn_event_handler, LV_EVENT_CLICKED, this);

    labelAction = lv_label_create(btnAction);
    if (isReporting) {
         lv_label_set_text(labelAction, "DETECTING...");
    } else {
         lv_label_set_text(labelAction, "START");
    }
    lv_obj_set_style_text_font(labelAction, &lv_font_montserrat_28, 0);
    lv_obj_center(labelAction);

    // Sensor Label
    labelSensorData = lv_label_create(lv_scr_act());
    lv_label_set_text(labelSensorData, "Sensor: Initializing...");
    lv_obj_set_style_text_color(labelSensorData, lv_color_white(), 0);
    lv_obj_set_style_text_font(labelSensorData, &lv_font_montserrat_28, 0);
    lv_obj_align(labelSensorData, LV_ALIGN_BOTTOM_MID, 0, -10);
}

void DisplayUI::updateWiFiStatus(bool connected) {
    if (labelWifiStatus) {
        lv_label_set_text(labelWifiStatus, connected ? "WiFi: OK" : "WiFi: Disc");
    }
}

void DisplayUI::format_sensor_val(char* buf, float val) {
    int int_part = (int)val;
    int dec_part = abs((int)((val - int_part) * 10));
    sprintf(buf, "%d.%d", int_part, dec_part);
}

void DisplayUI::updateSensorData(float ax, float ay, float az, float gx, float gy, float gz) {
    if (labelSensorData) {
        char s_ax[16], s_ay[16], s_az[16];
        char s_gx[16], s_gy[16], s_gz[16];

        format_sensor_val(s_ax, ax);
        format_sensor_val(s_ay, ay);
        format_sensor_val(s_az, az);
        format_sensor_val(s_gx, gx);
        format_sensor_val(s_gy, gy);
        format_sensor_val(s_gz, gz);

        lv_label_set_text_fmt(labelSensorData,
            "A: %s %s %s\nG: %s %s %s",
            s_ax, s_ay, s_az, s_gx, s_gy, s_gz);
    }
}
