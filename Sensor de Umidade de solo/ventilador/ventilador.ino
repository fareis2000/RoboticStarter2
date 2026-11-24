#include <DHT.h>

// Definições de pinos e tipo de sensor
#define PINO_DHT 2       // Pino de dados do DHT11
#define PINO_MOTOR 9     // Pino conectado à base do transistor
#define TIPO_DHT DHT11   // Modelo do sensor

// Limite de temperatura em graus Celsius
const float TEMP_LIMITE = 26.0;

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  Serial.begin(9600);
  pinMode(PINO_MOTOR, OUTPUT);
  digitalWrite(PINO_MOTOR, LOW); // Garante que o motor comece desligado
  
  dht.begin();
}

void loop() {
  // O DHT11 precisa de cerca de 2 segundos entre leituras
  delay(2000);

  float temperatura = dht.readTemperature();

  // Verifica se houve falha na leitura do sensor
  if (isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor DHT11!");
    return;
  }

  Serial.print("Temperatura atual: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Aciona ou desliga o transistor conforme a temperatura
  if (temperatura > TEMP_LIMITE) {
    digitalWrite(PINO_MOTOR, HIGH);
    Serial.println("Status: Motor LIGADO");
  } else {
    digitalWrite(PINO_MOTOR, LOW);
    Serial.println("Status: Motor DESLIGADO");
  }
}
