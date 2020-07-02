#include QMK_KEYBOARD_H

enum alt_layers {
    _QWERTY = 0,
    _FUNCTIONS,
    _NUMPAD
};

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
        LT(1, KC_CAPS), KC_A, KC_S, KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_GRV,           KC_UP,   MO(1),   \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, TG(2),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_FUNCTIONS] = LAYOUT(
        _______,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_MUTE, \
        _______, RGB_SPD,  RGB_VAI,  RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS,_______, KC_VOLU, \
        _______, RGB_RMOD, RGB_VAD,  RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,         _______, KC_VOLD, \
        _______, RGB_TOG,  _______, _______,  _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,         KC_PGUP, _______, \
        _______, _______,  _______,                             _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PAST, _______, _______, KC_PMNS, KC_PPLS, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______,          KC_PENT, _______, \
        _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_PSLS, _______,          _______, _______, \
        _______, _______, _______,                            KC_P0,                              _______, _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};


#define RED {RGB_RED}
#define BLUE {RGB_BLUE}
#define GREEN {RGB_GREEN}
#define YELLOW {RGB_YELLOW}

#ifdef _______
#undef _______
#define _______ {RGB_WHITE}

// static led mappings for layers
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    /*
     [_QWERTY] = {
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
         _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, \
         // Underglow LEDs
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
         _______, _______, _______, _______, _______, _______, _______, _______
     },
    */
    [_FUNCTIONS] = {
        _______, RED    , RED    , RED    , RED    , RED    , RED    , RED    , RED    , RED    , RED    , RED    , RED    , _______, BLUE   , \
        _______, GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , _______, _______, YELLOW , _______, BLUE   , BLUE   , BLUE   , _______, BLUE   , \
        _______, GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , _______, _______, _______, _______, _______, _______,          _______, BLUE   , \
        _______, GREEN  , _______, _______, _______, YELLOW , YELLOW , _______, _______, _______, _______, _______,          BLUE   , _______, \
        _______, _______, _______,                            _______,                            _______, _______, BLUE   , BLUE   , BLUE   , \
        // Underglow LEDs
        BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , \
        BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , \
        BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE   , BLUE
    },
    [_NUMPAD] = {
        _______, _______, _______, _______, _______, _______, _______, _______, BLUE   , _______, _______, BLUE   , BLUE   , _______, _______, \
        _______, _______, _______, _______, _______, _______, RED    , RED    , RED    , _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, RED    , RED    , RED    , _______, _______, _______,          BLUE   , _______, \
        _______, _______, _______, _______, _______, _______, RED    , RED    , RED    , RED    , BLUE   , _______,          _______, _______, \
        _______, _______, _______,                            RED    ,                            _______, YELLOW , _______, _______, _______, \
        // Underglow LEDs
        GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , \
        GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , \
        GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN  , GREEN
    }
};

#undef _______
#define _______ KC_TRANS
#endif


// returns default rgb_config for the given mode
rgb_config_t rgb_mode_get_default(uint8_t mode) {
    rgb_config_t ret;
    switch(mode) {
        case RGB_MATRIX_SOLID_COLOR:
          ret.hsv = (HSV){HSV_WHITE};
          break;
        case RGB_MATRIX_SOLID_REACTIVE:
          ret.hsv = (HSV){HSV_CYAN};
          break;
        default:
          // use red as default
          ret.hsv = (HSV){HSV_RED};
    }
    return ret;
}

// applys the default rgb_config for the current mode
void rgb_matrix_set_default(void) {
    // only set the HSV, since that's all I'm playing with at the moment
    rgb_matrix_config.hsv = rgb_mode_get_default(rgb_matrix_get_mode()).hsv;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    rgb_matrix_set_default();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

// process keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case RGB_RMOD:
        case RGB_MOD:
            if (record->event.pressed) {
                // process as normal...
                process_rgb(keycode, record);
                // then set new default
                rgb_matrix_set_default();
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

// set hardcoded layer RGB maps from ledmap
void set_layer_color(int layer) {

    // skip layer _QWERTY to allow effects
    if (layer == _QWERTY) { return; }

    int min_led = 0;
    int max_led = DRIVER_LED_TOTAL;
    if (rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
        // skip keylight leds
        min_led = 67;
    } else if (rgb_matrix_get_flags() == LED_FLAG_KEYLIGHT) {
        // skip underglow leds
        max_led = 67;
    }

    for (int i = min_led; i < max_led; i++) {
        RGB rgb = {
            .r = pgm_read_byte(&ledmap[layer][i][0]),
            .g = pgm_read_byte(&ledmap[layer][i][1]),
            .b = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (rgb.r || rgb.g || rgb.b) {
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else {
            // default is 0xFFFFFF so should always have rgb set
        }
    }
}

// calculate the "on" colour of indicator keys to make them stand out from their
// off colour.
HSV get_indicator_on_color(HSV off) {
    // set opposite in HSV space, except Value which should be 100 if it was
    // zero before
    HSV on = {
        .h = 255 - off.h,
        .s = 255 - off.s,
        .v = (off.v == 0) ? 255 : off.v,
    };
    return on;
}


// set caps lock colour based on the current config HSV and flag status
// could be adapted to handle other indicator lights fairly easily, but my
// setup doesn't use those.
void set_capslock_color(void) {

    HSV hsv_off = rgb_matrix_config.hsv;
    // if keylights are off then set the off colour to {0,255,0}
    // (fully saturated but off. opposite is white.)
    if (!HAS_FLAGS(rgb_matrix_get_flags(), LED_FLAG_KEYLIGHT)) {
        hsv_off = (HSV){0, 255, 0};
    }
    HSV hsv_on = get_indicator_on_color(hsv_off);

    RGB off = hsv_to_rgb(hsv_off);
    RGB on = hsv_to_rgb(hsv_on);

    if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(USB_LED_CAPS_LOCK_SCANCODE, on.r, on.g, on.b);
    } else {
        rgb_matrix_set_color(USB_LED_CAPS_LOCK_SCANCODE, off.r, off.g, off.b);
    }
}

// Runs every cycle to set the RGB state
void rgb_matrix_indicators_user(void) {
    // don't bother if LEDs should be off
    if (g_suspend_state ||
        rgb_matrix_get_flags() == LED_FLAG_NONE) {
        return;
    }
    set_layer_color(get_highest_layer(layer_state));
    set_capslock_color();
}
