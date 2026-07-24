#include "AfficheurOLED.h"

AfficheurOLED::AfficheurOLED()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
}

void AfficheurOLED::initialiser()
{
    if (!display.begin(OLED_I2C_ADDRESS, true))
    {
        Serial.println("Écran SH1106 non détecté !");
        while (1)
            ;
    }
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
}

void AfficheurOLED::afficheMessageCentre(const char *message,
                                             const char *format,
                                             ...)
{
    char valeur[32];

    va_list args;
    va_start(args, format);
    vsnprintf(valeur, sizeof(valeur), format, args);
    va_end(args);

    afficheDeuxLignesCentrees(message, valeur);
}

void AfficheurOLED::afficheMessageCentre(const char *message)
{
    afficheDeuxLignesCentrees(message, nullptr);
}

void AfficheurOLED::afficheDeuxLignesCentrees(const char *ligne1,
                                              const char *ligne2)
{
    display.clearDisplay();
    display.setTextSize(2);
 
    int16_t x1, y1;
    uint16_t w, h;

    if (ligne2 == nullptr)
    {
        display.getTextBounds(ligne1, 0, 0, &x1, &y1, &w, &h);

        display.setCursor((display.width() - w) / 2,
                          (display.height() - h) / 2);

        display.print(ligne1);
    }
    else
    {
        display.getTextBounds(ligne1, 0, 0, &x1, &y1, &w, &h);
        int x = (display.width() - w) / 2;

        const int hauteurLigne = 16; // police 8 px × taille 2
        const int espace = 4;

        const int hauteurTotale = hauteurLigne * 2 + espace;
        const int y1Pos = (display.height() - hauteurTotale) / 2;
        const int y2Pos = y1Pos + hauteurLigne + espace;

        display.setCursor(x, y1Pos);
        display.print(ligne1);

        display.getTextBounds(ligne2, 0, 0, &x1, &y1, &w, &h);
        x = (display.width() - w) / 2;

        display.setCursor(x, y2Pos);
        display.print(ligne2);
    }

    display.display();
}


void AfficheurOLED::clear()
{
    display.clearDisplay();
    display.display();
}

void AfficheurOLED::afficherTexte(
    uint8_t taille,
    uint8_t x,
    uint8_t y,
    const char *format,
    ...)
{
    char buffer[32];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    display.setTextSize(taille);
    display.setCursor(x, y);
    display.print(buffer);
}
// exemple : oled.afficherTexte(2, 0, 0, "Température : %.1f°", temperature);
// ou bien : oled.afficherTexte(1, 0, 16, "Puissance : %d W", puissance);
// ou encore : oled.afficherTexte(1, 0, 32, "Mode : %s", mode == AUTO ? "Auto" : "Manuel");

void AfficheurOLED::setCursor(uint8_t x, uint8_t y)
{
    display.setCursor(x, y);
}

void AfficheurOLED::setTextSize(uint8_t taille)
{
    display.setTextSize(taille);
}

void AfficheurOLED::print(
    const char *texte,
    ...)
{
    char buffer[32];

    va_list args;
    va_start(args, texte);
    vsnprintf(buffer, sizeof(buffer), texte, args);
    va_end(args);

    display.print(buffer);
}

void AfficheurOLED::println(const char *texte, ...)
{
    char buffer[32];

    va_list args;
    va_start(args, texte);
    vsnprintf(buffer, sizeof(buffer), texte, args);
    va_end(args);

    display.println(buffer);
}

void AfficheurOLED::drawLine(uint8_t xd, uint8_t yd, uint8_t xf, uint8_t yf)
{
    display.drawLine(xd,yd,xf,yf,SH110X_WHITE);
}

void AfficheurOLED::flush()
{
    display.display();
}