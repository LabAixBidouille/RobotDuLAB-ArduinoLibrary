#Bibliothèque Arduino pour RobotDuLAB
Bibliothèque arduino de pilotage de RobotDuLAB. RobotDuLAB est un robot simple, économique et open source pour apprendre à programmer en classe.

## Présentation de RobotDuLAB

Un robot pour apprendre à programmer aux enfants : 

- Utilisable en écoles primaires, collèges et lycées
- Toutes les pièces mécaniques sont imprimables (impression 3D – fichiers .stl fournis) 
- Partie électronique basée sur une carte de prototypage « arduino » 
- Libre (copiable, modifiable) et évolutif (de nombreuses options possibles)
   
RoboduLAB, permet une approche ludique de l’apprentissage du code à l’école primaire, des plots au format lego permettent de personnaliser le robot. En collège et en lycée RoboduLAB est un support de thème très riche pour le travail en équipes projets : conception, réalisation, expérimentation. 

La programmation se fait par assemblage de blocs (type scratch). Le programme se télécharge directement dans le robot depuis le PC ou la tablette en WIFI.
## Installation
Pour installer la bibliothèque, il suffit de télécharger l'archive et de la décompresser dans le dossier `library` d'Arduino.

## Utilisation de la bibliothèque
La bibliothèque à pour objectif de simplifier au maximum la programmation de RobotDuLAB. Elle possède donc un nombre d'instruction volontairement limité. L'accent a particulièrement été mis sur l'expréssivité du code.

Pour utiliser la bibliothèque, il suffit d'inclure le fichier `RobotDuLAB.h`, de créer un objet du type `RobotDuLAB` et d'utiliser ses différentes méthodes.

Voici un exemple permettant de programmer le robot pour qu'il évite les obstacles :
```cpp
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
  robotDuLAB.Avancer();
  if (robotDuLAB.getDistance() < 10)
  {
    robotDuLAB.TournerAGauche()
    delay(1000);
  }
  delay(1000);
}
```

## Releases
### 0.0.1 - Aug 8, 2016
* release initiale