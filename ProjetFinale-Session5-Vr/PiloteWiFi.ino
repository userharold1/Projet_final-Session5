//piloteWifiUdp:
//Historique: 
// 2025-11-16, Harold Kouadio, creation

//INCLUSIONS
#include "main.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include "piloteWiFi.h"


//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
WiFiUDP udp;
static char message[255];
//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void piloteWiFiUDP_Transmet(unsigned char octet)
{
  udp.beginPacket(IPDEST,PORTDEST);
  udp.print(octet);
  udp.endPacket();
}

char* piloteWiFiUDP_litRecu(void)
{
  int longueur = udp.read(message, sizeof(message) - 1);
  message[longueur] = '\0';

  return message;
}


void piloteWiFiUDP_initialise(void)
{
  // Démarage Mode Wifi AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  delay(100);
  WiFi.softAPConfig(LOCALIPAP, GETAWAYAP, SUBNETAP);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  // Démarrage du port UDP
  udp.begin(PORTDEST);
  Serial.println("Début du Programme");
}