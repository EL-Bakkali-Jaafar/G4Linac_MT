#!/bin/bash 

g4linac_installation=$1
geant4_installation=$2
root_installation=$3
DosimetricData=$4
physics_quantity=$5
arg1=$6
arg2=$7
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

echo "./G4Linac_DataAnalysis DosimetricData" $DosimetricData $physics_quantity  $arg1 $arg2 
./G4Linac_DataAnalysis DosimetricData $DosimetricData $physics_quantity  $arg1 $arg2 

echo "./G4Linac_DataAnalysis DosimetricData" $DosimetricData $physics_quantity  $arg1 $arg2 
exit
