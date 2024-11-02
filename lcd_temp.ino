
#include <LiquidCrystal.h>
#include <DHT22.h>

// Define the LCD pins according to the LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Define the DHT sensor type and pin
#define DHTPIN 2        // Pin where the DHT22 is connected
DHT22 dht(DHTPIN);

#define D0_PIN 12
#define D1_PIN 13

// Timer variables for button actions
unsigned long d0StartTime = 0;
unsigned long d1StartTime = 0;
bool d0Active = false;
bool d1Active = false;

void setup() {
  // Initialize the LCD and set its dimensions
  lcd.begin(16, 2); 
  lcd.print("DHT22 Sensor");  // Initial message
  delay(2000);                 // Wait for 2 seconds

  // Start the DHT sensor
  // dht.begin();
  
  pinMode(D0_PIN, OUTPUT);
  pinMode(D1_PIN, OUTPUT);
  // Clear the LCD for sensor readings
  lcd.clear();
}

void loop() {
  // Read the temperature and humidity from the DHT22
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature(); // Temperature in Celsius

  // Check if any readings failed and exit early
  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.print("Sensor error");
    return;
  }

  // Print the temperature and humidity on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);  // Top line
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);  // Bottom line
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Check button presses
  int button = analogRead(A0); // Read the button status from A0
  
  if (button < 50) {          // Right button
    d1StartTime = millis();
    d1Active = true;
    digitalWrite(D1_PIN, HIGH);
  } else if (button < 200) {  // Up button
    // Placeholder for additional functionality
  } else if (button < 400) {  // Down button
    // Placeholder for additional functionality
  } else if (button < 600) {  // Left button
    d0StartTime = millis();
    d0Active = true;
    digitalWrite(D0_PIN, HIGH);
  } else if (button < 800) {  // Select button
    // Placeholder for additional functionality
  }

  // Handle D0 timer (30 seconds)
  if (d0Active && (millis() - d0StartTime >= 5000)) {
    digitalWrite(D0_PIN, LOW);
    d0Active = false;
  }

  // Handle D1 timer (5 minutes)
  if (d1Active && (millis() - d1StartTime >= 10000)) {
    digitalWrite(D1_PIN, LOW);
    d1Active = false;
  }
  // Update every 2 seconds
  delay(2000);
}
