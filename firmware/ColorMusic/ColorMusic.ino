// ------------ НАСТОРЙКИ ------------
#define USE_BTN 1         // 1 использовать кнопку, 0 нет
#define BTN_PIN 4         // кнопка на D2
#define STRIP_PIN 2       // D4 пин подключения ленты
#define MAX_LEDS 300      // максимальное количество светодиодов
#define MAX_PRESETS 20    // максимальное количество режимов

// ------------ WiFi AP ------------
const char AP_NameChar[] = "Color Music";
const char WiFiPassword[] = "12345678";

// ---------- БИБЛИОТЕКИ -----------
#include <VolAnalyzer.h>
#include <EEPROM.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <GyverPortal.h>
#include "data.h"
#include "Button.h"
#include "Timer.h"
#include "palletes.h"

// ------------------- ДАТА --------------------
CRGB leds[MAX_LEDS];
GyverPortal portal;
VolAnalyzer analyzer(A0);     // вход звука на А0
Button btn(BTN_PIN);          // кнопка
Timer effTmr(30, true);       // таймер эфектов
Timer rainbowTmr(30, true);   // таймер градиента
Timer EEtmr(10000, true);     // таймер eeprom
Timer changeTmr;              // таймер смены режимов
Timer connTmr(120000);        // таймер переподключения сети
Timer turnoffTmr;             // таймер выключения
Preset preset[MAX_PRESETS];
Config cfg;

void setup() {
  Serial.begin(9600);
  EE_Init();      // старт eeprom
  stripInit();    // старт ленты
  buttonInit();   // старт кнопки
  WiFiInit();     // старт wifi
  analogInit();   // старт микрофона
}

void loop() {
  WiFiRoutine();      // обновляем страницу
  yield();
  tryReconnect();     // переподключаемся если wifi не подключился
  yield();
  button();           // проверяем кнопку
  yield();
  presetManager();    // крутим эффекты
  yield();
  effectsRountine();  // эффекты
  yield();
  checkEEupdate();    // проверяем eeprom
}
