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
#include "ActionInitialization.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#include "QBBC.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#include "PhysicsList.hh"
#include "Randomize.hh"
#include <sys/types.h>
#include <ctime>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "G4AutoDelete.hh"
#include "RunAction.hh"
using namespace std;
int main(int argc,char** argv)
{
G4Random::setTheEngine(new CLHEP::RanecuEngine);
#ifdef G4MULTITHREADED
G4MTRunManager* runManager = new G4MTRunManager;
int _numberOfThreads=G4Threading::G4GetNumberOfCores();
runManager->SetNumberOfThreads( _numberOfThreads);
#else
G4RunManager* runManager = new G4RunManager;
#endif
runManager->SetUserInitialization(new DetectorConstruction());
runManager->SetUserInitialization(new PhysicsList);
runManager->SetUserInitialization(new ActionInitialization()); 
#ifdef G4VIS_USE
G4VisManager* visManager = new G4VisExecutive;
//visManager->SetVerboseLevel(0);
visManager->Initialize();
#endif
G4UImanager* UImanager = G4UImanager::GetUIpointer();
if (argc!=1) {
G4String command = "/control/execute ";
G4String fileName = argv[1];
UImanager->ApplyCommand(command+fileName);
int _NumberOfRunningWorkerThreads=G4Threading::GetNumberOfRunningWorkerThreads();
DetectorConstruction * pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
int TotalNumberOfToBeProcessedEvents=pDetectorConstruction->NumberOfEventsPerThread*_NumberOfRunningWorkerThreads;
pDetectorConstruction-> NUMBER_OF_THREADS=_NumberOfRunningWorkerThreads;
runManager->SetEventModulo(pDetectorConstruction->NumberOfEventsPerThread);
runManager->BeamOn(TotalNumberOfToBeProcessedEvents);
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
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
