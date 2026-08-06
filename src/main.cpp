#include "Arduino.h"
#include "OLED_Config.h" //precise le type d'afficheur OLED utilisé (SH1106 ou SSD1306)

//A ce stade on a #define OLED_SH1106   ou bien #define OLED_SSD1306
#include "AfficheurOLED.h" //la classe est définie

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

AfficheurOLED oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    Serial.begin(115200);
    Serial.println("Test Afficheur OLED");
    delay(2000);

    #if defined(OLED_SSD1306)

        // Wait for display
        delay(500);

        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
        {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ; // Don't proceed, loop forever
        }

    #elif defined(OLED_SH1106)
            oled.begin(0x3C, true);
    #endif

    //suite de la configuration de l'écran OLED
    delay(2000);
    oled.setTextColor(1);
}

void loop()
{
    Serial.print(".");
    oled.clearDisplay();
    oled.setTextSize(3);
    oled.setCursor(0, 0);
    oled.printf("Ok\n");
    oled.setTextSize(2);
    oled.printf("ok %d\n", 42);
    oled.setTextSize(1);
    oled.printf("ok %.2f\n", 12.345);
    oled.display();
    delay(2000);

    oled.clearDisplay();
    Serial.println("bonjour");
    oled.afficheMessageCentre("Bonjour");
    oled.display();
    delay(2000);
    
    
    oled.clearDisplay();
    oled.afficheDeuxLignesCentrees(
        "TEMP2lc",
        "12.5");
    oled.setTextSize(1);
    oled.print((char)247);
    oled.display();
    delay(2000);

    oled.clearDisplay();
    oled.afficheDeuxLignesTailles(2,"TEMP.",3,"100.5");
    oled.display();
    delay(2000);

    oled.clearDisplay();
    oled.afficherTexte(2, 0, 0,"HYGROM.");
    oled.afficherTexte(3, 0, 32, "%.1f%%", 45.5);
    oled.display();
    delay(2000);

    oled.clearDisplay();
    oled.afficherTexte(2, 64, 34, "HYGRO");
    oled.display();
    delay(2000);
}