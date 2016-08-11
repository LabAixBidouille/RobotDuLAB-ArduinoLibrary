/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software< /span>
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ROBOTDULAB_H_
#define _ROBOTDULAB_H_

#if ARDUINO >= 100
    #include "Arduino.h"
    #include "Print.h"
#else
    #include "WProgram.h"
#endif

#include <Servo.h>
#include <Adafruit_NeoPixel.h>

/** Constants */

/** Couleurs */
typedef enum
{
    NOIR     = (0), 
    ROUGE    = (1), 
    VERT     = (2), 
    MAGENTA  = (3), 
    BLEU     = (4), 
    BLANC    = (5), 
    TURQUOISE= (6), 
    JAUNE    = (7), 
    VIOLET   = (8), 
} couleur_index_t;

uint32_t couleurs[] = {
    Adafruit_NeoPixel::Color(0, 0, 0),
    Adafruit_NeoPixel::Color(255, 0, 0),
    Adafruit_NeoPixel::Color(0, 255, 0),
    Adafruit_NeoPixel::Color(139, 0, 139),
    Adafruit_NeoPixel::Color(0, 0, 255),
    Adafruit_NeoPixel::Color(127, 127, 127),
    Adafruit_NeoPixel::Color(0, 245, 255),
    Adafruit_NeoPixel::Color(255, 215, 0),
    Adafruit_NeoPixel::Color(208, 32, 114),
};

/** Sens de rotation servomoteur */
typedef enum
{
    INVERSE = (0),
    ARRET = (90),
    NORMAL = (180),
} sens_rotation_t;

/** Gestion de l'anneau de LED */

const int NB_LED = 16;

typedef enum
{
    COULEUR = (1),
    ARC_EN_CIEL = (2),
    ARC_EN_CIEL_CYCLIQUE = (3),
    COULEUR_CYCLIQUE = (4),
} choix_animation_anneau_led_t;


 
class RobotDuLAB {
        const int triggerPin; // broche trig du capteur US HC-SR04
        const int echoPin; // broche echo du capteur US HC-SR04
        const int roueDroitePin; 
        const int roueGauchePin;
        const int anneauDeLedPin;

        Servo roueDroite;
        Servo roueGauche;

        Adafruit_NeoPixel anneauDeLed;

    public:

        // Constructor(s)
        RobotDuLAB(const int triggerPin, const int echoPin, const int roueDroitePin, 
                    const int roueGauchePin, const int anneauDeLedPin):triggerPin(triggerPin), 
                                                                        echoPin(echoPin),
                                                                        roueDroitePin(roueDroitePin),
                                                                        roueGauchePin(roueGauchePin),
                                                                        anneauDeLedPin(anneauDeLedPin),
                                                                        roueDroite(), 
                                                                        roueGauche(), 
                                                                        anneauDeLed(NB_LED, anneauDeLedPin, NEO_GRB + NEO_KHZ800) {

        }

        virtual ~RobotDuLAB() {}

        void begin(){
            // Initialisation du HC-SR04
            pinMode (triggerPin,OUTPUT); 
            digitalWrite(triggerPin, LOW); 
            pinMode(echoPin, INPUT);
            delay(100);

            //Initialisation Anneau de LED     
            anneauDeLed.begin();
            delay(100);
            eteindreAnneauDeLed();
            
        }

        void Arreter() {
            MettreEnMouvement(ARRET, ARRET);
        }

        void Avancer() {       
            MettreEnMouvement(NORMAL, INVERSE);
        }

        void Reculer() {
            MettreEnMouvement(INVERSE, NORMAL);
        }

        void TournerAGauche() {
            MettreEnMouvement(NORMAL, NORMAL);
        }

        void TournerADroite() {
            MettreEnMouvement(INVERSE, INVERSE);
        }

        void AnimerAnneauLed(choix_animation_anneau_led_t choix, couleur_index_t couleur){
            roueGauche.detach();
            roueDroite.detach();
            switch (choix){
                case COULEUR :
                    anneauDeLed.setPixelColor(14, couleurs[couleur]);
                    anneauDeLed.setPixelColor(15, couleurs[couleur]);
                    anneauDeLed.setPixelColor(0, couleurs[couleur]);
                    break;
                case ARC_EN_CIEL :
                    rainbow(20);
                    break;
                case ARC_EN_CIEL_CYCLIQUE :
                    rainbowCycle(20);
                    break;
                case COULEUR_CYCLIQUE :
                    theaterChase(couleurs[couleur], 50);
                    break;
            }
            anneauDeLed.show();
        }

        long getDistanceObstacle(){
            digitalWrite(triggerPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(triggerPin, LOW);

            long duree_echo = pulseIn(echoPin, HIGH);
            return microsecondsEnCentimetres(duree_echo);
        }

    private:
        void MettreEnMouvement(sens_rotation_t sensRoueDroite, sens_rotation_t sensRoueGauche) {
            if(!roueDroite.attached())
                roueDroite.attach(roueDroitePin);
            if(!roueGauche.attached())
                roueGauche.attach(roueGauchePin);

            roueDroite.write(sensRoueDroite);
            roueGauche.write(sensRoueGauche);
        }

        void eteindreAnneauDeLed(){
            for (int i = 0; i < NB_LED; ++i)
            {
                anneauDeLed.setPixelColor(i, couleurs[NOIR]);
            }
            anneauDeLed.show();
            
        }

        long microsecondsEnCentimetres(long microseconds)
        {
            // The speed of sound is 340 m/s or 29 microseconds per centimeter.
            // The ping travels out and back, so to find the distance of the
            // object we take half of the distance travelled.
            return microseconds / 29 / 2;
        }

        // Fill the dots one after the other with a color
        void colorWipe(uint32_t c, uint8_t wait) {
            for(uint16_t i=0; i<anneauDeLed.numPixels(); i++) {
                anneauDeLed.setPixelColor(i, c);
                anneauDeLed.show();
                delay(wait);
            }
        }

        void rainbow(uint8_t wait) {
            uint16_t i, j;

            for(j=0; j<256; j++) {
                for(i=0; i<anneauDeLed.numPixels(); i++) {
                    anneauDeLed.setPixelColor(i, Wheel((i+j) & 255));
                }
                anneauDeLed.show();
                delay(wait);
            }
        }

        // Slightly different, this makes the rainbow equally distributed throughout
        void rainbowCycle(uint8_t wait) {
            uint16_t i, j;

            for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
                for(i=0; i< anneauDeLed.numPixels(); i++) {
                    anneauDeLed.setPixelColor(i, Wheel(((i * 256 / anneauDeLed.numPixels()) + j) & 255));
                }
                anneauDeLed.show();
                delay(wait);
            }
        }

        //Theatre-style crawling lights.
        void theaterChase(uint32_t c, uint8_t wait) {
            for (int j=0; j<10; j++) {  //do 10 cycles of chasing
                for (int q=0; q < 3; q++) {
                    for (uint16_t i=0; i < anneauDeLed.numPixels(); i=i+3) {
                        anneauDeLed.setPixelColor(i+q, c);    //turn every third pixel on
                    }
                    anneauDeLed.show();

                    delay(wait);

                    for (uint16_t i=0; i < anneauDeLed.numPixels(); i=i+3) {
                        anneauDeLed.setPixelColor(i+q, 0);        //turn every third pixel off
                    }
                }
            }
        }

        //Theatre-style crawling lights with rainbow effect
        void theaterChaseRainbow(uint8_t wait) {
            for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
                for (int q=0; q < 3; q++) {
                    for (uint16_t i=0; i < anneauDeLed.numPixels(); i=i+3) {
                        anneauDeLed.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
                    }
                    anneauDeLed.show();

                    delay(wait);

                    for (uint16_t i=0; i < anneauDeLed.numPixels(); i=i+3) {
                        anneauDeLed.setPixelColor(i+q, 0);        //turn every third pixel off
                    }
                }
            }
        }

        // Input a value 0 to 255 to get a color value.
        // The colours are a transition r - g - b - back to r.
        uint32_t Wheel(byte WheelPos) {
            WheelPos = 255 - WheelPos;
            if(WheelPos < 85) {
                return anneauDeLed.Color(255 - WheelPos * 3, 0, WheelPos * 3);
            }
            if(WheelPos < 170) {
                WheelPos -= 85;
                return anneauDeLed.Color(0, WheelPos * 3, 255 - WheelPos * 3);
            }
            WheelPos -= 170;
            return anneauDeLed.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
};

#endif /* _ROBOTDULAB_H_ */
