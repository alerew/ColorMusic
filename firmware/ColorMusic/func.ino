void analogInit() {
  analyzer.setVolK(20);           // плавность громкости (0-31)
  analyzer.setTrsh(50);           // порог тишины
  analyzer.setVolMin(10);         // мин. громкость 10
  analyzer.setVolMax(255);        // макс. громкость 255
  analyzer.setDt(1000);            // время между опросами АЦП
  analyzer.setPeriod(5000);       // период между выборками
  analyzer.setPulseTrsh(200);     // верхний порог пульса
  analyzer.setPulseMin(80);       // нижний порог пульса
  analyzer.setPulseTimeout(200);  // таймаут пульсов
}

void stripInit() {
  FastLED.addLeds<WS2812, STRIP_PIN, GRB>(leds, MAX_LEDS).setCorrection( TypicalLEDStrip );
  if (cfg.limit > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, cfg.limit);
  FastLED.setBrightness(cfg.bright);
  FastLED.clear();
}

void changeMode(int8_t dir) {
  cfg.curPreset += dir;   // меняем режим
  if (cfg.curPreset > cfg.presetAmount - 1) cfg.curPreset = 0;
  if (cfg.curPreset < 0) cfg.curPreset = cfg.presetAmount - 1;
  reload = 1;       // обновляем страницу
  EE_updateCfg();
}
void setMode(byte mode) {
  cfg.curPreset = constrain(mode, 0, cfg.presetAmount - 1);
  reload = 1;
  EE_updateCfg();
}
void setState(bool state) {
  if (state == false) {
    turnoffTmr.setInterval(700);
    turnoffTmr.restart();
  }
  else {
    setPower(1);
  }
}
void setPower(bool state) {
  cfg.state = state;
  if (state == 0) {
    FastLED.clear();
    FastLED.show();
  }
  EE_updateCfg();
}
