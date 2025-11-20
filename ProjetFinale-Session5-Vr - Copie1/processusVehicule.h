
// serviceWiFiUDP.h
// Auteur : Harold pour ProjetFinDeSession
// Service UDP avec machines à états (réception + transmission)

#ifndef PROCESSUSVEHICULE_H
#define PROCESSUSVEHICULE_H

// Defines
#define POSITION_DEPART                0
#define POSITION_LIGNE_MILIEU_AVANT    1
#define POSITION_LIGNE_FIN             2
#define POSITION_LIGNE_MILIEU_RETOUR   3
#define POSITION_LIGNE_DEBUT           4

#define SUIVEUR_ACTIF 1
#define SUIVEUR_NON_ACTIF 0

// STRUCTURE DU PROCESSUS
typedef struct
{
  unsigned char CompteurPosi; 
  unsigned char derniereLignePleine ;
  unsigned char controleSuiveur;

} PROCESSUSVEHICULE;

extern PROCESSUSVEHICULE processusVehicule;


void processusVehicule_initialise(void);

#endif