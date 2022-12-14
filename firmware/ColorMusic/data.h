#define CUR_PRES preset[cfg.curPreset]    // текущий режим
#define CUR_PAL paletteArr[CUR_PRES.pallete]    // текущая палитра

// служебные переменные для эффектов
int MAX_CH = 50;    // cfg.numLeds / 2
float indexL = (float)255 / MAX_CH;

struct Preset {
  byte effect = 0;    // тип эфекта
  byte pallete = 0;   // палитра
  byte scale = 100;   // масштаб
  byte speed = 30;    // скорость эфекта
  byte color = 0;     // цвет
  byte flag = 0;
};

struct Config {
  byte state = 1;         // вкл/выкл
  int8_t curPreset = 0;   // текущий режим
  int numLeds = 100;      // количество светодиодов
  byte bright = 255;      // яркость
  int limit = 1500;       // ограничение по току
  byte presetAmount = 5;  // количество режимов
  byte change = 1;        // автосмена режимов
  byte period = 60;       // период автосмены
  byte WiFimode = 0;      // 0 AP, 1 local
  char ssid[32] = "Color Music";  // логин wifi
  char pass[32] = "";     // пароль wifi
};

byte reload = 0;    // перезагрузка страницы

byte steps[3] = {151, 129, 1};

char *effectNames = "Резкая смена цвета,Столбик громкости,Бегущие огни,Градиент";
char *palleteNames = "Тепло,Лава,Вечеринка,Радуга,Павлин,Облака,Океан,Лес,Sound level";
char *stepNames = "151,129,1 (Огненная палитра)";
