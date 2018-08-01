#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <dht.h>
#include <RTClib.h>
#include <EEPROMex.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>

///////////////////////////////////////////////////////////////////////////////
//                            DEFINE                                    
///////////////////////////////////////////////////////////////////////////////

// Broches reservées au shield ethernet:
// 10 -> SS for ethernet controller
// 4 -> SS for SD card
// 50 / 51 / 52 / 53

 #define soft_incub
// #define com_serie
//   #define com_sdcard

// Configuration clavier
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Configuration I/O
#define DHT221_PIN 2
#define DHT222_PIN 6
#define ONE_WIRE_BUS 7
#define relais 8
#define ALARM 9
#define relais_secu A3




///////////////////////////////////////////////////////////////////////////////
//                            INIT                                    
///////////////////////////////////////////////////////////////////////////////

File fichierSD;

dht DHT;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Adresse IP et Port
IPAddress ip(192, 168, 1, 177);
EthernetServer server(2853);

RTC_DS3231 RTC;

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWire(ONE_WIRE_BUS);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensors(&ourWire);

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

///////////////////////////////////////////////////////////////////////////////
//                            Définition des variables                                    
///////////////////////////////////////////////////////////////////////////////

int lcd_key     = 0;
int adc_key_in  = 0;
double Setpoint, Input, Output;
float temp_DS18B20;
float tempC;
float humd;
float temp;
float t2;
float h2;
float tempM = 0;
double Pcoeff = 21;       // 21
double Pvalue = 0;
double Icoeff = 0.01;     // 0.01
double Ivalue = 0;
double tempD = 0;
double tempDM = 0;
float tempMini= 100.0;
float tempMaxi= 0.0;
float humMaxi = 0.0;
float humMini = 100.0;
float humDelta;
double PIdelta;
double PIsum;
int page = 0;
double consigne = 31.0;
double consigneH = 85.0;
int heures;
int minutes;
int jour;
int mois;
int mem_heures;
int mem_minutes;
int mem_jour;
int mem_mois;
int addr_eeprom = 0;
unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long previousMillis2 = 0;
const long interval2 = 60000;
int mem_relais_secu = 0;
int mem_decl_relais_secu = 0;

///////////////////////////////////////////////////////////////////////////////
//                            Routines                                    
///////////////////////////////////////////////////////////////////////////////

// Lecture des boutons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);    
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnLEFT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnRIGHT;
 if (adc_key_in < 850)  return btnSELECT;  

 return btnNONE; 
}

///////////////////////////////////////////////////////////////////////////////
//                            SETUP                                    
///////////////////////////////////////////////////////////////////////////////
void setup() {

  lcd.begin(20,4);   // initialize the lcd for 16 chars 2 lines, turn on backlight
    
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  // Serial.print("server is at ");
  // Serial.println(Ethernet.localIP());

  Wire.begin();
  RTC.begin();
  pinMode(3, OUTPUT); //Configure la broche RELAIS en sortie 
  pinMode(ALARM, OUTPUT); //Configure la broche Alarme en sortie 
  pinMode(relais_secu, OUTPUT); //Configure la broche relais sécurité en sortie
  
  digitalWrite(relais_secu, HIGH); // par défaut, la relais n'est pas collé
  
  // Ajuste l'heure du module et consigne. A executer une seule fois
//   EEPROM.writeDouble(addr_eeprom, 33.5);
//   RTC.adjust(DateTime(__DATE__, __TIME__));

   consigne = EEPROM.readDouble(addr_eeprom);

  /*-( Start up the DallasTemperature library )-*/
   sensors.begin();

  #ifdef com_sdcard
    //Initialisation de l'instance
    if(!SD.begin(4)) {
      Serial.println(F("Initialisation carte SD impossible !"));
      return;
    }
    Serial.println(F("Initialisation carte SD OK"));
  #endif 

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                            Programme principal                                    
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void loop() {

  DateTime now = RTC.now();
  heures=now.hour();
  minutes=now.minute();
  jour=now.day();
  mois=now.month();
  
  #ifdef soft_incub
    dial_serie();
  #endif

  unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        ecran();
        temp_humid(); 
        regulation();

        // Mesure sonde DS18b20
        sensors.requestTemperatures(); // Send the command to get temperatures
        temp_DS18B20=sensors.getTempCByIndex(0);
    
    }

      unsigned long currentMillis2 = millis();

    if (currentMillis2 - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis2;

        #ifndef soft_incub
            dial_serie();
        #endif  
 
    }
    
    int newPIsum= int(PIsum);
    ethernet();
    key();

    // Surveillance écart consigne/température
    if (temp > consigne + 0.3 || temp < consigne - 0.3)
      analogWrite(ALARM, 252);
    else
      digitalWrite(ALARM, HIGH);

}
