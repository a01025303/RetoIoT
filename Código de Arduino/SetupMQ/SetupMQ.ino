// Inicialización de variables 
// Variables MQ7
const int MQ7_pin = 0; // Pin que se utilza para lectura de datos
const float RL7 = 1000; // Resistencia RL 1K
const float CLEAN_AIR_RATIO7 = 27; // Función constante de la medición de aire puro del sensor
float voltaje_MQ7; // Voltaje del MQ7
float RS7; // Rs del MQ7
float RO7; // Ro del MQ7

// Variables MQ9
const int MQ9_pin = 1; // Pin que se utilza para lectura de datos
const float RL9 = 1000; // Resistencia RL 1K
const float CLEAN_AIR_RATIO9 = 9.99; // Función constante de la medición de aire puro del sensor
float voltaje_MQ9; // Voltaje del MQ9
float RS9; // Rs del MQ9
float RO9;  // Ro del MQ9

void setup() {
  // Inicializar en 9600
  Serial.begin(9600);
}

void loop() {
  // Lectura valores aire MQ7 (para obtener RO7)
  int lectura_actual7; // Variable para la lectura actual
  lectura_actual7 = analogRead(MQ7_pin); // Lectura analógica MQ7
  voltaje_MQ7 = (float) 5*lectura_actual7/1024; // Obtención de voltaje MQ7 mediante la relación (5/1024)
  RS7 = ((float) RL7*(5-voltaje_MQ7)/voltaje_MQ7); // Obtención de Rs de MQ7 mediante la realación establecida en el datasheet
  RO7 = RS7/CLEAN_AIR_RATIO7; // Obtención de Ro de MQ7 --> despejando para RS/RO = CLEAN_AIR_RATIO (esto viene del datasheet)
   

  // Lectura valores aire MQ9 (para obtener RO9)
  int lectura_actual9; // Variable para la lectura actual
  lectura_actual9 = analogRead(MQ9_pin); // Lectura analógica MQ9
  voltaje_MQ9 = (float) 5*lectura_actual9/1024; // Obtención de voltaje MQ9 mediante la relación (5/1024)
  RS9 = ((float) RL9*(5-voltaje_MQ9)/voltaje_MQ9); // Obtención de Rs de MQ9 mediante la realación establecida en el datasheet
  RO9 = RS9/CLEAN_AIR_RATIO9; // Obtención de Ro de MQ9 --> despejando para RS/RO = CLEAN_AIR_RATIO (esto viene del datasheet)

  // Imprimir valores de RO
  Serial.print("RO de MQ7: "); 
  Serial.print(RO7);
  Serial.print("   |   RO de MQ9: ");
  Serial.print(RO9);
  delay(500); 
  Serial.println("");

  // Se toman los valores de Ro para utilizarlos en las funciones de mediciones reales de CO y LPG
}
