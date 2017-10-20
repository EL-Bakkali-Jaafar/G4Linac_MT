#!/bin/bash 
geant4_installation=$2
g4linac_installation=$1
valgrind_installation=$3


source $geant4_installation/bin/geant4.sh
#
source /home/jaafar/Geant4/root/bin/thisroot.sh
#
cd $g4linac_installation
# 


cd bin_G4Linac_Head

#
$valgrind_installation/valgrind --tool=helgrind ./G4Linac_Head run.mac

#read
exit
