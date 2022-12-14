void effectsRountine() {
  if (!cfg.state) return;
  if (!connect) {
    fader(CRGB::Red);
    return;
  }
  analyzer.tick();
  yield();
  if (!effTmr.isReady()) return;

  byte vol = analyzer.getVol();
  yield();

  // =================================================== ЭФФЕКТЫ ===================================================
  static byte color = 0;
  switch (CUR_PRES.effect) {
    case 0: // =================================== РЕЗКАЯ СМЕНА ЦВЕТА ===================================
      {
        CRGB c;
        if (analyzer.getPulse() && CUR_PRES.pallete < 2) color += steps[CUR_PRES.pallete];    // скачок громкости
        else if (CUR_PRES.pallete == 2) color += steps[CUR_PRES.pallete];

        if (CUR_PRES.pallete == 3) c = CHSV(vol / 5, 255 - vol / 2, vol);                     // огненная палитра
        else c = setWheel8(color, vol);

        for (int i = 0; i < cfg.numLeds; i++) {
          leds[i] = c;
        }
      }
      break;
    case 1: // =================================== СТОЛБИК ГРОМКОСТИ ===================================
      {
        static byte hue = 0;
        FastLED.clear();
        if (rainbowTmr.isReady()) {
          hue += CUR_PRES.speed / 5;
        }
        if (CUR_PRES.speed == 0) hue = 0;

        byte count = 0;
        for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - map(vol, 0, 255, 0, MAX_CH)); i--) {
          leds[i] = ColorFromPalette(CUR_PAL, getScale(count) * 2 - hue);   // заливка по палитре
          count++;
        }
        count = 0;
        for (int i = (MAX_CH); i < (MAX_CH + map(vol, 0, 255, 0, MAX_CH)); i++ ) {
          leds[i] = ColorFromPalette(CUR_PAL, getScale(count) * 2 - hue);   // заливка по палитре
          count++;
        }
      }
      break;
    case 2: // =================================== БЕГУЩИЕ ОГНИ ===================================
      {
        for (int k = 0; k < 2; k++) {
          for (int i = cfg.numLeds - 1; i > MAX_CH; i--) {
            leds[i] = leds[i - 1];
          }
          for (int i = 0; i < MAX_CH; i++) {
            leds[i] = leds[i + 1];
          }
        }
        if (analyzer.getPulse() && CUR_PRES.pallete < 2) color += steps[CUR_PRES.pallete];   // скачок громкости
        else if (CUR_PRES.pallete == 2) color += steps[CUR_PRES.pallete];

        if (CUR_PRES.pallete == 3) leds[MAX_CH] = CHSV(vol / 5, 255 - vol / 2, vol);   // огненная палитра
        else leds[MAX_CH] = CHSV(color, 255, vol);
      }
      break;
    case 3: // =================================== ГРАДИЕНТ ===================================
      {
        static uint16_t counter = 0;
        for (int i = 0; i < cfg.numLeds; i++) {
          if (CUR_PRES.flag == 1)leds[i] = ColorFromPalette(CUR_PAL, getMaxNoise(getScale(i), counter), 255, LINEARBLEND);   // перлин
          else leds[i] = ColorFromPalette(CUR_PAL, getScale(i) + counter, 255, LINEARBLEND);   // градиент
        }
        if (rainbowTmr.isReady()) {
          counter += CUR_PRES.speed / 5;
        }
      }
      break;
    case 4:
      {
        for (int i = 0; i < cfg.numLeds; i++) {
          leds[i] = setWheel8(CUR_PRES.pallete, 255);
        }
      }
      break;
  }
  yield();
  FastLED.show();
}
float getScale(int num) {
  if (CUR_PRES.scale == 0) return (float)255 * num / (cfg.numLeds - 1);
  return (float)CUR_PRES.scale * num / 5;
}
CRGB setWheel8(uint8_t color, int br) {
  uint8_t r = 0, g = 0, b = 0;
  uint8_t shift;
  if (color > 170) {
    shift = (color - 170) * 3;
    r = shift;
    g = 0;
    b = 255 - shift;
  } else if (color > 85) {
    shift = (color - 85) * 3;
    r = 0;
    g = 255 - shift;
    b = shift;
  } else {
    shift = color * 3;
    r = 255 - shift;
    g = shift;
    b = 0;
  }
  _fade8local(r, g, b, br);
  return CRGB(r, g, b);
}
void _fade8(uint8_t& x, uint8_t br) {
  x = ((uint16_t)x * (br + 1)) >> 8;
}
void _fade8local(byte& r, byte& g, byte& b, byte br) {
  if (br >= 0) {
    _fade8(r, br);
    _fade8(g, br);
    _fade8(b, br);
  }
}

void blink16(CRGB color) {
  for (byte i = 0; i < 3; i++) {
    fill_solid(leds, MAX_LEDS, color);
    FastLED.show();
    delay(300);
    FastLED.clear();
    FastLED.show();
    delay(300);
  }
}
byte getMaxNoise(uint16_t x, uint16_t y) {
  return constrain(map(inoise8(x, y), 50, 200, 0, 255), 0, 255);
}
void fader(CRGB color) {
  static uint32_t tmr;
  static int val = 0;
  static bool dir = true;
  if (millis() - tmr >= 20) {
    tmr = millis();
    val += dir ? 3 : -3;
    val = constrain(val, 5, 120);
    if (val >= 120 || val <= 5) dir = !dir;
    FastLED.showColor(color, val);
  }
}
