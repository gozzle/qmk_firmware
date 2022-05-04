#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_BACKLIGHT
RGB_MATRIX_EFFECT(SOLID_REACTIVE_BACKLIGHT)
#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#ifndef RGB_MATRIX_BACKLIGHT_HSV
#define RGB_MATRIX_BACKLIGHT_HSV HSV_WHITE
#endif
#ifndef RGB_MATRIX_KEYREACTIVE_DELAY
#define RGB_MATRIX_KEYREACTIVE_DELAY 70
#endif

typedef uint8_t (*addsub_f)(uint8_t x, uint8_t y);

// the number of ticks to pause at the top.
// for highlighting the reaction before fading out
// must be less than 255
uint8_t pause_ticks = RGB_MATRIX_KEYREACTIVE_DELAY;

// after <pause_ticks>, cycle smoothly from HSV back to white
static HSV SOLID_REACTIVE_BACKLIGHT_math(HSV hsv, uint16_t offset) {
  HSV base = (HSV){RGB_MATRIX_BACKLIGHT_HSV};

  offset = ((uint16_t)qsub8(offset, pause_ticks) * 255) / (255 - pause_ticks);

  // make hue take the shortest path around the cycle, so that nearby hues fade
  // naturally
  int8_t hdiff = ((base.h - hsv.h + 384) % 256 - 128) * offset / 255;
  uint8_t sdiff = scale16by8(offset, abs(hsv.s - base.s));
  uint8_t vdiff = scale16by8(offset, abs(hsv.v - base.v));
  addsub_f h_op = hdiff > 0 ? add8 : sub8;
  addsub_f s_op = hsv.s > base.s ? sub8 : add8;
  addsub_f v_op = hsv.v > base.v ? sub8 : add8;
  hsv.h = h_op(hsv.h, abs(hdiff));
  hsv.s = s_op(hsv.s, sdiff);
  hsv.v = v_op(hsv.v, vdiff);

  return hsv;
}

static bool SOLID_REACTIVE_BACKLIGHT(effect_params_t* params) {
  return effect_runner_reactive(params, &SOLID_REACTIVE_BACKLIGHT_math);
}

#        endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif     // ENABLE_RGB_MATRIX_SOLID_REACTIVE_BACKLIGHT
#endif         // RGB_MATRIX_KEYREACTIVE_ENABLED
