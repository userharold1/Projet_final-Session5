//piloteWifiUdp:
//Historique: 
// 2025-11-16, Harold Kouadio, creation

//INCLUSIONS
#include "main.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include "piloteWiFiUDP.h"


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
    int packetSize = udp.parsePacket();

    if (packetSize)          // → un paquet est disponible
    {
        int longueur = udp.read(message, sizeof(message) - 1);

        if (longueur < 0)
        {
          longueur = 0;
        }
        message[longueur] = '\0';
    }
    else                     // → aucun paquet
    {
        message[0] = '\0';   // IMPORTANT : message vide = aucun msg reçu
    }

    return message;
}



void piloteWiFiUDP_initialise(void)
{
  // Démarage Mode Wifi AP
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(LOCALIPAP, GETAWAYAP, SUBNETAP);
  delay(100);
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  // Démarrage du port UDP
  udp.begin(PORTDEST);
  Serial.println("Début du Programme");
}