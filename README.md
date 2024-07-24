# puerta-domotica-utp

# Puerta Domotica Trabajo Final
Grupo 1

Librerias incluidas en este proyecto

``` 
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
```


# Proyecto de Puerta Domótica UTP

Este proyecto consiste en un sistema de control de acceso mediante una puerta domótica, desarrollado con Arduino y ARDUINO CONTROLLER de la Play Store . El sistema permite abrir la puerta mediante una aplicación móvil conectada por Bluetooth.

## Tabla de Contenidos

- [Descripción](#descripción)
- [Requisitos](#requisitos)
- [Configuración del Hardware](#configuración-del-hardware)
- [Configuración del Software](#configuración-del-software)
- [Instalación](#instalación)
- [Uso](#uso)
- [Contribuciones](#contribuciones)
- [Licencia](#licencia)

## Descripción

El sistema de puerta domótica está diseñado para proporcionar un método seguro y conveniente de acceso. Utiliza un Arduino conectado a un keypad y un módulo Bluetooth para recibir comandos desde una aplicación móvil.

## Requisitos

Para reproducir este proyecto, necesitarás los siguientes componentes:

- 2 Arduino Uno
- 1 Keypad 4x4
- 1 Módulo Bluetooth HC-05
- 1 Relay
- 1 Transformador de 220V a 5V
- 1 Pantalla LCD
- Cables de conexión

## Configuración del Hardware

### Primer Arduino

1. **Relay**: Conecta el relay al primer Arduino de la siguiente manera:
    - A0 a IN4 del relay
    - A1 a IN3 del relay
    - A2 a IN2 del relay
    - A3 a IN1 del relay
    - VCC del relay a 5V del Arduino
    - GND del relay a GND del Arduino

2. Este Arduino se encarga de abrir la puerta.

### Segundo Arduino

1. **Keypad**: Conecta el keypad al segundo Arduino de la siguiente manera:
    - Pin 7 a columna 1
    - Pin 8 a columna 2
    - Pin 9 a columna 3
    - Pin 10 a columna 4
    - Pin 11 a fila 1
    - Pin 12 a fila 2
    - Pin 13 a fila 3

2. **Módulo Bluetooth**: Conecta el módulo Bluetooth al segundo Arduino de la siguiente manera:
    - RX del módulo Bluetooth a pin 2 del Arduino
    - TX del módulo Bluetooth a pin 3 del Arduino
    - VCC del módulo Bluetooth a la breadboard
    - GND del módulo Bluetooth a la breadboard

3. **Pantalla LCD**: Conecta la pantalla LCD a la breadboard compartiendo el VCC y GND con el módulo Bluetooth.

## Configuración del Software

1. **Arduino**: Programa ambos Arduinos con los sketches proporcionados en la carpeta `arduino_code`.

2. **Arduino App Controller**:  instalarla en tu dispositivo móvil.

## Instalación

1. Clona este repositorio en tu máquina local:
    ```bash
    git clone https://github.com/ipasco01/puerta-domotica-utp.git
    ```

2. Sube los sketches a los Arduinos:
    - Abre el archivo `Relay_Arduino.ino` y súbelo al primer Arduino.
    - Abre el archivo `Keypad_Bluetooth_Arduino.ino` y súbelo al segundo Arduino.

3. Configura la aplicación móvil utilizando arduino controller en play store y descárgala en tu dispositivo.

## Uso

1. Enciende el sistema conectando ambos Arduinos.
2. Abre la aplicación en tu dispositivo móvil.
3. Empareja el dispositivo móvil con el módulo Bluetooth del sistema.
4. Usa la aplicación para enviar el comando `open` y abrir la puerta.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, sigue estos pasos para contribuir:

1. Haz un fork del repositorio.
2. Crea una rama nueva (`git checkout -b feature/nueva-caracteristica`).
3. Realiza tus cambios y haz commit (`git commit -am 'Añadir nueva característica'`).
4. Haz push a la rama (`git push origin feature/nueva-caracteristica`).
5. Abre un Pull Request.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.
