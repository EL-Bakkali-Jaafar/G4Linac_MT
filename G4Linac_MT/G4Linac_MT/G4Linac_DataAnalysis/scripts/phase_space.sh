#!/bin/bash 

g4linac_installation=$1
geant4_installation=$2
root_installation=$3
physics_quantity=$4
h5phase_space=$5
source $geant4_installation/bin/geant4.sh
#
source $root_installation/bin/thisroot.sh
#
cd $g4linac_installation
# 

if [ -d "bin_G4Linac_DataAnalysis" ]; then

rm -R bin_G4Linac_DataAnalysis
fi

mkdir bin_G4Linac_DataAnalysis
cd bin_G4Linac_DataAnalysis

#
cmake  -DGeant4_DIR= $geant4_installation $g4linac_installation/G4Linac_DataAnalysis

make


#
./G4Linac_DataAnalysis PhaseSpaceData $h5phase_space $physics_quantity 


exit
