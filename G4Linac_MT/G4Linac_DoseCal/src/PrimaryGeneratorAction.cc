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
#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4UserH5PhaseSpaceReader.hh"
#include "H5Cpp.h"
#include "DetectorConstruction.hh"

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4ThreadLocal G4UserH5PhaseSpaceReader* PrimaryGeneratorAction::theG4UserH5PhaseSpaceReader;

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()

{

auto id_thread = std::to_string(G4Threading::G4GetThreadId()); 
//
//
G4cout<<" initializing class PrimaryGeneratorAction" <<G4endl;
{
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction * pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 

theG4UserH5PhaseSpaceReader = new G4UserH5PhaseSpaceReader();
 G4cout<<"pDetectorConstruction->GeneratorFlag : " << pDetectorConstruction->GeneratorFlag<<G4endl;
// 
G4cout<<" pDetectorConstruction->Nsplit : " << pDetectorConstruction->Nsplit<<G4endl;
theG4UserH5PhaseSpaceReader-> SET_PARAMETERS(pDetectorConstruction->H5PhaseSpaceFileName,
                                             false,
                                                pDetectorConstruction->NewZSTOP,// Z STOP
                                               pDetectorConstruction->GeneratorFlag, // GENERATOR FLAG: 0 NRMAL, 1 ROT SPLIT, 2 RECYCLING
                                                pDetectorConstruction->Nsplit);// SPLITTING FACTOR

   

//
}


}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
   // 

if (theG4UserH5PhaseSpaceReader) delete theG4UserH5PhaseSpaceReader;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

//G4cout<<"event id: "<<anEvent->GetEventID()<<G4endl;

 //
theG4UserH5PhaseSpaceReader->GeneratePrimaryVertex(anEvent);
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void PrimaryGeneratorAction::SetNewZSTOP(G4double _ZSTOP){
this->NewZSTOP=_ZSTOP;

}
void PrimaryGeneratorAction::SetH5PhaseSpaceFileName(G4String _Filename){
this->H5PhaseSpaceFileName=_Filename+".h5";

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
