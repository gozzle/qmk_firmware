#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
RGB_MATRIX_EFFECT(WHITE_SOLID_REACTIVE)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV WHITE_SOLID_REACTIVE_math(HSV hsv, uint16_t offset) {
  HSV white = (HSV){HSV_WHITE_CUSTOM};

  if (offset > 50) {

    // unsigned int maths means that things go wrong if I don't treat these cases
    // separately
    // TODO figure out a neater way of doing this
    if (hsv.h > white.h) {
      hsv.h -= scale16by8(offset, (hsv.h - white.h));
    } else {
      hsv.h += scale16by8(offset, (white.h - hsv.h));
    }
    if (hsv.s > white.s) {
      hsv.s -= scale16by8(offset, (hsv.s - white.s));
    } else {
      hsv.s += scale16by8(offset, (white.s - hsv.s));
    }
  }
  return hsv;
}

static bool WHITE_SOLID_REACTIVE(effect_params_t* params) {
  return effect_runner_reactive(params, &WHITE_SOLID_REACTIVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // RGB_MATRIX_KEYREACTIVE_ENABLED
