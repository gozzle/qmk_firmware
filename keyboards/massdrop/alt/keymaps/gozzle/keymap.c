#include QMK_KEYBOARD_H

enum alt_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase                                   //Working
    L_BRD,              //LED Brightness Decrease                                   //Working
    L_PTN,              //LED Pattern Select Next                                   //Working
    L_PTP,              //LED Pattern Select Previous                               //Working
    L_PSI,              //LED Pattern Speed Increase                                //Working
    L_PSD,              //LED Pattern Speed Decrease                                //Working
    L_T_MD,             //LED Toggle Mode                                           //Working
    L_T_ONF,            //LED Toggle On / Off                                       //Broken
    L_ON,               //LED On                                                    //Broken
    L_OFF,              //LED Off                                                   //Broken
    L_T_BR,             //LED Toggle Breath Effect                                  //Working
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction                    //Working
    U_T_AGCR,           //USB Toggle Automatic GCR control                          //Working
    DBG_TOG,            //DEBUG Toggle On / Off                                     //
    DBG_MTRX,           //DEBUG Toggle Matrix Prints                                //
    DBG_KBD,            //DEBUG Toggle Keyboard Prints                              //
    DBG_MOU,            //DEBUG Toggle Mouse Prints                                 //
    MD_BOOT             //Restart into bootloader after hold timeout                //Working
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
        LT(1, KC_CAPS), KC_A, KC_S, KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_GRV,           KC_UP,   MO(1),   \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, TG(2),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_MUTE, \
        L_T_BR,   L_PSD,   L_BRI,   L_PSI,   _______, _______, _______, _______, U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS,_______, KC_VOLU, \
        _______, L_PTP,   L_BRD,   L_PTN,    _______, _______, _______, _______, _______, _______, _______, _______,         _______, KC_VOLD, \
        _______, L_T_MD,  L_T_ONF, L_T_PTD,  _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,         KC_PGUP, _______, \
        _______, _______, _______,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    [2] = LAYOUT(
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

// Taken from qmk_firmware/tmk_core/protocol/arm_atsam/led_matrix_programs.c
#define LED_ANIMATION_ID_WHITE 7

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Set the default LED effect to be solid white
    led_animation_id = LED_ANIMATION_ID_WHITE;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_MD:
            if (record->event.pressed) {
                led_lighting_mode++;
                if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                led_enabled = !led_enabled;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                led_enabled = 1;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                led_enabled = 0;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_PTD:
            if (record->event.pressed) {
                led_animation_direction = !led_animation_direction;
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
        default:
            return true; //Process all other keycodes normally
    }
}

led_instruction_t led_instructions[] = {
    //LEDs are normally inactive, no processing is performed on them
    //Flags are used in matching criteria for an LED to be active and indicate how to color it
    //Flags can be found in tmk_core/protocol/arm_atsam/led_matrix.h (prefixed with LED_FLAG_)
    //LED IDs can be found in config_led.h in the keyboard's directory
    //Examples are below

    //All LEDs use the user's selected pattern (this is the factory default)
    { .flags = LED_FLAG_USE_ROTATE_PATTERN },

    //When layer1 is active: edge is blue; F keys are red; LED controls are green; Navigation & media are blue; Misc/Debug are yellow
    // Blue edge
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        .id0 = 0x00000000, .id1 = 0x00000000, .id2 = 0xFFFFFFF8, .id3 = 0x000003FF,
        .b = 255,
        .layer = 1
    },
    // Red F1 keys
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // keys 2 - 13 0000 0000 0000 0000 0001 1111 1111 1110
        .id0 = 0x00001FFE, .id1 = 0x00000000, .id2 = 0x00000000, .id3 = 0x00000000,
        .r = 255,
        .layer = 1
    },
    // Green LED Controls
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // keys 16, 17, 18, 19, 32: 0000 0000 0000 0111 1000 0000 0000 0000
        // keys 33, 34, 46, 47, 48: 0000 0000 0000 0000 1110 0000 0000 0011
        .id0 = 0x80078000, .id1 = 0x0000E003, .id2 = 0x00000000, .id3 = 0x00000000,
        .g = 255,
        .layer = 1
    },
    // Blue Nav & Media Controls
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // id0 keys 15, 26, 27, 28, 30: 0010 1110 0000 0000 0100 0000 0000 0000
        // id1 keys 44, 57: 0000 0001 0000 0000 0000 1000 0000 0000
        // id2 keys 65, 66, 67: 0000 0000 0000 0000 0000 0000 0000 0111
        .id0 = 0x2E004000, .id1 = 0x01000800, .id2 = 0x00000007, .id3 = 0x00000000,
        .b = 255,
        .layer = 1
    },
    // Yellow Misc/Debug
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // 24, 50, 51
        // id0 keys 24: 0000 0000 1000 0000 0000 0000 0000 0000
        // id1 keys 50, 51: 0000 0000 0000 0110 0000 0000 0000 0000
        .id0 = 0x00800000, .id1 = 0x00060000, .id2 = 0x00000000, .id3 = 0x00000000,
        .r = 255, .g = 255,
        .layer = 1
    },

    // When layer 2 is active: edge is green; number keys are red; operator keys are yellow
    // Green edge
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        .id0 = 0x00000000, .id1 = 0x00000000, .id2 = 0xFFFFFFF8, .id3 = 0x000003FF,
        .g = 255,
        .layer = 2
    },
    // Red num keys
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // 22, 23, 24, 37, 38, 39, 49, 50, 51, 62
        // id0 keys 22, 23, 24: 0000 0000 1110 0000 0000 0000 0000 0000
        // id1 keys 37, 38, 39, 51, 52, 53, 54, 62: 0010 0000 0011 1100 0000 0000 0111 0000
        .id0 = 0x00E00000, .id1 = 0x203C0070, .id2 = 0x00000000, .id3 = 0x00000000,
        .r = 255,
        .layer = 2
    },
    // Blue operator keys
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // 9, 12, 13, 43, 52, 53
        // id0 keys 9, 12, 13: 0000 0000 0000 0000 0001 1001 0000 0000
        // id1 keys 43, 55: 0000 0000 0100 0000 0000 0100 0000 0000
        .id0 = 0x00001900, .id1 = 0x00400400, .id2 = 0x00000000, .id3 = 0x00000000,
        .b = 255,
        .layer = 2
    },
    // Yellow Fn key
    {
        .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB,
        // 64
        // id1 keys 64: 1000 0000 0000 0000 0000 0000 0000 0000
        .id0 = 0x00000000, .id1 = 0x80000000, .id2 = 0x00000000, .id3 = 0x00000000,
        .r = 255, .g = 255,
        .layer = 2
    },

    //end must be set to 1 to indicate end of instruction set
     { .end = 1 }
};
