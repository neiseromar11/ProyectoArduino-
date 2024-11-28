#include <LedControl.h>
#include <EEPROM.h>

// Definición de pines
const int pinData = 12;
const int pinClk = 11;
const int pinCS = 13;
const int numMatrices = 4;

// Constantes
const int MAX_MENSAJE = 50;
const int VELOCIDAD_SCROLL = 300; // Velocidad de desplazamiento en ms

LedControl lc = LedControl(pinData, pinClk, pinCS, numMatrices);

// Buffer para el mensaje
char mensajeSerial[MAX_MENSAJE];


const byte PATRONES[][8] = {
  // Números 0-9
  {B00111100,B01100110,B01101110,B01110110,B01100110,B01100110,B00111100,B00000000}, // 0
  {B00011000,B00111000,B00011000,B00011000,B00011000,B00011000,B00111100,B00000000}, // 1
  {B00111100,B01100110,B00000110,B00001100,B00110000,B01100000,B01111110,B00000000}, // 2
  {B00111100,B01100110,B00000110,B00011100,B00000110,B01100110,B00111100,B00000000}, // 3
  {B00001100,B00011100,B00111100,B01101100,B01111110,B00001100,B00001100,B00000000}, // 4
  {B01111110,B01100000,B01111100,B00000110,B00000110,B01100110,B00111100,B00000000}, // 5
  {B00111100,B01100110,B01100000,B01111100,B01100110,B01100110,B00111100,B00000000}, // 6
  {B01111110,B00000110,B00001100,B00011000,B00110000,B00110000,B00110000,B00000000}, // 7
  {B00111100,B01100110,B01100110,B00111100,B01100110,B01100110,B00111100,B00000000}, // 8
  {B00111100,B01100110,B01100110,B00111110,B00000110,B01100110,B00111100,B00000000}, // 9
  // Letras A-Z
  {B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110,B00000000}, // A
  {B01111100,B01100110,B01100110,B01111100,B01100110,B01100110,B01111100,B00000000}, // B
  {B00111100,B01100110,B01100000,B01100000,B01100000,B01100110,B00111100,B00000000}, // C
  {B01111100,B01100110,B01100110,B01100110,B01100110,B01100110,B01111100,B00000000}, // D
  {B01111110,B01100000,B01100000,B01111100,B01100000,B01100000,B01111110,B00000000}, // E
  {B01111110,B01100000,B01100000,B01111100,B01100000,B01100000,B01100000,B00000000}, // F
  {B00111100,B01100110,B01100000,B01101110,B01100110,B01100110,B00111100,B00000000}, // G
  {B01100110,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110,B00000000}, // H
  {B00111100,B00011000,B00011000,B00011000,B00011000,B00011000,B00111100,B00000000}, // I
  {B00011110,B00001100,B00001100,B00001100,B01101100,B01101100,B00111000,B00000000}, // J
  {B01100110,B01101100,B01111000,B01110000,B01111000,B01101100,B01100110,B00000000}, // K
  {B01100000,B01100000,B01100000,B01100000,B01100000,B01100000,B01111110,B00000000}, // L
  {B01100011,B01110111,B01111111,B01101011,B01100011,B01100011,B01100011,B00000000}, // M
  {B01100011,B01110011,B01111011,B01101111,B01100111,B01100011,B01100011,B00000000}, // N
  {B00111100,B01100110,B01100110,B01100110,B01100110,B01100110,B00111100,B00000000}, // O
  {B01111100,B01100110,B01100110,B01111100,B01100000,B01100000,B01100000,B00000000}, // P
  {B00111100,B01100110,B01100110,B01100110,B01101110,B01100110,B00111110,B00000000}, // Q
  {B01111100,B01100110,B01100110,B01111100,B01111000,B01101100,B01100110,B00000000}, // R
  {B00111100,B01100110,B01100000,B00111100,B00000110,B01100110,B00111100,B00000000}, // S
  {B01111110,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00000000}, // T
  {B01100110,B01100110,B01100110,B01100110,B01100110,B01100110,B00111100,B00000000}, // U
  {B01100110,B01100110,B01100110,B01100110,B01100110,B00111100,B00011000,B00000000}, // V
  {B01100011,B01100011,B01100011,B01101011,B01111111,B01110111,B01100011,B00000000}, // W
  {B01100110,B01100110,B00111100,B00011000,B00111100,B01100110,B01100110,B00000000}, // X
  {B01100110,B01100110,B00111100,B00011000,B00011000,B00011000,B00011000,B00000000}, // Y
  {B01111110,B00000110,B00001100,B00011000,B00110000,B01100000,B01111110,B00000000}, // Z
  // Caracteres especiales
  {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}, // espacio
  {B00011000,B00011000,B00011000,B00011000,B00011000,B00000000,B00011000,B00000000}, // !
  {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00011000,B00000000}, // .
  {B00000000,B00000000,B00000000,B00111100,B00111100,B00000000,B00000000,B00000000}, // -
  {B00000000,B00000000,B00011000,B00000000,B00000000,B00011000,B00000000,B00000000}, // :
  {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01111110,B00000000}, // _


};

// Función para obtener el índice del patrón
int obtenerIndicePatron(char c) {
  if (c >= '0' && c <= '9') return c - '0';  // Números
  else if (c >= 'A' && c <= 'Z') return c - 'A' + 10;  // Mayúsculas
  else if (c == ' ') return 36;  // Espacio
  else if (c == '!') return 37;  // Exclamación
  else if (c == '.') return 38;  // Punto
  else if (c == '-') return 39;  // Guión
  else if (c == ':') return 40;  // Dos puntos
  else if (c == '_') return 41;  // Guion bajo
  else return 36;
}

// Función para mostrar un carácter
void mostrarCaracter(char caracter, int matriz) {
  int indice = obtenerIndicePatron(caracter);
  for (int i = 0; i < 8; i++) {
    lc.setRow(matriz, i, PATRONES[indice][i]);
  }
}

// Función para desplazar el mensaje
void desplazarMensaje(const char* mensaje) {
  int longitudMensaje = strlen(mensaje);
  
  // Para cada posición del mensaje
  for (int i = 0; i < longitudMensaje + numMatrices; i++) {
    // Limpiar pantallas
    for (int j = 0; j < numMatrices; j++) {
      lc.clearDisplay(j);
    }
    
    // Mostrar caracteres actuales
    for (int j = 0; j < numMatrices; j++) {
      // Desplazar el mensaje a la izquierda
      if (i - j >= 0 && i - j < longitudMensaje) {
        mostrarCaracter(mensaje[i - j], j);
      }
    }
    
    delay(VELOCIDAD_SCROLL);
    
    // Verificar si hay nuevo mensaje
    if (Serial.available() > 0) {
      return;
    }
  }
}

// Función para guardar el mensaje en la EEPROM
void guardarMensajeEEPROM(const char* mensaje) {
  for (int i = 0; i < MAX_MENSAJE; i++) {
    EEPROM.write(i, mensaje[i]);
    if (mensaje[i] == '\0') break; 
  }
}

// Función para leer el mensaje de la EEPROM
void leerMensajeEEPROM() {
  for (int i = 0; i < MAX_MENSAJE; i++) {
    mensajeSerial[i] = EEPROM.read(i);
    if (mensajeSerial[i] == '\0') break; 
  }
}

void setup() {
  Serial.begin(9600);
  
  // Inicializar matrices
  for (int i = 0; i < numMatrices; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  
  // Leer el mensaje almacenado en EEPROM
  leerMensajeEEPROM();
  
  Serial.println("Ingrese su mensaje:");
}

void loop() {
   if (Serial.available() > 0) {
    int index = 0;
    delay(100); // Esperar a que lleguen todos los caracteres
    
    // Leer mensaje
    while (Serial.available() > 0 && index < MAX_MENSAJE - 1) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') continue; // Ignorar nuevas líneas
      mensajeSerial[index++] = c;
    }
    mensajeSerial[index] = '\0'; // Asegurarse de terminar la cadena con '\0'
    
    Serial.print("Mostrando: ");
    Serial.println(mensajeSerial);
    
    // Guardar el mensaje en la EEPROM
    guardarMensajeEEPROM(mensajeSerial);
    
    // Leer el mensaje guardado desde la EEPROM y mostrarlo
    leerMensajeEEPROM();
    Serial.print("Mensaje guardado en EEPROM: ");
    Serial.println(mensajeSerial);
  }
  
  // Mostrar mensaje
  if (strlen(mensajeSerial) > 0) {
    desplazarMensaje(mensajeSerial);
  }
}

void leerEEPROMCompleta() {
  Serial.println("Contenido de la EEPROM:");
  for (int i = 0; i < MAX_MENSAJE; i++) {
    char c = EEPROM.read(i);
    if (c == '\0') break; // Detener en el primer carácter nulo
    Serial.print(c);
  }
  Serial.println(); // Salto de línea al final
}
