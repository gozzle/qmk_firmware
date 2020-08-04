#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
RGB_MATRIX_EFFECT(WHITE_SOLID_REACTIVE)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef uint8_t (*addsub_f)(uint8_t x, uint8_t y);

// the number of ticks to pause at the top.
// for highlighting the hue before fading out
// must be less than 255
uint8_t pause_ticks = 70;

// after <pause_ticks>, cycle smoothly from HSV back to custom white
static HSV WHITE_SOLID_REACTIVE_math(HSV hsv, uint16_t offset) {
  HSV white = (HSV){HSV_WHITE_CUSTOM};

  offset = qsub8(offset, pause_ticks) * 255 / (255 - pause_ticks);

  uint8_t hdiff = scale16by8(offset, abs(hsv.h - white.h));
  uint8_t sdiff = scale16by8(offset, abs(hsv.s - white.s));
  addsub_f h_op = hsv.h > white.h ? sub8 : add8;
  addsub_f s_op = hsv.s > white.s ? sub8 : add8;
  hsv.h = h_op(hsv.h, hdiff);
  hsv.s = s_op(hsv.s, sdiff);

  return hsv;
}

static bool WHITE_SOLID_REACTIVE(effect_params_t* params) {
  return effect_runner_reactive(params, &WHITE_SOLID_REACTIVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // RGB_MATRIX_KEYREACTIVE_ENABLED
