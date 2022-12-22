void build() {
  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);
  //GP.THEME(GP_LIGHT);
  GP.UPDATE("rel,st,br,mode,eff,pal");

  GP.RELOAD("rel");

  GP.TITLE("Color Music");
  GP.HR();

  GP.NAV_TABS("Главная,WiFi,Настройки");
  GP.HR();

  // =================================== ГЛАВНАЯ ===================================
  M_NAV_BLOCK(
    M_BLOCK_TAB(
      "Питание",
      GP.SWITCH("st", cfg.state);
      GP.HR();
      GP.LABEL("Яркость");
      GP.SLIDER("br", cfg.bright, 0, 255);
    )

    M_BLOCK_TAB(
      "Режимы",
      GP.NUMBER("mode", "", cfg.curPreset + 1);
      GP.BUTTON("prev", "Предыдущий");
      GP.BUTTON("next", "Следующий");
    )

    M_BLOCK_TAB(
      "Настройка режима",
      GP.LABEL("Эффект");
      GP.BREAK();
      GP.SELECT("eff", effectNames, CUR_PRES.effect);
      GP.HR();
      settingModeBuild();
    )
  );

  // =================================== WIFI ===================================
  M_NAV_BLOCK(
    M_BLOCK(
      GP.FORM_BEGIN("/wifi");
      GP.TEXT("ssid", "SSID", cfg.ssid);
      GP.BREAK();
      GP.PASS("pass", "Password", cfg.pass);
      GP.SUBMIT("Сохранить");
      GP.FORM_END();
    );
  );

  // =================================== НАСТРОЙКИ ===================================
  M_NAV_BLOCK(
    M_BLOCK(
      GP.LABEL("Количество режимов");
      GP.SLIDER("am", cfg.presetAmount, 1, MAX_PRESETS);
      GP.HR();
      GP.LABEL("Автосмена режимов");
      GP.BREAK();
      GP.SWITCH("cn", cfg.change);
      GP.HR();
      GP.LABEL("Период смены режимов");
      GP.SLIDER("prd", cfg.period, 30, 300);
    );
    M_BLOCK(
      GP.LABEL("Количество светодиодов");
      GP.NUMBER("leds", "", cfg.numLeds);
      GP.HR();
      GP.LABEL("Лимит по току");
      GP.SLIDER("lm", cfg.limit, 500, 3000);
    );
    M_BLOCK(
      GP.LABEL("Для применения некоторых");
      GP.BREAK();
      GP.LABEL("настроек требуется перезагрузка!");
      GP.BUTTON("rst", "Перезагрузка");
      GP.BUTTON("clr", "Сброс настроек");
    );
    GP.BUTTON_MINI_LINK("https://github.com/alerew/ColorMusic", "О проекте");
  );

  GP.BUILD_END();
}

void settingModeBuild() {
  if (CUR_PRES.effect == 1) {
    GP.LABEL("Палитра");
    GP.BREAK();
    GP.SELECT("pal", palleteNames, CUR_PRES.pallete);
    GP.HR();
    GP.LABEL("Скорость");
    GP.BREAK();
    GP.SLIDER("spd", CUR_PRES.speed, 0, 255);
  }
  else if (CUR_PRES.effect == 3) {
    GP.LABEL("Палитра");
    GP.BREAK();
    GP.SELECT("pal", palleteNames, CUR_PRES.pallete);
    GP.HR();
    GP.LABEL("Перлин");
    GP.BREAK();
    GP.SWITCH("per", CUR_PRES.flag);
    GP.HR();
    GP.LABEL("Скорость");
    GP.BREAK();
    GP.SLIDER("spd", CUR_PRES.speed, 0, 255);
    GP.HR();
    GP.LABEL("Масштаб");
    GP.BREAK();
    GP.SLIDER("scl", CUR_PRES.scale, 0, 255);
  }
  else if(CUR_PRES.effect == 4){
    GP.LABEL("Цвет");
    GP.BREAK();
    GP.SLIDER("pal", CUR_PRES.pallete, 0, 255);
  }
  else {
    GP.LABEL("Шаг изменения цвета");
    GP.BREAK();
    GP.SELECT("pal", stepNames, CUR_PRES.pallete);
  }
}
