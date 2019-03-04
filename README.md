# StationMeteo
Projet IOT Station Meteo
Displayign of data on a map

In order to view a .nc file, put in a first folder : the python script + a folder named "examples"
In the folder "examples" put a .nc named file.nc

# Affichage sur carte via Basemap avec script python

Basé sur : https://matplotlib.org/basemap/
Les bibliothèques Basemap et cm de mpl_toolkits doivent être installées,
tout comme netCDF4, numpy et matplotlib.

Basemap : Outil de matplotlib permettant de tracer les maps
netCDF4 : Bibliothèque permettant l'ouverture des fichiers récupérer sur water.weather.gov

Fonctionne sur python 2.7, testé sous Ubuntu 16.04

# Exemples de données affichées

Traitement du fichier file.nc et ajout de quelques données simulant une lecture MQTT
(Data.jpeg)

Il est possible de positionner des repères sur les cartes affichées.
(Figure_1-1.png)

