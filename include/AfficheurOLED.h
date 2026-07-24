#pragma once

#include <Arduino.h>
#include <Wire.h>
//message d'erreur à ignorer, ils disparaissent quand on appelle la bibliothèque
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

class AfficheurOLED
{
    private:
        static constexpr uint8_t SCREEN_WIDTH = 128;
        static constexpr uint8_t SCREEN_HEIGHT = 64;
        static constexpr int8_t OLED_RESET = -1;
        static constexpr uint8_t OLED_I2C_ADDRESS = 0x3C;
        Adafruit_SH1106G display;
        

    public:
        AfficheurOLED();

        void initialiser();

        void afficheMessageCentre(const char *message);
        void afficheMessageCentre(const char *message, const char *format, ...);
        void afficheDeuxLignesCentrees(const char *ligne1, const char *ligne2);

        void clear();

        void AfficheurOLED::afficherTexte(
            uint8_t taille,
            uint8_t x,
            uint8_t y,
            const char *texte)

        
        void setCursor(uint8_t x, uint8_t y);
        void setTextSize(uint8_t taille);
        void print(const char *texte);
        void afficher();
};

/*
afficheur.afficheMessageCentre("Mode");

afficheur.afficheMessageCentre("Trappe", "%d", angle);

afficheur.afficheMessageCentre("Temp", "%.1f", temperature);

afficheur.afficheMessageCentre("Humidité", "%.0f %%", humidite);

afficheur.afficheMessageCentre("Durée", "%02d:%02d", h, min);
*/
