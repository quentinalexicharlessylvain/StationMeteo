# StationMeteo
Projet IOT Station Meteo


## Prérequis :
Pour flasher la carte avec le programme
* Importer la bibliothèque DHT.zip dans l’IDE Arduino
Croquis -> Inclure une bibliothèque -> Ajouter la bibliothèque .ZIP …
* Pour flasher le nodemcu maintenir le bouon flash en branchant la carte puis relacher.

## Configuration :
Pour récuperer l’ID et le PAC Sigfox du module Sigfox vous pouvez :
* Consulter le moniteur série d’Arduino (n’oubliez pas de mettre Baud rate sur 115200 )
 OU 
* Lors du démarage de la carte un hotspot Wifi est créé ( WeatherStation ) la LED verte en est témoin. Connectez vous-y et les informations seront disponibles a l’adresse 192.168.4.1.

## Débuter l’aquisition et la transmission de données :
Il suffit de sortir du mode d’initialisation pour cela appuyer sur le bouton ce qui va éteindre le module Wifi de l’ESP et démarrer la communication. 
Si vous souhaitez afficher de nouveau cette page appuyez sur le bouton afin d’allumer le module Wifi.
