#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

// Definición de pines y configuración del teclado 4x4
const byte filas = 4;
const byte columnas = 4;
byte pinesFilas[] = {13, 12, 11, 10};
byte pinesColumnas[] = {9, 8, 7, 6};
char teclas[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad tecladoUno = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas);

// Configuración del LCD
LiquidCrystal_I2C lcd1(0x27, 16, 2); // Dirección I2C del primer LCD

// Pines del LED, buzzer, sensor de temperatura TMP36 y sensor PIR
#define LED_PIN 5
#define BUZZER_PIN 3
#define TEMP_PIN A0
#define PIR_PIN 4

// Almacena la clave ingresada
char clave[5] = "";
int indiceClave = 0;

// Definición de los pines para el módulo Bluetooth
SoftwareSerial bluetooth(2, 3); // RX, TX

void setup() {
  Serial.begin(9600); // Comunicación con el segundo Arduino
  bluetooth.begin(9600); // Comunicación Bluetooth
  guardarCodigo(0, "5678");
  guardarCodigo(5, "9856");
  inicializarLCD();
  inicializarPines();
}

void loop() {
 
    
    
  verificarTeclaPresionada();
  
  verificarComandoSerial();
}

void inicializarLCD() {
  lcd1.init();
  lcd1.clear();
  delay(2000);
  lcd1.backlight();
  mostrarMensaje("Proyecto Arquitectu");
  mostrarMensajeSegundaLinea("ra de Computadoras");
  delay(2000);
  mostrarMensaje("Bienvenid@");
  delay(2000);
  lcd1.clear();
  mostrarMensaje("Ingrese clave:");
  mostrarMensajeSegundaLinea("_ _ _ _");
}

void inicializarPines() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
}

void verificarTeclaPresionada() {
  char tecla_presionada = tecladoUno.getKey();

  if (tecla_presionada != NO_KEY) {
    Serial.print("Tecla: ");
    Serial.println(tecla_presionada);

    if (indiceClave < 4) {
      clave[indiceClave] = tecla_presionada;
      indiceClave++;
    }

    lcd1.setCursor(0, 1);
    for (int i = 0; i < 4; i++) {
      lcd1.print(clave[i]);
      lcd1.print(' ');
    }
    if (indiceClave == 4) {
      // Verificar código
      if (verificarCodigoEEPROM(0, clave) || verificarCodigoEEPROM(5, clave)) {
        mostrarMensaje("Puerta Abierta");
        mostrarMensajeSegundaLinea(":)");
        
        // Enviar señal al segundo Arduino para abrir la puerta
        Serial.println("OPEN");
        bluetooth.println("OPEN"); // Enviar comando al módulo Bluetooth
        delay(10000);
        inicializarLCD();
      } else {
        mostrarMensaje("Error :(");
        mostrarMensajeSegundaLinea("Codigo erroneo");
        delay(2000);
        inicializarLCD();
      }
      // Resetear clave para nuevo intento
      indiceClave = 0;
      memset(clave, '_', 4);
    }
  }
}

void verificarComandoSerial() {
  if (bluetooth.available() > 0) {
    String comando = bluetooth.readStringUntil('\n');
    comando.trim();
    if (comando == "OPEN") {
      Serial.println("OPEN"); 
       mostrarMensaje("Puerta Abierta");
        mostrarMensajeSegundaLinea(":)");
      delay(2000);
        inicializarLCD();
    }
  }
}

bool verificarCodigoEEPROM(int direccion, const char* codigo) {
  for (int i = 0; i < 4; i++) {
    if (EEPROM.read(direccion + i) != codigo[i]) {
      return false;
    }
  }
  return true;
}

void guardarCodigo(int direccion, const char* codigo) {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(direccion + i, codigo[i]);
  }
}

// Función para mostrar mensajes en el LCD
void mostrarMensaje(const char* mensaje) {
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(mensaje);
}

void mostrarMensajeSegundaLinea(const char* mensaje) {
  lcd1.setCursor(0, 1);
  lcd1.print(mensaje);
}
