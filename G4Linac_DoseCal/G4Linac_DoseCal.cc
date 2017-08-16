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
/*
 *   AUTHOR:
 *
 *   Dr. Jaafar EL Bakkali, Assistant Professor of Nuclear Physics, Rabat, Morocco.
 *   e-mail: bahmedj@gmail.com

-------------------------------------------------------------------------------------------
 * For documentation
 * see http://H5PhaseSpace.GitHub.com
 *
 * - 23/07/2017: public version 2.0
 *
--------------------------------------------------------------------------------------------
*/

#include "H5Cpp.h"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#include "Randomize.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4ScoringManager.hh"
#include "DetectorROGeometry.hh"
#include "G4SDManager.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "Physics.hh"

int main(int argc,char** argv)
{
G4Random::setTheEngine(new CLHEP::RanecuEngine);
#ifdef G4MULTITHREADED
G4MTRunManager* runManager = new G4MTRunManager;
//
int _numberOfThreads=G4Threading::G4GetNumberOfCores();
//int _numberOfThreads=1;
runManager->SetNumberOfThreads(_numberOfThreads);
//
runManager->SetVerboseLevel(0);
#else
G4RunManager* runManager = new G4RunManager;

#endif
G4String parallelWorldName = "ParallelScoringWorld";
DetectorConstruction * pDetectorConstruction= new  DetectorConstruction(_numberOfThreads);
pDetectorConstruction-> RegisterParallelWorld(new DetectorROGeometry(parallelWorldName));
runManager->SetUserInitialization(pDetectorConstruction);
G4VModularPhysicsList* physics = new Physics;
//
physics->SetVerboseLevel(0);
physics->RegisterPhysics(new G4ParallelWorldPhysics(parallelWorldName));
runManager->SetUserInitialization(physics);
runManager->SetUserInitialization(new ActionInitialization());  
#ifdef G4VIS_USE
G4VisManager* visManager = new G4VisExecutive;
//
visManager->SetVerboseLevel(0);
visManager->Initialize();
#endif
G4UImanager* UImanager = G4UImanager::GetUIpointer();
if (argc!=1) {
G4String command = "/control/execute ";
G4String fileName = argv[1];
UImanager->SetVerboseLevel(0);
UImanager->ApplyCommand(command+fileName);
}
else {
#ifdef G4UI_USE
G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
UImanager->ApplyCommand("/control/execute vis.mac"); 
#else
#endif
ui->SessionStart();
delete ui;
#endif
}
#ifdef G4VIS_USE
delete visManager;
#endif
delete runManager;
return 0;
}
