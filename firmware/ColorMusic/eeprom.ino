#define EE_KEY 74
bool EEcfgFlag = false;
bool EEpresetFlag = false;

void EE_Init() {
  EEPROM.begin(1000);   // старт eeprom
  delay(100);
  if (EEPROM.read(0) != EE_KEY) {
    EEPROM.write(0, EE_KEY);
    EEPROM.put(1, cfg);
    EEPROM.put(sizeof(cfg) + 1, preset);
    EEPROM.commit();
  }
  EEPROM.get(1, cfg);
  EEPROM.get(sizeof(cfg) + 1, preset);

  changeTmr.setInterval(cfg.period * 1000L);    // меняем период автосмены режимов
  if (cfg.change) changeTmr.restart();
  else changeTmr.stop();      // отключаем автосмену
  
  MAX_CH = cfg.numLeds / 2;   // служебные переменные для эфектов
  indexL = (float)255 / MAX_CH;
}

void EE_updateCfg() {
  EEcfgFlag = true;
  EEtmr.restart();
}
void EE_updatePreset() {
  EEpresetFlag = true;
  EEtmr.restart();
}

void checkEEupdate() {
  if (EEtmr.isReady()) {
    EEupdate();   // обновление eeprom
    EEtmr.stop();
  }
}

void EEupdate() {
  if (EEcfgFlag || EEpresetFlag) {
    if (EEcfgFlag) {
      EEcfgFlag = false;
      EEPROM.put(1, cfg);   // пишем в eeprom
    }
    if (EEpresetFlag) {
      EEpresetFlag = false;
      EEPROM.put(sizeof(cfg) + 1, preset);   // пишем в eeprom
    }
    EEPROM.commit();
  }
}
void EEreset() {    // сброс настроек
  EEPROM.write(0, EE_KEY + 1);
  EEPROM.commit();
  blink16(CRGB::Red);
  ESP.restart();
}
