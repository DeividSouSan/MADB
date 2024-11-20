// C++ code
//


// Definindo nome para as portas digitais e analógicas
#define LED_VERM 4
#define LED_AMAR 5
#define LED_VERD 6
#define FOTORESISTOR A4
#define TEMP_SOLO A1
#define TEMP_AMBIENTE A2
#define UMIDADE_AMBIENTE A3
#define UMIDADE_SOLO A0

// Calibrando os sensores {valor_min, valor_max}
int intervalo_luminosidade[2] = {2, 404}; // Luminosidade
int intervalo_umidade_ambiente[2] = {0, 1023}; // Umidade Ambiente
int intervalo_temperatura_solo[2] = {0, 1023}; // Temperatura Solo
int intervalo_temperatura_ambiente[2] = {0, 1023}; // Temperatura Ambiente
int intervalo_umidade_solo[2] = {0, 876}; // Umidade Solo

// Variáveis para armazenar o valor dos sensores
int luz_ambiente_a = 0;
int temp_solo_a = 0;
int umidade_ambiente_a= 0;
int temp_ambiente_a = 0;
int umidade_solo_a = 0;

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
    digitalWrite(LED_VERM, HIGH);
    digitalWrite(LED_AMAR, HIGH);
    digitalWrite(LED_VERD, HIGH);

    // INICIO LEITURAS //
	Serial.println("------LEITURA------");

    // -> Medições em relação ao SOLO
	
	temp_solo_a = analogRead(TEMP_SOLO);
	int temp_solo = map_A_G(temp_solo_a, intervalo_temperatura_solo[0], intervalo_temperatura_solo[1]);
		
	Serial.print("Temperatura do Solo: ");
	Serial.print(temp_solo);
	Serial.println(" C");

    umidade_solo_a = analogRead(UMIDADE_SOLO);
	int umidade_solo = map_A_P(umidade_solo_a, intervalo_umidade_solo[0], intervalo_umidade_solo[1]);
		
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
}
