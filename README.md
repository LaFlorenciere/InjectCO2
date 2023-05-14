# InjectCO2
Injecteur CO2 automatique


Modes de fonctionnement : 

Il existe six modes de fonctionnement que l'utilisateur peut sélectionner :

EV1 Partielle : Seule l'électrovanne 1 est activée à intervalles réguliers.

EV2 Partielle : Seule l'électrovanne 2 est activée à intervalles réguliers.

EV1&2 Partielle : Les deux électrovannes sont activées à intervalles réguliers.

EV1 Continu : L'électrovanne 1 est activée en continu.

EV2 Continu : L'électrovanne 2 est activée en continu.

EV1&2 Continu : Les deux électrovannes sont activées en continu.




Achats: 


- [ ] Electrovannes x 2:  https://www.amazon.fr/gp/product/B00DQ24GS6/ref=ppx_yo_dt_b_asin_title_o02_s01?ie=UTF8&psc=1
- [ ] Interrupteurs x3  https://www.amazon.fr/gp/product/B0817GT6CJ/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1
- [ ] Relais : https://www.amazon.fr/gp/product/B06XL1F53G/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1
- [ ] Ecran : https://www.amazon.fr/gp/product/B0725KXF99/ref=ppx_yo_dt_b_asin_title_o04_s01?ie=UTF8&psc=1
- [ ] Transformateur 12V https://www.amazon.fr/gp/product/B07BFDG42Z/ref=ppx_yo_dt_b_asin_title_o07_s01?ie=UTF8&psc=1
- [ ] Arduino Uno : https://www.amazon.fr/Elegoo-ATmega328P-ATMEGA16U2-Controller-Microcontrôleur/dp/B01N91PVIS/ref=sr_1_5?keywords=Arduino+uno&qid=1684084513&sr=8-5  ou mega 2560  https://www.amazon.fr/gp/product/B06XKZY117/ref=ppx_yo_dt_b_asin_title_o07_s01?ie=UTF8&psc=1
- [ ] Cable Dupont MF/MM/FF : https://www.amazon.fr/gp/product/B01JD5WCG2/ref=sw_img_1?smid=AZF7WYXU5ZANW&psc=1
- [ ] Diode axiales:  https://www.amazon.fr/BOJACK-redresseur-barrière-Schottky-axiales/dp/B07XZ3GF68/ref=sr_1_12?crid=1WETNE0DEN5J7&keywords=diode+de+roue+libre&qid=1684084720&sprefix=diode+de+roue+libre%2Caps%2C310&sr=8-12
- [ ] Adaptateur prise 12V : https://www.amazon.fr/gp/product/B0BR4S7J23/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
- [ ] Boitier armoire de contrôle : https://www.amazon.fr/gp/product/B07C7X9K5R/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1
- [ ] Encodeur rotatif KY-040 : https://www.amazon.fr/Taiss-Arduino-encodeur-rotatif-Capuchon/dp/B08ZKK4DGS/ref=sr_1_5?crid=G4NKUDSKXQ6M&keywords=encodeur+rotatif+ky-040&qid=1684084959&sprefix=KY-040+%2Caps%2C2204&sr=8-5



Montage

Carte Arduino : Vous aurez besoin d'une carte Arduino Mega 2560 pour ce projet.

Encodeur rotatif : C'est un dispositif de saisie qui peut être tourné dans les deux sens. Il a trois broches - CLK (ou A), DT (ou B) et SW (ou Button). Connectez la broche A à la broche 2 de l'Arduino Mega, la broche B à la broche 3 de l'Arduino Mega, et la broche Button à la broche 4. N'oubliez pas de connecter également la broche GND de l'encodeur à une broche GND de l'Arduino Mega.

Interrupteurs : Vous aurez besoin de deux interrupteurs pour contrôler les électrovannes. Connectez un côté de chaque interrupteur à une broche GND de l'Arduino Mega et l'autre côté respectivement aux broches A3 et A4 de l'Arduino Mega.

Électrovannes : Ces composants permettent de contrôler le débit d'un fluide. Connectez la broche positive (généralement rouge) de chaque électrovanne à une broche de sortie de l'Arduino Mega (9 et 10 respectivement), et la broche négative (généralement noire) à une broche GND de l'Arduino Mega. Selon la tension requise par vos électrovannes, vous pourriez avoir besoin d'un transistor et d'une diode de roue libre pour chaque électrovanne pour contrôler la haute tension à partir de la sortie de basse tension de l'Arduino Mega.

Écran LCD I2C : Pour l'Arduino Mega, connectez la broche SDA à la broche 20 (SDA) de l'Arduino, la broche SCL à la broche 21 (SCL), VCC à la broche 5V, et GND à une broche GND.

Bibliothèques Arduino : Vous aurez besoin des bibliothèques Wire, LiquidCrystal_I2C et RotaryEncoder. Vous pouvez les installer via le gestionnaire de bibliothèques de l'IDE Arduino. Allez dans Sketch > Include Library > Manage Libraries..., tapez le nom de la bibliothèque dans la barre de recherche, puis cliquez sur Install.

Code : Une fois que vous avez connecté tous les composants et installé les bibliothèques, vous pouvez télécharger le code, l'ouvrir dans l'IDE Arduino et le téléverser sur votre carte.
N'oubliez pas de vérifier les connexions et de vous assurer que tout est correctement alimenté avant de téléverser le code sur l'Arduino. Aussi, assurez-vous que les électrovannes sont compatibles avec votre source d'alimentation.
