#include <RobotDuLAB.h>
#define TRIGGER_PIN 2 // broche trig du capteur US HC-SR04
#define ECHO_PIN 4 // broche echo du capteur US HC-SR04
#define ROUE_DROITE_PIN 5
#define ROUE_GAUCHE_PIN 3
#define ANNEAU_LED_PIN 6

RobotDuLAB robotDuLAB(TRIGGER_PIN, ECHO_PIN, ROUE_DROITE_PIN, ROUE_GAUCHE_PIN, ANNEAU_LED_PIN);

void setup()
{
  	robotDuLAB.begin();
}


void loop()
{
	robotDuLAB.AnimerAnneauLed(COULEUR,VERT);
	delay(1000);
	robotDuLAB.AnimerAnneauLed(ARC_EN_CIEL,VERT);
	delay(1000);
	robotDuLAB.AnimerAnneauLed(ARC_EN_CIEL_CYCLIQUE);
	delay(1000);
	robotDuLAB.AnimerAnneauLed(COULEUR_CYCLIQUE,VERT);
	delay(1000);
}