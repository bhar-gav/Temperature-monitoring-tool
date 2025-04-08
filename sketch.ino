
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 14      // Pin to which the DHT22 sensor is connected
#define DHTTYPE DHT22  // DHT 22 (AM2302) sensor type

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

int ledPin = 15;  // Declaration of LED pin variable

void setup() {
  pinMode(ledPin, OUTPUT);  // Declare LED as an output
  // Initialize LCD
  LCD.init();
  LCD.backlight();
  LCD.setCursor(1,0);
  LCD.print("  INDIRA D.A ");
  LCD.setCursor(1,1);
  LCD.print("  6705223035   ");
  delay (500);
  LCD.clear();
  LCD.setCursor(1,0);
  LCD.print("SISTEM PEMANTAU");
  LCD.setCursor(1,1);
  LCD.print("   SUHU DEMAM  ");
  delay (500);
  LCD.clear();
  LCD.setCursor(1,0);
  LCD.print("    MULAI     ");
  delay(700);
  LCD.clear();
}

void loop() {
  // Read data from the DHT sensor
  float temperature = dht.readTemperature();

  // Check if the DHT sensor read was successful
  if (!isnan(temperature)) {
    LCD.init();
    LCD.backlight();
    LCD.setCursor(0, 0);
    LCD.print("Temperature: ");
    LCD.print(temperature);
    LCD.print("°C");

    // Check if temperature is above 38 degrees Celsius
    if (temperature > 38.0) {
      digitalWrite(ledPin, HIGH); // Turn on the LED
      LCD.setCursor(0, 1);
      LCD.print("      DEMAM    ");
    } else {
      digitalWrite(ledPin, LOW); // Turn off the LED
      LCD.setCursor(0, 1);
      LCD.print("   SUHU NORMAL  ");
    }
  } else {
    LCD.init();
    LCD.backlight();
    LCD.setCursor(0, 0);
    LCD.print("Error reading DHT sensor");
    digitalWrite(ledPin, LOW); // Turn off the LED in case of an error
  }

  delay(2000); // Delay for 2 seconds before reading again
}
