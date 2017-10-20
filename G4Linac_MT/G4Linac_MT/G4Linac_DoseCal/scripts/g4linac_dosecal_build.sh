#!/bin/bash 
geant4_installation=$2
g4linac_installation=$1
source $geant4_installation/bin/geant4.sh
#
source /home/jaafar/Geant4/root/bin/thisroot.sh
#
cd $g4linac_installation
# 

if [ -d "bin_G4Linac_DoseCal" ]; then

rm -R bin_G4Linac_DoseCal
fi

mkdir bin_G4Linac_DoseCal
cd bin_G4Linac_DoseCal

#
cmake  -DGeant4_DIR= $geant4_installation $g4linac_installation/G4Linac_DoseCal

make



#read
exit
