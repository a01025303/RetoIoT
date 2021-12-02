// Importar librerías 

#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <WiFiNINA.h>

// Inicialización de variables 

char ssid[] = "Vum"; // Nombre de la red
char password[] = "12345678"; // Contraseña de la red

int status = WL_IDLE_STATUS; // Variable que contiene un status temporal

char server[] = "622c-148-241-109-145.ngrok.io";    // URL del servidor a utilizar (se debe cambiar cada vez que se vuelva a correr ngrok)

WiFiClient client; // Crear cliente de tipo WiFiClient --> este objeto permite conectarnos a un IP en un puerto determinado

// Variables MQ7
int adc_MQ7; // Lectura analógica MQ7
float voltajeMQ7; // Voltaje MQ7
float RS7; // Rs MQ7
float RO7 = 497.13; // Ro MQ7 --> Calculado en "SetupMQ" mediante mediciones del sensor en aire limpio 
double CO; // Valor de medición de CO

// Variables MQ9
int adc_MQ9; // Lectura analógica MQ9
float voltajeMQ9; // Voltaje MQ9
float RS9; // Rs MQ9
float RO9 = 682.36; // Ro MQ7 --> Calculado en "SetupMQ" mediante mediciones del sensor en aire limpio
double LPG; // Valor de medición de LPG

// Variables utilizadas para llenar tablas en base de datos
int SensorID; // ID de un sensor
String GasMedido; // Gas medido por el sensor
int counter = 0; // Contador para asignar un id de medición en la tabla de diagnósticos 

// Setup
void setup(){
  Serial.begin(9600); // Iniciar la comunicación serial con 9600 

  while (status != WL_CONNECTED) { // Ciclo para iterar mientras todavía no se tenga una conexión
    Serial.println("Attempting to connect to Network: "); // Mandar mensaje de intento de conexión
    Serial.println(ssid); // Imprimir la red 
    status = WiFi.begin(ssid,password); // Inicializar librería 
    delay (1000); 
  }

  Serial.print("Connected to SSID: "); // Avisar que se logró conectar a la red
  Serial.println(WiFi.SSID()); // Obtener SSID 
  IPAddress ip = WiFi.localIP(); // Obtener IP 
  IPAddress gateway = WiFi.gatewayIP(); // Obtener gateway
  Serial.print("IP Address: "); 
  Serial.println(ip); // Imprimir IP

}

void loop(){

  // Inicializar variables locales para indicar los niveles de gases (se inicializan aquí para que se reinicien en cada ciclo)

  // Niveles de CO
  bool HighCO = false; 
  bool LowCO = false; 
  bool NormalCO = false; 

  // Niveles de LPG
  bool HighLPG = false; 
  bool LowLPG = false; 
  bool NormalLPG = false;

  // Inicializar archivos de Json
  DynamicJsonDocument mq7(1024); // Json para MQ7
  DynamicJsonDocument mq9(1024); // Json para MQ9 
  DynamicJsonDocument COlevels(1024); // Json para niveles de CO
  DynamicJsonDocument LPGlevels(1024); // Json para niveles de LPG

  // Obtención de mediciones MQ7
  adc_MQ7 = analogRead(A0); //Lemos la salida analógica  del MQ7
  voltajeMQ7 = adc_MQ7 * (5.0 / 1024.0); //Convertimos la lectura en un valor de voltaje
  RS7 = 1000*((5-voltajeMQ7)/voltajeMQ7);  //Calculamos Rs con un RL de 1k
  CO = 108.46*pow(RS7/RO7, -1.4777); // calculamos la concentración  de CO en ppm

  // Obtención de mediciones MQ9
  adc_MQ9 = analogRead(A1); //Lemos la salida analógica  del MQ9
  voltajeMQ9 = adc_MQ9 * (5.0 / 1024.0); //Convertimos la lectura en un valor de voltaje
  RS9 = 1000*((5-voltajeMQ9)/voltajeMQ9);  //Calculamos Rs con un RL de 1k
  LPG = 1015.7*pow(RS9/RO9, -2.075); // calculamos la concentración  de LPG en ppm

  // Json para MQ7 (los demás valores de la tabla en la base de datos se generan automáticamente)
  mq7["Value"] = CO; // Asignar el valor de CO a Value
  mq7["idSensor"] = 1; // Asignar el identificador del sensor (1 para el MQ7) al idSensor

  counter ++; // Una vez realizada la medición de CO, añadir 1 al contador 

  // Condiciones para indicar diagnóstico
  if(CO >= 0 && CO < 26) // Rango de 0 - 25 ppm
    LowCO = true; // Diagnóstico en Low
  else if(CO >= 26 && CO < 51) // Rango de 26 - 50 ppm
    NormalCO = true; // Diagnóstico en Normal
  else if(CO >= 51) // De 51 ppm en adelante 
    HighCO = true; // Diagnóstico en High

  // Json de valores para la tabla de diagnóstico 
  COlevels["HighAlert"] = HighCO; // Asignar valor de HighCO a "HighAlert"
  COlevels["LowAlert"] = LowCO; // Asignar valor de LowCO a "LowAlert"
  COlevels["NormalLevel"] = NormalCO; // Asignar valor de NormalCO a "NormalLevel"
  COlevels["idMeasurement"] = counter; // Asignar valor de counter a "idMeasurement"

  
  // Json para MQ9
  mq9["Value"] = LPG; // Asignar el valor de LPG a Value
  mq9["idSensor"] = 2; // Asignar el identificador del sensor (2 para el MQ9) al idSensor

  counter++; // Una vez realizada la medición de LGP, añadir 1 al contador 

  // Condiciones para indicar diagnóstico
  if(LPG >= 0 && LPG < 5000) // Rango 0 - 5000 ppm
  {
    // Diagnóstico en Low y Normal
    LowLPG = true; 
    NormalLPG = true; 
  }
  else if(LPG >= 5001) // Rango mayor a 5000 ppm
    HighLPG = true; // Diagnóstico en High
    
  LPGlevels["HighAlert"] = HighLPG; // Asignar valor de HighLPG a "HighAlert"
  LPGlevels["LowAlert"] = LowLPG; // Asignar valor de LowLPG a "LowAlert"
  LPGlevels["NormalLevel"] = NormalLPG; // Asignar valor de NormalLPG a "NormalLevel"
  LPGlevels["idMeasurement"] = counter; // Asignar valor de counter a "idMeasurement"

  // Creación de strings en donde se va a guardar el Json convertido
  String postData1;
  String postData2;
  String postData3;
  String postData4;

  // Crear documentos de Json 
  serializeJson(mq7, postData1); // obtener información de mq7 y escribir en postData1
  serializeJson(COlevels, postData2); // obtener información de COlevels y escribir en postData2
  serializeJson(mq9, postData3); // obtener información de mq9 y escribir en postData3
  serializeJson(LPGlevels, postData4); // obtener información de LPGlevels y escribir en postData4

  // POST REQUESTS
   if (client.connect(server, 80)) { // Conectar al cliente al servidor en el puerto indicado 
    client.println("POST /measurement HTTP/1.1"); // Indicar en dónde hacer el post --> se hace al sitio con /measurement
    client.println("Host: 622c-148-241-109-145.ngrok.io"); // Indicar el host
    client.println("Content-Type: application/json"); // Indicar el tipo de contenido 
    client.print("Content-Length: "); // Indicar el largo --> no se pone el número porque tendría que ser exacto
    client.println(postData1.length()); // Indicar largo del Json
    client.println();
    client.print(postData1); // Imprimir el string
   }

   if (client.connect(server, 80)) { // Conectar al cliente al servidor en el puerto indicado 
    client.println("POST /diagnostic HTTP/1.1"); // Indicar en dónde hacer el post --> se hace al sitio con /diagnostic
    client.println("Host: 622c-148-241-109-145.ngrok.io"); // Indicar el host
    client.println("Content-Type: application/json"); // Indicar el tipo de contenido 
    client.print("Content-Length: "); // Indicar el largo --> no se pone el número porque tendría que ser exacto
    client.println(postData2.length()); // Indicar largo del Json
    client.println();
    client.print(postData2); // Imprimir el string
   }

   if (client.connect(server, 80)) { // Conectar al cliente al servidor en el puerto indicado 
    client.println("POST /measurement HTTP/1.1"); // Indicar en dónde hacer el post --> se hace al sitio con /measurement
    client.println("Host:  622c-148-241-109-145.ngrok.io"); // Indicar el host
    client.println("Content-Type: application/json"); // Indicar el tipo de contenido 
    client.print("Content-Length: "); // Indicar el largo --> no se pone el número porque tendría que ser exacto
    client.println(postData3.length()); // Indicar largo del Json
    client.println();
    client.print(postData3); // Imprimir el string
  }
  if (client.connect(server, 80)) { // Conectar al cliente al servidor en el puerto indicado 
    client.println("POST /diagnostic HTTP/1.1"); // Indicar en dónde hacer el post --> se hace al sitio con /diagnostic
    client.println("Host: 622c-148-241-109-145.ngrok.io"); // Indicar el host
    client.println("Content-Type: application/json"); // Indicar el tipo de contenido 
    client.print("Content-Length: "); // Indicar el largo --> no se pone el número porque tendría que ser exacto
    client.println(postData4.length()); // Indicar largo del Json
    client.println();
    client.print(postData4); // Imprimir el string
   }

  // Desconectar
  if (client.connected()) {
    client.stop();
  }

  // Imprimir los datos del Json en el monitor serial
  Serial.println(postData1);
  Serial.println(postData2);
  Serial.println(postData3);
  Serial.println(postData4);

  delay(500);
  
}
