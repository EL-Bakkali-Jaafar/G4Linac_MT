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
#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorMessenger::DetectorMessenger(DetectorConstruction* pDetectorConstruction)
: G4UImessenger(),fDetectorConstruction(pDetectorConstruction)
{
  DetectorDir = new G4UIdirectory("/Parameters/");
  DetectorDir->SetGuidance("............................");
    H5PhaseSpace_ZSTOPCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/ZSTOP",this);  
  H5PhaseSpace_ZSTOPCmd->SetGuidance("Set ZSTOP.");
  H5PhaseSpace_ZSTOPCmd->SetParameterName("ZSTOP",false);
  H5PhaseSpace_ZSTOPCmd->SetUnitCategory("Length");
  H5PhaseSpace_ZSTOPCmd->SetRange("");
  H5PhaseSpace_ZSTOPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


 H5PhaseSpace_NameCmd = new G4UIcmdWithAString("/Parameters/H5PhaseSpaceName",this);
 H5PhaseSpace_NameCmd->SetGuidance("");
 H5PhaseSpace_NameCmd->SetParameterName("H5PhaseSpaceName",false);
 H5PhaseSpace_NameCmd->SetDefaultValue("");
  H5PhaseSpace_ZSTOPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  phantomSizeXCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/VoxalizedPhantomSizeX",this);  
  phantomSizeXCmd->SetGuidance("Set VoxalizedPhantom Size along X axis.");
  phantomSizeXCmd->SetParameterName("VoxalizedPhantomSizeX",false);
  phantomSizeXCmd->SetUnitCategory("Length");
  phantomSizeXCmd->SetRange("VoxalizedPhantomSizeX>0.0");
  phantomSizeXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

 
  phantomSizeYCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/VoxalizedPhantomSizeY",this);  
  phantomSizeYCmd->SetGuidance("Set VoxalizedPhantom Size along Y axis.");
  phantomSizeYCmd->SetParameterName("VoxalizedPhantomSizeY",false);
  phantomSizeYCmd->SetUnitCategory("Length");
  phantomSizeYCmd->SetRange("VoxalizedPhantomSizeY>0.0");
  phantomSizeYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



 
  phantomSizeZCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/VoxalizedPhantomSizeZ",this);  
  phantomSizeZCmd->SetGuidance("Set VoxalizedPhantom Size along Z axis.");
  phantomSizeZCmd->SetParameterName("VoxalizedPhantomSizeZ",false);
  phantomSizeZCmd->SetUnitCategory("Length");
  phantomSizeZCmd->SetRange("VoxalizedPhantomSizeZ>0.0");
  phantomSizeZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


 
  numberOfVoxelsAlongXCmd = new G4UIcmdWithAnInteger("/Parameters/numberOfVoxelsAlongX",this);  
  numberOfVoxelsAlongXCmd->SetGuidance("Set number Of Voxels along X axis.");
  numberOfVoxelsAlongXCmd->SetParameterName("numberOfVoxelsAlongX",false);
  numberOfVoxelsAlongXCmd->SetRange("numberOfVoxelsAlongX>0");
  numberOfVoxelsAlongXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  numberOfVoxelsAlongYCmd = new G4UIcmdWithAnInteger("/Parameters/numberOfVoxelsAlongY",this);  
  numberOfVoxelsAlongYCmd->SetGuidance("Set number Of Voxels along Y axis.");
  numberOfVoxelsAlongYCmd->SetParameterName("numberOfVoxelsAlongY",false);
  numberOfVoxelsAlongYCmd->SetRange("numberOfVoxelsAlongY>0");
  numberOfVoxelsAlongYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  numberOfVoxelsAlongZCmd = new G4UIcmdWithAnInteger("/Parameters/numberOfVoxelsAlongZ",this);  
  numberOfVoxelsAlongZCmd->SetGuidance("Set number Of Voxels along Z axis.");
  numberOfVoxelsAlongZCmd->SetParameterName("numberOfVoxelsAlongZ",false);
  numberOfVoxelsAlongZCmd->SetRange("numberOfVoxelsAlongZ>0");
  numberOfVoxelsAlongZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



  ROGcenterPosCmd = new G4UIcmdWith3VectorAndUnit("/Parameters/ROGcenterPos",this);  
  ROGcenterPosCmd->SetGuidance("SET ROGcenterPos.");
  ROGcenterPosCmd->SetParameterName("ROGcenterPosX","ROGcenterPosY","ROGcenterPosZ",false,false);
  ROGcenterPosCmd->SetUnitCategory("Length");
  ROGcenterPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  NSPLITCmd = new G4UIcmdWithAnInteger("/Parameters/Nsplit",this);  
  NSPLITCmd->SetGuidance("Set NSPLIT");
  NSPLITCmd->SetParameterName("Nsplit",false);
  NSPLITCmd->SetRange("Nsplit>=0");
  NSPLITCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GENERATOR_FLAG_Cmd = new G4UIcmdWithAnInteger("/Parameters/GeneratorFlag",this);  
  GENERATOR_FLAG_Cmd ->SetGuidance("Set GeneratorFlag.");
  GENERATOR_FLAG_Cmd ->SetParameterName("GeneratorFlag",false);
  GENERATOR_FLAG_Cmd ->SetRange("GeneratorFlag>=0");
  GENERATOR_FLAG_Cmd ->AvailableForStates(G4State_PreInit,G4State_Idle);

  NameOfGeomFromTextFileCmd = new G4UIcmdWithAString("/Parameters/NameOfGeomFromTextFile",this);
  NameOfGeomFromTextFileCmd ->SetParameterName("NameOfGeomFromTextFile",false);
  NameOfGeomFromTextFileCmd ->SetDefaultValue("");

  NumberOfEventsPerThread_Cmd = new G4UIcmdWithAnInteger("/Parameters/NumberOfEventsPerThread",this);  
  NumberOfEventsPerThread_Cmd->SetGuidance("Set NumberOfEventsPerThread.");
  NumberOfEventsPerThread_Cmd ->SetParameterName("NumberOfEventsPerThread",false);
  NumberOfEventsPerThread_Cmd ->SetRange("NumberOfEventsPerThread>=0");
  NumberOfEventsPerThread_Cmd ->AvailableForStates(G4State_PreInit,G4State_Idle);


 
  GantryRotAngleCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/GantryRotAngle",this);  
  GantryRotAngleCmd->SetGuidance("GantryRotAngle.");
  GantryRotAngleCmd->SetParameterName("GantryRotAngle",false);
  GantryRotAngleCmd->SetUnitCategory("Angle");
  GantryRotAngleCmd->SetRange("GantryRotAngle>=0.0");
  GantryRotAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

 
  GantryRotAngleFlagCmd = new G4UIcmdWithABool("/Parameters/GantryRotAngleFlag",this);  
  GantryRotAngleFlagCmd->SetGuidance("GantryRotAngleFlag.");
  GantryRotAngleFlagCmd->SetParameterName("GantryRotAngleFlag",false);
  GantryRotAngleFlagCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



  CollimatorRotAngleCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/CollimatorRotAngle",this);  
  CollimatorRotAngleCmd->SetGuidance("CollimatorRotAngle.");
  CollimatorRotAngleCmd->SetParameterName("CollimatorRotAngle",false);
  CollimatorRotAngleCmd->SetUnitCategory("Angle");
  CollimatorRotAngleCmd->SetRange("CollimatorRotAngle>=0.0");
  CollimatorRotAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



 
  CollimatorRotAngleFlagCmd = new G4UIcmdWithABool("/Parameters/CollimatorRotAngleFlag",this);  
  CollimatorRotAngleFlagCmd->SetGuidance("CollimatorRotAngleFlag.");
  CollimatorRotAngleFlagCmd->SetParameterName("CollimatorRotAngleFlag",false);
  CollimatorRotAngleFlagCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



  
  StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/StepMaxValue",this);  
  StepMaxCmd->SetGuidance("Set StepMaxValue.");
  StepMaxCmd->SetParameterName("StepMaxValue",false);
  StepMaxCmd->SetUnitCategory("Length");
  StepMaxCmd->SetRange("StepMaxValue>0.0");
  StepMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

 


  StepMaxFlagCmd = new G4UIcmdWithABool("/Parameters/DefineStepMax",this);  
  StepMaxFlagCmd->SetGuidance("DefineStepMax.");
  StepMaxFlagCmd->SetParameterName("DefineStepMax",false);
  StepMaxFlagCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorMessenger::~DetectorMessenger()
{
  delete ROGcenterPosCmd;
  delete numberOfVoxelsAlongZCmd;
  delete numberOfVoxelsAlongYCmd;
  delete numberOfVoxelsAlongXCmd;
  delete phantomSizeXCmd;
  delete phantomSizeYCmd;
  delete phantomSizeZCmd; 
  delete DetectorDir;    
  delete H5PhaseSpace_NameCmd;
  delete H5PhaseSpace_ZSTOPCmd;
  delete NameOfGeomFromTextFileCmd;
  delete GENERATOR_FLAG_Cmd;
  delete NSPLITCmd;
  delete NumberOfEventsPerThread_Cmd;
  delete GantryRotAngleCmd;
  delete GantryRotAngleFlagCmd;
  delete CollimatorRotAngleFlagCmd;
  delete CollimatorRotAngleCmd;
  delete StepMaxCmd;
  delete StepMaxFlagCmd;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{       
if( command == phantomSizeXCmd )
   { fDetectorConstruction->SetVoxalizedPhantomSizeX(phantomSizeXCmd->GetNewDoubleValue(newValue));}
  

else if( command == GantryRotAngleCmd )
   { fDetectorConstruction->SetGantryRotAngle(GantryRotAngleCmd->GetNewDoubleValue(newValue));
}
 

else if( command == CollimatorRotAngleCmd )
   { fDetectorConstruction->SetCollimatorRotAngle(CollimatorRotAngleCmd->GetNewDoubleValue(newValue));
}
 
else if( command == GantryRotAngleFlagCmd )
   { fDetectorConstruction->SetGantryRotAngleFlag(GantryRotAngleFlagCmd->GetNewBoolValue(newValue));
}
  
else if( command == CollimatorRotAngleFlagCmd )
   { fDetectorConstruction->SetCollimatorRotAngleFlag(CollimatorRotAngleFlagCmd->GetNewBoolValue(newValue));
}
else if( command == phantomSizeYCmd )
   { fDetectorConstruction->SetVoxalizedPhantomSizeY(phantomSizeYCmd->GetNewDoubleValue(newValue));
}
  else if( command == NSPLITCmd )
   { fDetectorConstruction->SetNsplit(NSPLITCmd->GetNewIntValue(newValue));}
     
  else if( command == GENERATOR_FLAG_Cmd )
   { fDetectorConstruction->SetGeneratorFlag(GENERATOR_FLAG_Cmd->GetNewIntValue(newValue));}
      
else if( command == phantomSizeZCmd )
   { fDetectorConstruction->SetVoxalizedPhantomSizeZ(phantomSizeZCmd->GetNewDoubleValue(newValue));}
     
else if( command == numberOfVoxelsAlongZCmd )
   { fDetectorConstruction->SetNumberOfVoxelsAlongZ(numberOfVoxelsAlongZCmd->GetNewIntValue(newValue));}
     
else if( command == numberOfVoxelsAlongXCmd )
   { fDetectorConstruction->SetNumberOfVoxelsAlongX(numberOfVoxelsAlongXCmd->GetNewIntValue(newValue));}
     
else if( command == numberOfVoxelsAlongYCmd )
   { fDetectorConstruction->SetNumberOfVoxelsAlongY(numberOfVoxelsAlongYCmd->GetNewIntValue(newValue));}

 else  if( command == ROGcenterPosCmd )
   { fDetectorConstruction->SetReadOutGeometryCenterPosition(ROGcenterPosCmd->GetNew3VectorValue(newValue));}
    
 else  if( command == H5PhaseSpace_ZSTOPCmd )
   {
 fDetectorConstruction->SetNewZSTOP(H5PhaseSpace_ZSTOPCmd->GetNewDoubleValue(newValue));
}    
 else  if( command == H5PhaseSpace_NameCmd )
   { 
fDetectorConstruction->SetH5PhaseSpaceFileName(newValue);
}   
else  if( command == NameOfGeomFromTextFileCmd )
{ fDetectorConstruction->SetNameOfGeomFromTextFile(newValue);}
  
 else  if( command == NumberOfEventsPerThread_Cmd ){
   fDetectorConstruction-> SetNumberOfEventsPerThread(NumberOfEventsPerThread_Cmd->GetNewIntValue(newValue));
     }  

   
  if( command == StepMaxCmd )
   { fDetectorConstruction->SetStepMax(StepMaxCmd->GetNewDoubleValue(newValue));}

else if( command == StepMaxFlagCmd )
   { fDetectorConstruction->SetStepMaxFlag(StepMaxFlagCmd->GetNewBoolValue(newValue));
}

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
