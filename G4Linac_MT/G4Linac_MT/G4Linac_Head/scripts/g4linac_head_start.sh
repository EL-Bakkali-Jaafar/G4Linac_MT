#!/bin/bash 
ulimit unlimited
geant4_installation=$2
g4linac_installation=$1
source $geant4_installation/bin/geant4.sh
#
source /home/jaafar/Geant4/root/bin/thisroot.sh
#
cd $g4linac_installation
# 


cd bin_G4Linac_Head

#
 ./G4Linac_Head run.mac

#read
exit
