// C++ code
//

/*
PARTE 2 - LDR

Neste código, que incrementa a PARTE 1, temos a definição de um LDR, que será utilizado para indicar a luminosidade do ambiente.
*/


// Definindo nome para as portas digitais e analógicas
#define LED_VERM 4
#define LED_AMAR 5
#define LED_VERD 6
#define FOTORESISTOR A4

// Calibrando os sensores {valor_min, valor_max}
int intervalo_luminosidade[2] = {2, 404}; // Luminosidade

// Variáveis para armazenar o valor dos sensores
int luz_ambiente_a = 0;

void setup()
{
	pinMode(LED_VERM, OUTPUT);
	pinMode(LED_AMAR, OUTPUT);
	pinMode(LED_VERD, OUTPUT);
    Serial.begin(9600);
}

float map_A_P(int valor_analogico, int valor_min, int valor_max)
{
	/*
	Mapeamento de um valor analógico para porcentagem de acordo com o intervalo de valores.
	*/
	
	//float porcentagem = (float(umidade_a) / float(valor_max)) * 100.00; ou
	float porcentagem = map((valor_analogico), valor_min, valor_max, 0, 100);
	return porcentagem;
}

void loop()
{   
    digitalWrite(LED_VERM, HIGH);
    digitalWrite(LED_AMAR, HIGH);
    digitalWrite(LED_VERD, HIGH);

    // INICIO LEITURAS //
	Serial.println("------LEITURA------");

    luz_ambiente_a = analogRead(FOTORESISTOR);
	int luz_ambiente = map_A_P(luz_ambiente_a, intervalo_luminosidade[0], intervalo_luminosidade[1]);

	Serial.print("Iluminacao do Ambiente: ");
	Serial.print(luz_ambiente);
	Serial.println("%");
}
