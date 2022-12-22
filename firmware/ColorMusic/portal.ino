void action() {
  // =================================== CLICK ===================================
  if (portal.click()) {
    if (portal.click("st")) {
      setState(portal.getBool("st"));
    }
    if (portal.click("mode")) {
      setMode(portal.getInt("mode") - 1);
    }
    if (portal.click("next")) {
      changeMode(1);
    }
    if (portal.click("prev")) {
      changeMode(-1);
    }
    if (portal.click("br")) {
      cfg.bright = portal.getInt("br");
      FastLED.setBrightness(cfg.bright);
      EE_updateCfg();
    }
    if (portal.click("eff")) {
      CUR_PRES.effect = portal.getInt("eff");
      if (CUR_PRES.effect == 0 || CUR_PRES.effect == 2) CUR_PRES.pallete = constrain(CUR_PRES.pallete, 0, 3);
      else if (CUR_PRES.effect == 1 || CUR_PRES.effect == 3) CUR_PRES.pallete = constrain(CUR_PRES.pallete, 0, MAX_PALETTES - 1);
      if (CUR_PRES.effect == 1) CUR_PRES.scale = 0;
      reload = 1;
      EE_updatePreset();
    }
    if (portal.click("per")) {
      CUR_PRES.flag = portal.getBool("per");
      EE_updatePreset();
    }
    if (portal.click("pal")) {
      CUR_PRES.pallete = portal.getInt("pal");
      EE_updatePreset();
    }
    if (portal.click("spd")) {
      CUR_PRES.speed = portal.getInt("spd");
      EE_updatePreset();
    }
    if (portal.click("scl")) {
      CUR_PRES.scale = portal.getInt("scl");
      EE_updatePreset();
    }
    if (portal.click("cn")) {
      cfg.change = portal.getInt("cn");
      if (cfg.change) changeTmr.restart();
      else changeTmr.stop();
      EE_updateCfg();
    }
    if (portal.click("prd")) {
      cfg.period = portal.getInt("prd");
      changeTmr.setInterval(cfg.period * 1000L);
      EE_updateCfg();
    }
    if (portal.click("am")) {
      cfg.presetAmount = portal.getInt("am");
      MAX_CH = cfg.numLeds / 2;
      EE_updateCfg();
    }
    if (portal.click("lm")) {
      cfg.limit = portal.getInt("lm");
      EE_updateCfg();
    }
    if (portal.click("leds")) {
      cfg.numLeds = constrain(portal.getInt("leds"), 10, MAX_LEDS);
      EE_updateCfg();
    }
    if (portal.click("rst")) {
      EEupdate();
      ESP.restart();
    }
    if (portal.click("clr")) {
      EEreset();
    }
  }

  // =================================== UPDATE ===================================
  if (portal.update()) {
    if (portal.update("st")) portal.answer(cfg.state && dir);
    if (portal.update("br")) portal.answer(cfg.bright);
    if (portal.update("mode")) portal.answer(cfg.curPreset + 1);
    if (portal.update("eff")) portal.answer(CUR_PRES.effect);
    if (portal.update("pal")) portal.answer(CUR_PRES.pallete);
    if (portal.update("rel")) {
      portal.answer(reload);
      reload = 0;
    }
  }

  // =================================== FORM ===================================
  if (portal.form()) {
    if (portal.form("/wifi")) {
      portal.copyStr("ssid", cfg.ssid);
      portal.copyStr("pass", cfg.pass);
      portal.stop();
      EEPROM.put(1, cfg);
      EEPROM.commit();
      ESP.restart();
    }
  }
}
