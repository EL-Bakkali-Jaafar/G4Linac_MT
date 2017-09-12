#!/bin/bash 

geant4_installation=$2
g4linac_installation=$1
echo $1
echo $2
echo $3
source $geant4_installation/bin/geant4.sh
#
source /home/jaafar/Geant4/root/bin/thisroot.sh
#
cd $g4linac_installation
#
mkdir G4Linac_Head_bin

#
cd G4Linac_Head_bin

#
cmake  -DGeant4_DIR= $geant4_installation $g4linac_installation/G4Linac_Head

#
make

#
ls -all 

#
./G4Linac_Head run.mac

read
