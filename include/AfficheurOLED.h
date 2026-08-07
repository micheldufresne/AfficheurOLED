#pragma once

#include "OLED_Config.h"

#if defined(OLED_SSD1306)
  #include <Adafruit_SSD1306.h>
  using OLED_Base = Adafruit_SSD1306;

#elif defined(OLED_SH1106)

  #include <Adafruit_SH110X.h>
  using OLED_Base = Adafruit_SH1106G;

#else
  #error "Aucun type d'écran OLED défini"
#endif

class AfficheurOLED : public OLED_Base
{
  public:
    AfficheurOLED();

    bool begin();
    static constexpr uint16_t SH110X_WHITE = 1;
    void afficheMessageCentre(const char *message);
    void afficheMessageCentre(const char *message, const char *format, ...);
    void afficheDeuxLignesCentrees(const char *ligne1, const char *ligne2);
    void afficheDeuxLignesTailles(
        uint8_t taille1,
        const char *ligne1,
        uint8_t taille2,
        const char *ligne2);

    void afficherTexte(
        uint8_t taille,
        uint8_t x,
        uint8_t y,
        const char *format,
        ...);

    void printf(const char *format, ...);
};

/*
afficheMessageCentre("Mode");
afficheMessageCentre("Trappe", "%d", angle);
afficheMessageCentre("Temp", "%.1f", temperature);
afficheMessageCentre("Humidité", "%.0f %%", humidite);
afficheMessageCentre("Durée", "%02d:%02d", h, min);
afficherTexte(1, 0, 0,"HYGROMETRIE");
afficherTexte(2, 0, 45, "%.1f%",mesures.airEntree.humiditeRelative);
*/
