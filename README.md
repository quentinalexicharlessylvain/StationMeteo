# StationMeteo
Projet IOT Station Meteo

## Mode d'emploi : 
* Suivre le tuto de https://github.com/romaintribout/Sigfox-NODEMCU-BRKWS01-Wisol-SFM10R1 dans "Configure Sigfox Backend" en allant sur https://backend.sigfox.com et en se loggant
* Aller dans le dossier où se trouve ngrok, exécuter "cd chemindudossier"
* Ouvrir le serveur ngrok : exécuter "ngrok.exe http 5000" (sous Windows) 
* Copier adresse ngrok : "http://...ngrok.io"
* Coller dans index.html en remplaçant le début de l'adresse, fin du fichier, axios : "http://...ngrok.io/releve"
* Ouvrir le serveur, exécuter "python serveur.py"
* Coller adresse ngrok dans le navigateur

## Explication :
* Ngrok, c'est quoi ? Un service gratuit permettant de créer un serveur qui sert de tunnel. Si vous voulez en apprendre plus : https://ngrok.com/product

* Grâce à sigfox, on récupère les données du capteur en POST sur le serveur python via flask. On les mets dans une base de données avec la date en plus. Puis, toujours sur le même serveur python, les données sont envoyé sur ngrok/releve. La page web html récupère les données grâce à vuejs et axios sur cette adresse. Puis le serveur envoie le fichier html en brut en GET sur l'adresse ngrok. Ainsi, l'information sera valable partout 

* Améliorations : 
- Serveur stable avec adresse stable  
- Sécurité
