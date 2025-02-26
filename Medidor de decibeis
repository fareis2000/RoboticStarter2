#include <Wire.h>  // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h>  // Biblioteca para controle do LCD via I2C

// Inicializa o LCD no endereço 0x27 com 16 colunas e 2 linhas
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const int sampleWindow = 50;  // Tempo de amostragem em milissegundos
unsigned int sample;  // Variável para armazenar leituras do sensor

// Definição dos pinos
#define SENSOR_PIN A0  // Pino analógico onde o sensor de som está conectado
#define LED_VERDE 2  // LED indicador para nível de som baixo
#define LED_AMARELO 4  // LED indicador para nível de som moderado
#define LED_VERMELHO 3  // LED indicador para nível de som alto

void setup() {
  pinMode(SENSOR_PIN, INPUT);  // Define o pino do sensor como entrada
  pinMode(LED_VERDE, OUTPUT);  // Define o pino do LED "Quiet" como saída
  pinMode(LED_AMARELO, OUTPUT);  // Define o pino do LED "Moderate" como saída
  pinMode(LED_VERMELHO, OUTPUT);  // Define o pino do LED "Loud" como saída

  // Garante que todos os LEDs iniciam desligados
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.begin(9600);  // Inicia a comunicação serial com baud rate 9600
  lcd.init();  // Inicializa o LCD
  lcd.backlight();  // Liga a luz de fundo do LCD
  lcd.clear();  // Limpa o display do LCD
}

void loop() {
  unsigned long startMillis = millis();  // Armazena o tempo inicial da leitura

  float peakToPeak = 0;  // Variável para armazenar a diferença pico a pico
  unsigned int signalMax = 0;  // Armazena o maior valor lido
  unsigned int signalMin = 1024;  // Armazena o menor valor lido

  // Coleta dados do sensor dentro da janela de tempo definida
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(SENSOR_PIN);  // Lê o valor do sensor
    
    // Imprime os valores lidos do sensor no Monitor Serial
    Serial.print("Sensor Value: ");
    Serial.println(sample);

    // Atualiza os valores máximo e mínimo
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample;
      }
      if (sample < signalMin) {
        signalMin = sample;
      }
    }
  }

  peakToPeak = signalMax - signalMin;  // Calcula a diferença entre os picos

  // Imprime o valor de pico a pico no Monitor Serial
  Serial.print("Peak to Peak: ");
  Serial.println(peakToPeak);

  // Mapeia os valores lidos para uma escala de dB
  int db = map(peakToPeak, 0, 500, 50, 90);  // Converte os valores para um intervalo de 50 a 90 dB

  // Se o valor for muito pequeno, define um valor mínimo de 50 dB
  if (peakToPeak < 20) {
    db = 50;
  }

  // Imprime o valor do dB no Monitor Serial
  Serial.print("dB: ");
  Serial.println(db);

  // Exibe o nível de som no LCD
  lcd.setCursor(0, 0);  // Define o cursor na primeira linha
  lcd.print("Loudness: ");
  lcd.print(db);
  lcd.print("db");

  // Define os LEDs com base nos níveis de dB
  if (db <= 60) {
    lcd.setCursor(0, 1);  // Define o cursor na segunda linha
    lcd.print("Level: Quiet   ");  // Exibe "Quiet" e apaga caracteres extras
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
  } else if (db > 60 && db < 85) {
    lcd.setCursor(0, 1);
    lcd.print("Level: Moderate");
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  } else if (db >= 85) {
    lcd.setCursor(0, 1);
    lcd.print("Level: HIGH    ");
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }

  // Imprime o estado dos LEDs no Monitor Serial
  Serial.print("Quiet: ");
  Serial.println(digitalRead(LED_VERDE));
  Serial.print("Moderate: ");
  Serial.println(digitalRead(LED_AMARELO));
  Serial.print("Loud: ");
  Serial.println(digitalRead(LED_VERMELHO));

  delay(200);  // Aguarda 200 ms antes da próxima leitura para evitar leituras muito rápidas
}
