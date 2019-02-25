from mpl_toolkits.basemap import Basemap, cm
# requires netcdf4-python (netcdf4-python.googlecode.com)
from netCDF4 import Dataset as NetCDFFile
import numpy as np
import matplotlib.pyplot as plt
import random


nc = NetCDFFile('examples/file.nc')
#Source
#http://water.weather.gov/precip/

prcpvar = nc.variables['amountofprecip']
data = 0.01*prcpvar[:]

#In order to put new values
for i in range (620,630):
    for j in range (754,766):
        data[i][j]=50


latcorners = nc.variables['lat'][:]
loncorners = -nc.variables['lon'][:]
lon_0 = -nc.variables['true_lon'].getValue()
lat_0 = nc.variables['true_lat'].getValue()
# create figure and axes instances
fig = plt.figure(figsize=(8,8))
ax = fig.add_axes([0.1,0.1,0.8,0.8])

m = Basemap(resolution='l',satellite_height=4000000.,projection='nsper',lat_0 = 35., lon_0 = -20.,llcrnrx=400000.,llcrnry=500000.,urcrnrx=2700000.,urcrnry=2700000.)


# draw coastlines, state and country boundaries, edge of map.
m.drawcoastlines()
m.drawstates()
m.drawcountries()
# draw parallels.
parallels = np.arange(0.,90,10.)
m.drawparallels(parallels,labels=[1,0,0,0],fontsize=10)
# draw meridians
meridians = np.arange(180.,360.,10.)
m.drawmeridians(meridians,labels=[0,0,0,1],fontsize=10)
ny = data.shape[0]; nx = data.shape[1]
lons, lats = m.makegrid(nx, ny) # get lat/lons of ny by nx evenly space grid.
x, y = m(lons, lats) # compute map proj coordinates.
# draw filled contours.


#Select values on lader
#clevs = [0,1,2.5,5,7.5,10,15,20,30,40,50,70,100,150,200,250,300,400,500,600,750]
#clevs = []
clevs=[0,1,2,3,4,5,7.5,10,12.5,15,20,25,30,35,40,50,75,100,200]

'''
for i in range(0,5):
    clevs.append(i)
for i in range(0,5):
    clevs.append(5+2*i)
for i in range(0,5):
    clevs.append(15+5*i)
'''

cs = m.contourf(x,y,data,clevs,cmap=cm.s3pcpn)


# add colorbar.
cbar = m.colorbar(cs,location='bottom',pad="5%")
cbar.set_label('C')
# add title
plt.title("Show Example"+' for period ending '+prcpvar.dateofdata[7:9]+"/"+prcpvar.dateofdata[5:7]+"/"+prcpvar.dateofdata[0:4])
plt.show()

print(nc.variables['lat'][:])
print(nc.variables['lon'][:])
print(nc.variables['true_lon'].getValue())
print(nc.variables['true_lat'].getValue())
