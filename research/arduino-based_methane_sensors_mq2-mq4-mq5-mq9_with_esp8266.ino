// Include the library
#include <MQUnifiedsensor.h>

/**************************** Internet Connection ************************************/
#include "WiFiEsp.h"
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiEspClient  client;

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // TX, RX
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
/**************************** Internet Connection ************************************/

/************************ Hardware Related Macros ************************************/
#define         Board                   ("Arduino UNO")

/*********************** Software Related Macros ************************************/
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10)    // For arduino UNO/MEGA/NANO
#define         RatioMQ2CleanAir        (9.83)  // RS / R0 = 9.83 ppm
#define         RatioMQ4CleanAir        (4.4)   // RS / R0 = 60 ppm 
#define         RatioMQ5CleanAir        (6.5)   // RS / R0 = 6.5 ppm 
#define         RatioMQ9CleanAir        (9.6) //RS / R0 = 60 ppm 
#define         PreaheatControlPin5      (3) // Preaheat pin to control with 5 volts // For MQ5
#define         PreaheatControlPin14      (4) // Preaheat pin to control with 1.4 volts // For MQ5

/***************************** Globals ***********************************************/
MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, A0, "MQ-2");
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, A1, "MQ-4");
MQUnifiedsensor MQ5(Board, Voltage_Resolution, ADC_Bit_Resolution, A2, "MQ-5");
MQUnifiedsensor MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, A3, "MQ-9");

/*
const int mq2Pin = A0;  // Pin for MQ2 sensor
const int mq4Pin = A1;  // Pin for MQ4 sensor
const int mq5Pin = A2;  // Pin for MQ5 sensor
*/


void setup() {
  /*
  /**************************** Internet Connection ************************************/
  //Initialize serial and wait for port to open  
  Serial.begin(115200);  // Initialize serial
  while(!Serial){
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  // initialize serial for ESP module  
  setEspBaudRate(ESP_BAUDRATE);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  Serial.print("Searching for ESP8266..."); 
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  Serial.println("found it!");
   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  /**************************** Internet Connection ************************************/
  

  // Set math model to calculate the PPM concentration and the value of constants
  MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ5.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ9.setRegressionMethod(1); //_PPM =  a*ratio^b
 
  /*****************************  MQ Init ********************************************/ 
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/
  MQ2.init(); 
  MQ4.init(); 
  MQ5.init();
  MQ9.init();
 
  MQ2.setRL(5);
  MQ4.setRL(20);
  MQ5.setRL(20);
  MQ9.setRL(10);

  /*****************************  MQ CAlibration ********************************************/ 
  // Explanation: 
    // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
  // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor

  pinMode(PreaheatControlPin5, OUTPUT);
  pinMode(PreaheatControlPin14, OUTPUT);
  
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ2.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ2.calibrate(RatioMQ2CleanAir);
    Serial.print(".");

    MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
    Serial.print(".");

    MQ5.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ5.calibrate(RatioMQ5CleanAir);
    Serial.print(".");

    MQ9.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ9.calibrate(RatioMQ9CleanAir);
    Serial.print(".");
  }
  MQ2.setR0(calcR0/10);
  //Serial.println("  done!.");

  MQ4.setR0(calcR0/10);
  //Serial.println("  done!.");

  MQ5.setR0(calcR0/10);
  //Serial.println("  done!.");

  MQ9.setR0(calcR0/10);
  //Serial.println("  done!.");  

  /*****************************  MQ CAlibration ********************************************/ 
}

void loop() {

  /*
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  */
  
  /*
    MQ2                           MQ4                                   MQ5                              MQ9
    Exponential regression:       Exponential regression:               Exponential regression:          Exponential regression:
    Gas    | a      | b           Gas    | a      | b                   Gas    | a      | b              Gas    | a      | b
    CH4    | 4264.312 | -2.456    CH4    | 1012.7 | -2.786              CH4    | 177.65 | -2.56          CH4    | 4269.6 | -2.648
    H2     | 987.99 | -2.162      H2                                    H2     | 1163.8 | -3.874         
    LPG    | 574.25 | -2.222      LPG    | 3811.9 | -3.113              LPG    | 80.897 | -2.431         LPG    | 1000.5 | -2.186
    CO     | 36974  | -3.109      CO     | 200000000000000 | -19.05     CO     | 491204 | -5.826         CO     | 599.65 | -2.244
    Alcohol| 3616.1 | -2.675      Alcohol| 60000000000 | -14.01         Alcohol| 97124  | -4.918
    Propane| 658.71 | -2.168               
                                  Smoke  | 30000000    | -8.308
  */


  // MQ2
  MQ2.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup 
  
  // MQ2 Different Gasses
  MQ2.setA(164.312); MQ2.setB(-2.456); // Configure the equation to to calculate CH4 concentration
  float mq2_CH4 = MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ2.setA(987.99); MQ2.setB(-2.162); // Configure the equation to to calculate H2 concentration
  float mq2_H2 = MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
 
  MQ2.setA(574.25); MQ2.setB(-2.222); // Configure the equation to to calculate LPG concentration
  float mq2_LPG = MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ2.setA(924.35); MQ2.setB(-3.109); // Configure the equation to to calculate CO concentration
  float mq2_CO = MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ2.setA(90.40); MQ2.setB(-2.675); // Configure the equation to to calculate Alcohol concentration
  float mq2_Alcohol = MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup   

  MQ2.setA(658.71); MQ2.setB(-2.168); // Configure the equation to to calculate Alcohol concentration
  float mq2_Propane = MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup  
  

  // MQ4
  MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  // MQ4 Different Gasses
  MQ4.setA(6012.7); MQ4.setB(-2.786); // Configure the equation to to calculate CH4 concentration
  float mq4_CH4 = MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ4.setA(3811.9); MQ4.setB(-3.113); // Configure the equation to to calculate LPG concentration
  float mq4_LPG = MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ4.setA(200000000000000); MQ4.setB(-19.05); // Configure the equation to to calculate CO concentration
  float mq4_CO = MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ4.setA(60000000000); MQ4.setB(-14.01); // Configure the equation to to calculate Alcohol concentration
  float mq4_Alcohol = MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ4.setA(30000000); MQ4.setB(-8.308); // Configure the equation to to calculate Smoke concentration
  float mq4_Smoke = MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  // MQ5
  MQ5.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  // MQ4 Different Gasses
  MQ5.setA(177.65); MQ5.setB(-2.56); // Configure the equation to to calculate CH4 concentration
  float mq5_CH4 = MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
   
  MQ5.setA(1163.8); MQ5.setB(-3.874); // Configure the equation to to calculate H2 concentration
  float mq5_H2 = MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ5.setA(80.897); MQ5.setB(-2.431); // Configure the equation to to calculate CO concentration
  float mq5_LPG = MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ5.setA(491204); MQ5.setB(-5.826); // Configure the equation to to calculate Alcohol concentration
  float mq5_CO = MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ5.setA(97124); MQ5.setB(-4.918); // Configure the equation to to calculate Smoke concentration
  float mq5_Alcohol = MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    
  // MQ9
  MQ9.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ9.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  // MQ9 Different Gases
  MQ9.setA(4869.6); MQ9.setB(-2.648); // Configure the equation to to calculate CH4 concentration
  float mq9_CH4 = MQ9.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup  

  MQ9.setA(1000.5); MQ9.setB(-2.186); // Configure the equation to to calculate CO concentration
  float mq9_LPG = MQ9.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup  

  MQ9.setA(599.65); MQ9.setB(-2.244); // Configure the equation to to calculate Alcohol concentration
  float mq9_CO = MQ9.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  //Serial.println(String("MQ4 Gases   ") + "CH4: " + String(mq4_CH4) + " LPG: " + String(mq4_LPG) + " CO: " + String(mq4_CO) + " Alcohol: " + String(mq4_Alcohol) + " Smoke: " + String(mq4_Smoke));

  //                            MQ2 CH4                                     MQ4 CH4                                             MQ5 CH4                                              MQ9 CH4                                        MQ2 Alcohol                                               MQ2 CO                                             MQ4 Alcohol                             MQ4 CO                                                        MQ9 CO                           
  Serial.println(String("MQ2  ") + "CH4: " + String(mq2_CH4) + String("  |  MQ4  ") + "CH4: " + String(mq4_CH4) + String("  |  MQ5  ") + "CH4: " + String(mq5_CH4) + String("  |   MQ9  ") + "CH4: " + String(mq9_CH4) + String("  |   MQ2  ") + "Alcohol: " + String(mq2_Alcohol) + String("  |   MQ2  ") + "CO: " + String(mq2_CO) + String("  |  MQ2  ") + "H2: " + String(mq4_Alcohol) + String("  |  MQ4  ") + "CO: " + String(mq4_CO)  + String("  |   MQ9  ") + "CO: " + String(mq9_CO) ); 
  

  /**************************** Thingspeak Server ************************************/

  /*
  // set the fields with the values
  ThingSpeak.setField(1, mq2_CH4); 
  ThingSpeak.setField(2, mq4_CH4); 
  ThingSpeak.setField(3, mq9_CH4); 
  ThingSpeak.setField(4, mq5_CH4);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  */

  delay(10000);
  //delay(8UL * 60 * 60 * 1000); // Wait 20 seconds to update the channel again
  /**************************** Thingspeak Server ************************************/  
}

// This function attempts to set the ESP8266 baudrate. Boards with additional hardware serial ports
// can use 115200, otherwise software serial is limited to 19200.
void setEspBaudRate(unsigned long baudrate){
  long rates[6] = {115200,74880,57600,38400,19200,9600};

  Serial.print("Setting ESP8266 baudrate to ");
  Serial.print(baudrate);
  Serial.println("...");

  for(int i = 0; i < 6; i++){
    Serial1.begin(rates[i]);
    delay(100);
    Serial1.print("AT+UART_DEF=");
    Serial1.print(baudrate);
    Serial1.print(",8,1,0,0\r\n");
    delay(100);  
  }
    
  Serial1.begin(baudrate);
}
