#include <DHT.h>

// Define o tipo do sensor DHT e o pino em que está conectado
#define DHTPIN A2 // Pino conectado ao DHT11
#define DHTTYPE DHT11 // Define o tipo de sensor (DHT11)

// Cria o objeto DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  dht.begin();        // Inicializa o sensor DHT
  Serial.println("Sensor DHT11 iniciado!");
}

void loop() {
  // Lê a umidade e a temperatura do sensor
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica se a leitura foi bem-sucedida
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do sensor DHT!");
    return;
  }

  // Exibe os valores lidos
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print("%");
  Serial.print(" / Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
