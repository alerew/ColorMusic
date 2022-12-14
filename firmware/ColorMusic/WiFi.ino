void WiFiRoutine() {
  portal.tick();
}

void WiFiInit() {
  if (!cfg.WiFimode) setupAP();   // режим точки доступа
  else setupLocal();              // подключаемся к точке

  portal.attachBuild(build);
  portal.attach(action);
  portal.start();
}

void setupAP() {
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAP(AP_NameChar, WiFiPassword);    // создаём точку доступа
  delay(500);
}

void setupLocal() {
  if (cfg.ssid[0] == NULL && cfg.pass[0] == NULL) {
    setupAP();
  } else {
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    uint32_t tmr = millis();
    bool connect = false;
    byte failCount = 0;
    while (1) {
      WiFi.begin(cfg.ssid, cfg.pass);   // пытаемся подключиться к роутеру
      while (millis() - tmr < 10000) {
        if (WiFi.status() == WL_CONNECTED) {  // подключились
          connect = true;
          break;
        }
        delay(50);
      }
      if (connect) {
        connTmr.stop();
        return;
      } else {
        failCount++;
        tmr = millis();
        if (failCount >= 3) {     // не получилось подключиться
          connTmr.restart();
          setupAP();
          return;
        }
      }
    }
  }
  delay(500);
}
void tryReconnect() {
  if (connTmr.isReady()) {
    portal.stop();
    WiFiInit();
  }
}
