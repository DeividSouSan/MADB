// C++ code
//


// Definindo nome para as portas digitais e analógicas
#define MOTOR 2
#define LED_VERM 4
#define LED_AMAR 5
#define LED_VERD 6
#define UMIDADE_SOLO A0
#define TEMP_SOLO A1
#define TEMP_AMBIENTE A2
#define UMIDADE_AMBIENTE A3
#define FOTORESISTOR A4

// Variáveis para armazenar o valor dos sensores
int umidade_solo_a = 0;
int temp_solo_a = 0;
int umidade_ambiente_a= 0;
int temp_ambiente_a = 0;
int luz_ambiente_a = 0;

// Variáveis relacionados ao tempo de delay
int const PAUSA_ENTRE_APLICACAO = 20000; // 43.200.000 ms ou 12 horas
int const TEMPO_MOTOR_LIGADO = 5000;
int const PAUSA_ENTRE_LEITURA = 10000; // 600.000 ms ou 10 minutos


void setup()
{
  pinMode(MOTOR, OUTPUT);
  pinMode(LED_VERM, OUTPUT);
  pinMode(LED_AMAR, OUTPUT);
  pinMode(LED_VERD, OUTPUT);
  Serial.begin(9600);
}

float porcentagem_umidade(int umidade_a, int valor_min, int valor_max)
{
  /*
  Essa função converte a umidade analógica que varia de 
  valor_min à valor_max (de acordo com a calibragem feita) 
  em porcentagem.
  */
  
  float porcentagem = (float(umidade_a) / float(valor_max)) * 100.00;
  return porcentagem;
}

int graus_celsius_temp(int temp_a, int valor_min, int valor_max)
{
  /*
  Essa função converte a temperatura analogica, que varia de 
  valor_min à valor_max (de acordo com a calibragem feita)
  em porcentagem. 
  */
  
  int temp = map((temp_a), valor_min, valor_max, 125, -40);
  return temp; 
}


float porcentagem_luz(int luz_a, int valor_min, int valor_max)
{
  /*
  Essa função converte a luz analógica que varia de 
  valor_min à valor_max (de acordo com a calibragem feita) 
  em porcentagem.
  */
  
  float porcentagem = map((luz_a), valor_min, valor_max, 0, 100);
  // float porcentagem = (float(luz_a) / float(valor_max)) * 100.00; (dá na mesma)
  return porcentagem;
}


void loop()
{
  	Serial.println("------LEITURA------");
  	// LEITURAS
  	// Medições em relação ao SOLO
  
	umidade_solo_a = analogRead(UMIDADE_SOLO);
  	int umidade_solo = porcentagem_umidade(umidade_solo_a, 0, 876);
      
  	Serial.print("Umidade Solo: ");
	Serial.print(umidade_solo);
  	Serial.println("%");
    
    temp_solo_a = analogRead(TEMP_SOLO);
  	int temp_solo = graus_celsius_temp(temp_solo_a, 0, 1023);
      
  	Serial.print("Temperatura do Solo: ");
	Serial.print(temp_solo);
  	Serial.println(" C");
  
  	// Medições em relação ao AMBIENTE
  
    umidade_ambiente_a = analogRead(UMIDADE_AMBIENTE);
  	int umidade_ambiente = porcentagem_umidade(umidade_ambiente_a, 0, 1023);
  	
  	Serial.print("Umidade Ambiente: ");
	Serial.print(umidade_ambiente);
  	Serial.println("%");
    
    temp_ambiente_a = analogRead(TEMP_AMBIENTE);
  	int temp_ambiente = graus_celsius_temp(temp_ambiente_a, 0, 1023);
      
  	Serial.print("Temperatura do Ambiente: ");
	Serial.print(temp_ambiente);
  	Serial.println(" C");
  
  	luz_ambiente_a = analogRead(FOTORESISTOR);
  	Serial.println(luz_ambiente_a);
  	int luz_ambiente = porcentagem_luz(luz_ambiente_a, 6, 679);
  
  	Serial.print("Iluminacao do Ambiente: ");
	Serial.print(luz_ambiente);
  	Serial.println("%");
  
  	// REGRA DE NEGÓCIO
  
  	
  	Serial.println("------RESULTADO LEITURAS------");
  	
  	// - Verifica se o solo está propricio para nematoides
  	bool UMIDADE_SOLO_RUIM = (umidade_solo <= 20 || umidade_solo >= 80);
    bool TEMPERATURA_SOLO_RUIM = (temp_solo <= 15 || temp_solo >= 35);
      
    bool SOLO_PROPICIO_NEMATOIDES = (UMIDADE_SOLO_RUIM && TEMPERATURA_SOLO_RUIM);
 
  	if (SOLO_PROPICIO_NEMATOIDES)
    {
      	digitalWrite(LED_VERM, LOW);
      	digitalWrite(LED_AMAR, HIGH);
      	digitalWrite(LED_VERD, LOW);
      
      	Serial.println("O SOLO ESTA PROPICIO PARA NEMATOIDES! Verificando condicoes do ambiente...");
      
      	// - Verifica se o ambiente está adequado para aplicacao
      
        bool UMIDADE_AMBIENTE_RUIM = (umidade_ambiente <= 20 || umidade_ambiente >= 80);
        bool TEMPERATURA_AMBIENTE_RUIM = (temp_ambiente <= 15 || temp_ambiente >=35);
      	bool ILUMINACAO_RUIM = (luz_ambiente <= 70);

        bool AMBIENTE_PROPICIO_APLICACAO = !(UMIDADE_AMBIENTE_RUIM || TEMPERATURA_AMBIENTE_RUIM || ILUMINACAO_RUIM);

        if (AMBIENTE_PROPICIO_APLICACAO)
        {
            Serial.println("O AMBIENTE ESTA PROPICIO PARA APLICACAO!");
            Serial.print("LIGANDO MOTOR POR ");
            Serial.print(TEMPO_MOTOR_LIGADO);
            Serial.println(" SEGUNDOS.");

            digitalWrite(MOTOR, HIGH);
            delay(TEMPO_MOTOR_LIGADO);
            digitalWrite(MOTOR, LOW);
            Serial.println("APLICACAO FEITA, MOTOR DESLIGADO.");

            // - Ajustando LEDs de feedback
          	digitalWrite(LED_VERM, HIGH);
          	digitalWrite(LED_AMAR, LOW);
          	digitalWrite(LED_VERD, LOW);
          
          	// - Pause entre as aplicações
            delay(PAUSA_ENTRE_APLICACAO);
      } else {
          Serial.println("O AMBIENTE NAO ESTA PROPICIO PARA APLICACAO!");
          delay(PAUSA_ENTRE_LEITURA);
      }
    } else {
      	digitalWrite(LED_VERM, LOW);
      	digitalWrite(LED_AMAR, LOW);
      	digitalWrite(LED_VERD, HIGH);
      
      	Serial.println("O SOLO NAO ESTA PROPICIO PARA NEMATOIDES! Nao sera feita verificacao do ambiente.");   
      	delay(PAUSA_ENTRE_LEITURA);
    }
}


// Primeira fase
// Montar relação de componentes ( o que tem aqui e o que não tem)

