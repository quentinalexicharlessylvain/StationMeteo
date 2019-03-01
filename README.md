# StationMeteo
Projet IOT Station Meteo


## Pr�requis :
Pour flasher la carte avec le programme
* Importer la biblioth�que DHT.zip dans l�IDE Arduino
Croquis -> Inclure une biblioth�que -> Ajouter la biblioth�que .ZIP �
* Pour flasher le nodemcu maintenir le bouon flash en branchant la carte puis relacher.

## Configuration :
Pour r�cuperer l�ID et le PAC Sigfox du module Sigfox vous pouvez :
* Consulter le moniteur s�rie d�Arduino (n�oubliez pas de mettre Baud rate sur 115200 )
 OU 
* Lors du d�marage de la carte un hotspot Wifi est cr�� ( WeatherStation ) la LED verte en est t�moin. Connectez vous-y et les informations seront disponibles a l�adresse 192.168.4.1.

## D�buter l�aquisition et la transmission de donn�es :
Il suffit de sortir du mode d�initialisation pour cela appuyer sur le bouton ce qui va �teindre le module Wifi de l�ESP et d�marrer la communication. 
Si vous souhaitez afficher de nouveau cette page appuyez sur le bouton afin d�allumer le module Wifi.
