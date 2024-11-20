// C++ code
//

/* 
PARTE 1 - LEDS

Neste código, temos a definição de três LEDs, que serão utilizados para indicar o estado do solo e do ambiente.
*/

// Definindo nome para as portas digitais e analógicas
#define LED_VERM 4
#define LED_AMAR 5
#define LED_VERD 6

void setup()
{
	pinMode(LED_VERM, OUTPUT);
	pinMode(LED_AMAR, OUTPUT);
	pinMode(LED_VERD, OUTPUT);
}

void loop()
{
    digitalWrite(LED_VERM, HIGH);
    digitalWrite(LED_AMAR, HIGH);
    digitalWrite(LED_VERD, HIGH);
}