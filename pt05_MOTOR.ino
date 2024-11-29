// C++ code
//

/*
PARTE 5 - MOTOR

Neste código, que incrementa a PARTE 4, temos a definição de um motor, que será utilizado para simular a aplicação de um produto no solo.
*/

// Definindo nome para as portas digitais e analógicas
#define LED_VERM 4
#define LED_AMAR 5
#define LED_VERD 6
#define FOTORESISTOR A4
#define TEMP_SOLO A1
#define TEMP_AMBIENTE A2
#define UMIDADE_AMBIENTE A3
#define UMIDADE_SOLO A0
#define MOTOR 2

// Calibrando os sensores {valor_min, valor_max}
int intervalo_luminosidade[2] = {2, 404}; // Luminosidade
int intervalo_umidade_ambiente[2] = {0, 1023}; // Umidade Ambiente
int intervalo_temperatura_solo[2] = {0, 1023}; // Temperatura Solo
int intervalo_temperatura_ambiente[2] = {0, 1023}; // Temperatura Ambiente
int intervalo_umidade_solo[2] = {330, 1023}; // Umidade Solo

// Variáveis para armazenar o valor dos sensores
int luz_ambiente_a = 0;
int temp_solo_a = 0;
int umidade_ambiente_a= 0;
int temp_ambiente_a = 0;
int umidade_solo_a = 0;

// Variáveis relacionadas ao tempo de delay
int const PAUSA_ENTRE_APLICACAO = 20000; // 43.200.000 ms ou 12 horas
int const TEMPO_MOTOR_LIGADO = 5000;
int const PAUSA_ENTRE_LEITURA = 10000; // 600.000 ms ou 10 minutos

void setup()
{
	pinMode(LED_VERM, OUTPUT);
	pinMode(LED_AMAR, OUTPUT);
	pinMode(LED_VERD, OUTPUT);
    	pinMode(MOTOR, OUTPUT);
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

float map_A_P_hig(int valor_analogico, int valor_min, int valor_max)
{
	/*
	Mapeamento de um valor analógico para porcentagem do higrômetrto de acordo com o intervalo de valores.
	*/
	
	float porcentagem = map((valor_analogico), valor_max, valor_min, 100, 0);
	return porcentagem;
}

int map_A_G(int valor_analogico, int valor_min, int valor_max)
{
	/*
	Mapeamento de um valor analógico para graus celsius de acordo com o intervalo de valores.
	*/
	
	int temp = map((valor_analogico), valor_min, valor_max, -40, 125);
	return temp; 
}

void loop()
{   
   	 // INICIO LEITURAS //
	Serial.println("------LEITURA------");

    	// -> Medições em relação ao SOLO
	
	temp_solo_a = analogRead(TEMP_SOLO);
	int temp_solo = map_A_G(temp_solo_a, intervalo_temperatura_solo[0], intervalo_temperatura_solo[1]);
		
	Serial.print("Temperatura do Solo: ");
	Serial.print(temp_solo);
	Serial.println(" C");

	umidade_solo_a = analogRead(UMIDADE_SOLO);
	int umidade_solo = map_A_P_hig(umidade_solo_a, intervalo_umidade_solo[1], intervalo_umidade_solo[0]);
		
	Serial.print("Umidade Solo: ");
	Serial.print(umidade_solo);
	Serial.println("%");
	
	// -> Medições em relação ao AMBIENTE

    	luz_ambiente_a = analogRead(FOTORESISTOR);
	int luz_ambiente = map_A_P(luz_ambiente_a, intervalo_luminosidade[0], intervalo_luminosidade[1]);

	Serial.print("Iluminacao do Ambiente: ");
	Serial.print(luz_ambiente);
	Serial.println("%");

    	umidade_ambiente_a = analogRead(UMIDADE_AMBIENTE);
	int umidade_ambiente = map_A_P(umidade_ambiente_a, intervalo_umidade_ambiente[0], intervalo_umidade_ambiente[1]);
	
	Serial.print("Umidade Ambiente: ");
	Serial.print(umidade_ambiente);
	Serial.println("%");
	
	temp_ambiente_a = analogRead(TEMP_AMBIENTE);
	int temp_ambiente = map_A_G(temp_ambiente_a, intervalo_temperatura_ambiente[0], intervalo_temperatura_solo[1]);
		
	Serial.print("Temperatura do Ambiente: ");
	Serial.print(temp_ambiente);
	Serial.println(" C");

    	// INICIO REGRA DE NEGÓCIO //
	Serial.println("------RESULTADO LEITURAS------");
	
	// -> Verifica se o solo está propricio para nematoides
	bool UMIDADE_PROPRICIA_PARA_NEMATOIDES = (umidade_solo <= 20 || umidade_solo >= 80);
	bool TEMPERATURA_PROPRICIA_PARA_NEMATOIDES = (temp_solo <= 15 || temp_solo >= 35);
		
	bool SOLO_PROPICIO__PARA_NEMATOIDES = (UMIDADE_PROPRICIA_NEMATOIDES && TEMPERATURA_PROPRICIA_NEMATOIDES);

	if (SOLO_PROPICIO_NEMATOIDES)
	{	
		// -> Ajustando LEDs de feedback
		digitalWrite(LED_VERM, LOW);
		digitalWrite(LED_AMAR, HIGH);
		digitalWrite(LED_VERD, LOW);
	
		Serial.println("O SOLO ESTA PROPICIO PARA NEMATOIDES! Verificando condicoes do ambiente...");
	
		// -> Verifica se o ambiente está adequado para aplicacao
	
		bool UMIDADE_BOA_PARA_APLICACAO = (umidade_ambiente >= 55 || umidade_ambiente <= 90);
		bool TEMP_BOA_PARA_APLICACAO = (temp_ambiente <= 30);
		bool ILUMINACAO_BOA_PARA_APLICACAO = (luz_ambiente <= 70); // Representando muito sol

		bool AMBIENTE_PROPICIO_PARA_APLICACAO = (UMIDADE_BOA_PARA_APLICACAO && TEMP_BOA_PARA_APLICACAO && ILUMINACAO_BOA_PARA_APLICACAO);

		if (AMBIENTE_PROPICIO_PARA_APLICACAO)
		{
			Serial.println("O AMBIENTE ESTA PROPICIO PARA APLICACAO!");
			Serial.print("LIGANDO MOTOR POR ");
			Serial.print(TEMPO_MOTOR_LIGADO);
			Serial.println(" SEGUNDOS.");

			digitalWrite(MOTOR, HIGH);
			delay(TEMPO_MOTOR_LIGADO);
			digitalWrite(MOTOR, LOW);
			Serial.println("APLICACAO FEITA, MOTOR DESLIGADO.");

			// -> Ajustando LEDs de feedback
			digitalWrite(LED_VERM, HIGH);
			digitalWrite(LED_AMAR, LOW);
			digitalWrite(LED_VERD, LOW);
		
			// -> Pausa entre as aplicações
			delay(PAUSA_ENTRE_APLICACAO);
		} else {
			Serial.println("O AMBIENTE NAO ESTA PROPICIO PARA APLICACAO!");
			delay(PAUSA_ENTRE_LEITURA);
		}
	} else {
		// -> Ajustando LEDs de feedback
		digitalWrite(LED_VERM, LOW);
		digitalWrite(LED_AMAR, LOW);
		digitalWrite(LED_VERD, HIGH);
	
		Serial.println("O SOLO NAO ESTA PROPICIO PARA NEMATOIDES! Nao sera feita verificacao do ambiente.");   
		delay(PAUSA_ENTRE_LEITURA);
	}
}
