#define BUTTON_PIN 4
#define led_verde 3 // Pino onde o botão está conectado

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura o botão como entrada com resistor pull-up
  pinMode(led_verde, OUTPUT);
  Serial.println("Pressione o botão para ver no Serial Monitor.");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) { // Verifica se o botão foi pressionado
    Serial.println("Botão pressionado!");
    digitalWrite(led_verde, HIGH);
    delay(200); // Pequeno atraso para evitar múltiplas leituras devido ao bounce
    digitalWrite(led_verde, LOW);
  }
}
