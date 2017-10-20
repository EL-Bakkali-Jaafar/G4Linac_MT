#!/bin/bash 
geant4_installation=$2
g4linac_installation=$1
source $geant4_installation/bin/geant4.sh
#
source /home/jaafar/Geant4/root/bin/thisroot.sh
#
cd $g4linac_installation
# 

if [ -d "bin_G4Linac_Head" ]; then

rm -R bin_G4Linac_Head
fi

mkdir bin_G4Linac_Head
cd bin_G4Linac_Head

#
cmake  -DGeant4_DIR= $geant4_installation $g4linac_installation/G4Linac_Head

make -j4

#./G4Linac_Head run.mac

#read
exit
