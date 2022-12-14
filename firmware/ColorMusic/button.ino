#define CLICKS_TOUT 800

void buttonInit() {
#if (USE_BTN == 1)
  btn.setLevel(0);
  if (checkButton()) EEreset();
#endif
}

bool checkButton() {
#if (USE_BTN == 1)
  uint32_t tmr = millis();
  while (millis() - tmr < 2000) {
    btn.tick();
    if (btn.isHold()) return true;
  }
  return false;
#endif
}

void button() {
#if (USE_BTN == 1)
  static bool flag = 0, holdFlag = 0, brDir = 0;
  static Timer stepTmr(80, true);
  static uint32_t tmr = 0;
  static byte btnClicks = 0;

  btn.tick();

  if (btn.isClick()) {
    btnClicks++;
    tmr = millis();
  }

  if (btnClicks > 0 && millis() - tmr > CLICKS_TOUT) {
    switch (btnClicks) {
      case 1:
        setState(!cfg.state);   // включаем/выключаем
        break;
      case 2:
        changeMode(1);    // следующий режим
        break;
      case 3:
        changeMode(-1);   // предыдущий режим
        break;
      case 4:
        tryReconnect();
        break;
    }
    btnClicks = 0;
  }

  if (cfg.state && btn.isHold()) {    // кнопка зажата
    if (stepTmr.isReady()) {
      holdFlag = true;
      int temp = cfg.bright;
      temp += brDir ? 5 : -5;
      temp = constrain(temp, 0, 255);
      cfg.bright = temp;    // изменяем яркость
      FastLED.setBrightness(cfg.bright);
    }
  } else {
    if (holdFlag) {
      holdFlag = false;
      brDir = !brDir;
      EE_updateCfg();
    }
  }
#endif
}
