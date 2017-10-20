#!/bin/bash 
ulimit unlimited
geant4_installation=$2
g4linac_installation=$1
source $geant4_installation/bin/geant4.sh
#

#
cd $g4linac_installation
# 


cd bin_G4Linac_DoseCal

#
./G4Linac_DoseCal run.mac

#read
exit
