#include "Wire.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();   // pins I2C par défaut de ton Feather ESP32

  delay(500);
  Serial.println("🔎 Scan I2C en cours...");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("📍 Appareil trouvé à l'adresse 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("⚠️ Erreur à 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("❌ Aucun appareil I2C détecté");
  }

  Serial.println("----- Scan terminé -----\n");

  delay(2000); // Scan toutes les 2 secondes
}
