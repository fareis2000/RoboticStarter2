#include <Wire.h> // Inclusão da biblioteca necessária
#include <SPI.h> // Inclusão de biblioteca
#include <MFRC522.h> // Inclusão de biblioteca

#define SS_PIN 10 // Pino SDA
#define RST_PIN 9 // Pino de reset
#define BUTTON_PIN 4 // Pino do botão

MFRC522 rfid(SS_PIN, RST_PIN); // Passagem de parâmetros referente aos pinos

bool buttonPressed = false;
const int pinoLedVerde = 3; // Pino digital referente ao LED verde
const int pinoLedVermelho = 2; // Pino digital referente ao LED vermelho

String registeredTags[10]; // Array para armazenar até 10 tags
int registeredCount = 0; // Contador de tags registradas

void setup() {
  Serial.begin(9600); // Inicializa a serial
  Wire.begin(); // Inicializa a biblioteca Wire
  SPI.begin(); // Inicializa o barramento SPI
  rfid.PCD_Init(); // Inicializa MFRC522

  pinMode(pinoLedVerde, OUTPUT); // Define o pino como saída
  pinMode(pinoLedVermelho, OUTPUT); // Define o pino como saída
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Define o botão como entrada com resistor pull-up

  digitalWrite(pinoLedVerde, LOW); // LED inicia desligado
  digitalWrite(pinoLedVermelho, LOW); // LED inicia desligado

  Serial.println("Sistema pronto. Pressione o botão para registrar uma tag.");
}

void loop() {
  leituraRfid(); // Chama a função responsável pela validação da tag RFID
}

// Função de leitura e validação da tag RFID
void leituraRfid() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) // Verifica se o cartão está presente no leitor
    return;

  // Gera o identificador (UID) da tag lida
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i != 3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Identificador (UID) da tag: ");
  Serial.println(strID);

  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) { // Verifica se o botão foi pressionado
    registrarTag(strID);
  } else {
    validarTag(strID);
  }

  rfid.PICC_HaltA(); // Para a leitura do cartão
  rfid.PCD_StopCrypto1(); // Para a criptografia no PCD
}

// Função para registrar uma tag no array
void registrarTag(String tag) {

  if (registeredCount < 10) {
    for (int i = 0; i < registeredCount; i++) {
      if (registeredTags[i] == tag) {
        Serial.println("Tag já registrada.");
        return;
      }
    }
    registeredTags[registeredCount] = tag;
    registeredCount++;
    Serial.println("Tag registrada com sucesso.");
  } else {
    Serial.println("Limite de registros alcançado.");
  }
}

// Função para validar uma tag registrada
void validarTag(String tag) {
  for (int i = 0; i < registeredCount; i++) {
    if (registeredTags[i] == tag) {
      digitalWrite(pinoLedVerde, HIGH); // Liga o LED verde
      delay(3000); // Intervalo de 3 segundos
      digitalWrite(pinoLedVerde, LOW); // Desliga o LED verde
      Serial.println("Acesso permitido.");
      return;
    }
  }
  digitalWrite(pinoLedVermelho, HIGH); // Liga o LED vermelho
  delay(3000); // Intervalo de 3 segundos
  digitalWrite(pinoLedVermelho, LOW); // Desliga o LED vermelho
  Serial.println("Acesso negado.");
}