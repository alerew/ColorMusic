void analogInit() {
  analyzer.setVolK(20);           // плавность громкости (0-31)
  analyzer.setTrsh(50);           // порог тишины
  analyzer.setVolMin(10);         // мин. громкость 10
  analyzer.setVolMax(255);        // макс. громкость 255
  analyzer.setDt(700);            // время между опросами АЦП
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
  changeTmr.reset();
  reload = 1;       // обновляем страницу
  EE_updateCfg();
}
void setMode(byte mode) {
  cfg.curPreset = constrain(mode, 0, cfg.presetAmount - 1);
  changeTmr.reset();
  reload = 1;
  EE_updateCfg();
}
bool dir = true;
void presetManager() {
  if (changeTmr.isReady()) {
    changeMode(1);
  }

  byte thisBright = cfg.bright;
  if (turnoffTmr.running()) _fade8(thisBright, dir ? turnoffTmr.getLength8() : 255 - turnoffTmr.getLength8());    // изменяем яркость при включении/выключении
  if (turnoffTmr.isReady()) {
    turnoffTmr.stop();
    if (!dir) setPower(0);     // выключаем
    return;
  }
  FastLED.setBrightness(thisBright);
}
void setState(bool state) {
  if (state == false) {
    dir = false;
    turnoffTmr.setInterval(1000);
    turnoffTmr.restart();
  }
  else {
    dir = true;
    turnoffTmr.setInterval(1000);
    turnoffTmr.restart();
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
