//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
  AUTHOR: Dr. Jaafar EL Bakkali, Assistant Professor of Nuclear Physics, Rabat, Morocco.
  e-mail: bahmedj@gmail.com

  For documentation
  see http://G4Linac_MT.github.com
 
  10/08/2017: public version 1.0
 
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorMessenger.hh"
#include "G4Threading.hh"
#include "H5PhaseSpaceWriter.hh"
#include "G4SDManager.hh"
#include "G4AutoDelete.hh"
#include"G4RegionStore.hh"
#include"globals.hh"
#include"G4Material.hh"
#include"G4MaterialTable.hh"
#include"G4Element.hh"
#include"G4ElementTable.hh"
#include"G4Box.hh"
#include"G4Region.hh"
#include"G4ThreeVector.hh"
#include"G4PVPlacement.hh"
#include"G4PVReplica.hh"
#include"G4SDManager.hh"
#include"G4VisAttributes.hh"
#include"G4Colour.hh"
#include"G4Tubs.hh"
#include"G4Cons.hh"
#include"G4Paraboloid.hh"
#include"G4SubtractionSolid.hh"
#include"G4UnionSolid.hh"
#include"G4IntersectionSolid.hh"
#include "G4tgbVolumeMgr.hh"
#include "G4tgrMessenger.hh"
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),mSD(0)
{
 pDetectorMessenger= new DetectorMessenger(this);

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNumberOfEventsPerThread(int _NumberOfEventsPerThread){

this->NumberOfEventsPerThread=_NumberOfEventsPerThread;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNameOfGeomFromTextFile(G4String _FileName){
this->geom_file_name=_FileName;

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorConstruction::~DetectorConstruction()
{ 

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4VPhysicalVolume* DetectorConstruction::Construct(){
messenger = new G4tgrMessenger;
G4String filename = this->geom_file_name;
G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
volmgr->AddTextFile(filename);
//------------------------------------------------
// Read the text files and construct the GEANT4 geometry
//------------------------------------------------
this->physWorld= volmgr->ReadAndConstructDetector();
return this->physWorld;


}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::ConstructSDandField(){
G4SDManager* pSDManager = G4SDManager::GetSDMpointer();
mSD = new H5PhaseSpaceWriter("Phantom");
pSDManager-> AddNewDetector(mSD);
SetSensitiveDetector("PHASE_SPACE",mSD);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetH5PhaseSpaceZStop(G4double _Zstop){
this->zstop=_Zstop;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetH5PhaseSpaceName(G4String _PhaseSpaceName){
this->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION=_PhaseSpaceName;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
