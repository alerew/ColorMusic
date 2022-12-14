#pragma once

#define MAX_PALETTES 9
DEFINE_GRADIENT_PALETTE(soundlevel_gp) {
  0,    0,    255,  0,  // green
  100,  255,  255,  0,  // yellow
  150,  255,  100,  0,  // orange
  200,  255,  50,   0,  // red
  255,  255,  0,    0   // red
};

CRGBPalette16 paletteArr[] = {
  HeatColors_p,             // тепло
  LavaColors_p,             // лава
  PartyColors_p,            // вечеринка
  RainbowColors_p,          // радуга
  RainbowStripeColors_p,    // павлин
  CloudColors_p,            // облака
  OceanColors_p,            // океан
  ForestColors_p,           // лес
  soundlevel_gp,
};
