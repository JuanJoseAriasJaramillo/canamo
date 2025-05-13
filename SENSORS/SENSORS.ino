#include <DHT.h>
#include <DHT_U.h>

#define Type DHT11

//pins
const int dhtPin = 33;
const int moisturePin = 32;

//DHT
DHT HT(dhtPin, Type);

// moistures values
const int dry = 4000; //aproximcion estimada de nivel de sequedad 
const int wet = 1000; //aproximacion estimada de la humedad total del sensor 

// Intervalo de tiempo
const int dt = 1000;

void setup() {
    Serial.begin(115200);
    HT.begin();
}

//floorHumidity
float readSoilMoisture() {
    int moistureSensorVal = analogRead(moisturePin);
    float percentageMoisture = 100.0 * (dry - moistureSensorVal) / (dry - wet);
    return constrain(percentageMoisture, 0, 100);
    
}

//read temperature and humidity from DHT11
void readDHT(float &humidity, float &tempC, float &tempF) {
    humidity = HT.readHumidity();
    tempC = HT.readTemperature();
    tempF = HT.readTemperature(true);
}

//SERIAL DATA
void displayData(float soilMoisture, float humidity, float tempC, float tempF) {
    Serial.print("Humedad del suelo: ");
    Serial.print(soilMoisture, 2);
    Serial.print("% - - - - Humedad relativa: ");
    Serial.print(humidity);
    Serial.print("%  Temperatura: ");
    Serial.print(tempC);
    Serial.print("°C / ");
    Serial.print(tempF);
    Serial.println("°F");
    
}

void loop() {
    float soilMoisture = readSoilMoisture();
    float humidity, tempC, tempF;
    readDHT(humidity, tempC, tempF);
    displayData(soilMoisture, humidity, tempC, tempF);
    delay(dt);

    float readmoisturePin = analogRead(moisturePin);
    Serial.println(readmoisturePin);

    
}