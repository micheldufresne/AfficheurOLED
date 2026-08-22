#include "AfficheurOLED.h"

AfficheurOLED::AfficheurOLED()
    : OLED_Base(128, 64, &Wire, -1)
{
}

bool AfficheurOLED::begin()
{
#if defined(OLED_SSD1306)
    return OLED_Base::begin(SSD1306_SWITCHCAPVCC, 0x3C);
#else
    return OLED_Base::begin(0x3C, true);
#endif
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
    clearDisplay();
    setTextSize(2);
 
    int16_t x1, y1;
    uint16_t w, h;

    if (ligne2 == nullptr)
    {
        getTextBounds(ligne1, 0, 0, &x1, &y1, &w, &h);

        setCursor((width() - w) / 2,
                          (height() - h) / 2);

        print(ligne1);
    }
    else
    {
        getTextBounds(ligne1, 0, 0, &x1, &y1, &w, &h);
        int x = (width() - w) / 2;

        const int hauteurLigne = 16; // police 8 px × taille 2
        const int espace = 4;

        const int hauteurTotale = hauteurLigne * 2 + espace;
        const int y1Pos = (height() - hauteurTotale) / 2;
        const int y2Pos = y1Pos + hauteurLigne + espace;

        setCursor(x, y1Pos);
        print(ligne1);

        getTextBounds(ligne2, 0, 0, &x1, &y1, &w, &h);
        x = (width() - w) / 2;

        setCursor(x, y2Pos);
        print(ligne2);
    }
    display();
}

void AfficheurOLED::afficheDeuxLignesTailles(
    uint8_t taille1,
    const char *ligne1,
    uint8_t taille2,
    const char *ligne2)
{
    clearDisplay();
    setTextSize(taille1);
    int16_t x1, y1;
    uint16_t w, h;
    int16_t SCREEN_WIDTH = width();
    getTextBounds(ligne1, 0, 0, &x1, &y1, &w, &h);
    setCursor((SCREEN_WIDTH - w) / 2,0);
    println(ligne1);

    setTextSize(taille2);
    getTextBounds(ligne2, 0, 0, &x1, &y1, &w, &h);
    setCursor((SCREEN_WIDTH - w) / 2, 32);
    println(ligne2);
    display();
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

    setTextSize(taille);
    setCursor(x, y);
    print(buffer);
}
// exemple : oled.afficherTexte(2, 0, 0, "Température : %.1f°", temperature);
// ou bien : oled.afficherTexte(1, 0, 16, "Puissance : %d W", puissance);
// ou encore : oled.afficherTexte(1, 0, 32, "Mode : %s", mode == AUTO ? "Auto" : "Manuel");
// ne pas oublier de faire un oled.flush() pour afficher le texte sur l'écran

void AfficheurOLED::printf(const char *format, ...)
{
    char buffer[64];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    print(buffer);
}
