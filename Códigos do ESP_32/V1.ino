#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Fabnet";            // Nome da sua rede Wi-Fi
const char* password = "71037523";       // Senha da sua rede Wi-Fi

// Endereço do servidor Django onde os dados serão enviados
const char* serverName = "http://192.168.0.10:8000/esp_data/"; 

// URL do servidor Django de onde o ESP32 vai buscar os comandos
const char* commandURL = "http://192.168.0.10:8000/get_command/";

void setup() {
  Serial.begin(115200);    // Inicializando a comunicação serial
  WiFi.begin(ssid, password);  // Conectando ao Wi-Fi

  Serial.print("Conectando-se ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {    // Espera até conectar
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi! 🎉");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {  // Verifica se está conectado ao Wi-Fi
    HTTPClient http;

    // Enviando dados para o servidor
    http.begin(serverName);  // URL para enviar os dados
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "data=Ola do ESP32";  // Dado que será enviado
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();  // Pega a resposta do servidor
      Serial.println("Dados enviados: " + response);
    } else {
      Serial.println("Erro ao enviar dados 😞");
    }
    http.end();  // Fecha a conexão

    // Agora vamos pegar o comando do servidor
    http.begin(commandURL);
    httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();  // Pega o comando
      Serial.println("Comando recebido: " + payload);

      // Faz algo com base no comando recebido
      if (payload.indexOf("comando1") > 0) {
        Serial.println("Executando Comando 1 🎯");
      } else if (payload.indexOf("comando2") > 0) {
        Serial.println("Executando Comando 2 🔥");
      } else if (payload.indexOf("comando3") > 0) {
        Serial.println("Executando Comando 3 🚀");
      }
    } else {
      Serial.println("Erro ao obter comando 😢");
    }
    http.end();  // Fecha a conexão

  } else {
    Serial.println("Desconectado do WiFi 😓");
  }

  // Aguarde 5 segundos antes de enviar novamente
  delay(5000);
}
