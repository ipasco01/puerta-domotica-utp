// Definición de los pines a los que están conectados los relés
const int relayPin1 = A0;

void setup() {
  // Configurar los pines de los relés como salidas
  pinMode(relayPin1, OUTPUT);

  // Inicializar los relés en apagado
  digitalWrite(relayPin1, LOW);

  // Iniciar comunicación serie
  Serial.begin(9600);
}

void loop() {
  // Verificar si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    // Si se recibe el comando "OPEN", encender el relé
    if (command == "OPEN") {
      digitalWrite(relayPin1, HIGH);  // Encender el relé
      delay(5);                    // Mantenerlo encendido por 1 segundo
      digitalWrite(relayPin1, LOW);   // Apagar el relé

      // Pausar un momento para evitar que el comando se procese dos veces
      delay(5); // Ajustar según sea necesario para evitar dobles lecturas
      }
      }
}