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
 * see http://G4Linac_MT.GitHub.com
 *
 * - 23/07/2017: public version 2.0
 *
--------------------------------------------------------------------------------------------
*/
#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
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
  phantomSizeXCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/phantomSizeX",this);  
  phantomSizeXCmd->SetGuidance("Set phantom Size along X axis.");
  phantomSizeXCmd->SetParameterName("phantomSizeX",false);
  phantomSizeXCmd->SetUnitCategory("Length");
  phantomSizeXCmd->SetRange("phantomSizeX>0.0");
  phantomSizeXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

 
  phantomSizeYCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/phantomSizeY",this);  
  phantomSizeYCmd->SetGuidance("Set phantom Size along Y axis.");
  phantomSizeYCmd->SetParameterName("phantomSizeY",false);
  phantomSizeYCmd->SetUnitCategory("Length");
  phantomSizeYCmd->SetRange("phantomSizeY>0.0");
  phantomSizeYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



 
  phantomSizeZCmd = new G4UIcmdWithADoubleAndUnit("/Parameters/phantomSizeZ",this);  
  phantomSizeZCmd->SetGuidance("Set phantom Size along Z axis.");
  phantomSizeZCmd->SetParameterName("phantomSizeZ",false);
  phantomSizeZCmd->SetUnitCategory("Length");
  phantomSizeZCmd->SetRange("phantomSizeZ>0.0");
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




  CenterVoxel_Y_IDCmd = new G4UIcmdWithAnInteger("/Parameters/CenterVoxel_Y_ID",this);  
  CenterVoxel_Y_IDCmd->SetGuidance("Set CenterVoxel_Y_ID.");
  CenterVoxel_Y_IDCmd->SetParameterName("CenterVoxel_Y_ID",false);
  CenterVoxel_Y_IDCmd->SetRange("CenterVoxel_Y_ID>=0");
  CenterVoxel_Y_IDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  CenterVoxel_X_IDCmd = new G4UIcmdWithAnInteger("/Parameters/CenterVoxel_X_ID",this);  
  CenterVoxel_X_IDCmd->SetGuidance("SetCenterVoxel_X_ID.");
  CenterVoxel_X_IDCmd->SetParameterName("CenterVoxel_X_ID",false);
  CenterVoxel_X_IDCmd->SetRange("CenterVoxel_X_ID>=0");
  CenterVoxel_X_IDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);





  NomalizedPDDVoxel_Z_IDCmd = new G4UIcmdWithAnInteger("/Parameters/NomalizedPDDVoxel_Z_ID",this);  
  NomalizedPDDVoxel_Z_IDCmd->SetGuidance("SetNomalizedPDDVoxel_Z_ID.");
  NomalizedPDDVoxel_Z_IDCmd->SetParameterName("NomalizedPDDVoxel_Z_ID",false);
  NomalizedPDDVoxel_Z_IDCmd->SetRange("NomalizedPDDVoxel_Z_ID>=0");
  NomalizedPDDVoxel_Z_IDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



  NomalizedPROFILEVoxel_X_IDCmd = new G4UIcmdWithAnInteger("/Parameters/NomalizedPROFILEVoxel_X_ID",this);  
  NomalizedPROFILEVoxel_X_IDCmd->SetGuidance("SetNomalizedPROFILEVoxel_X_ID.");
  NomalizedPROFILEVoxel_X_IDCmd->SetParameterName("NomalizedPROFILEVoxel_X_ID",false);
  NomalizedPROFILEVoxel_X_IDCmd->SetRange("NomalizedPROFILEVoxel_X_ID>=0");
  NomalizedPROFILEVoxel_X_IDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



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
  delete CenterVoxel_X_IDCmd;    
  delete CenterVoxel_Y_IDCmd;    
  delete NomalizedPDDVoxel_Z_IDCmd; 
  delete NomalizedPROFILEVoxel_X_IDCmd; 
  delete DetectorDir;    
  delete H5PhaseSpace_NameCmd;
  delete H5PhaseSpace_ZSTOPCmd;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{       
if( command == phantomSizeXCmd )
   { fDetectorConstruction->SetPhantomSizeX(phantomSizeXCmd->GetNewDoubleValue(newValue));}
     
else if( command == phantomSizeYCmd )
   { fDetectorConstruction->SetPhantomSizeY(phantomSizeYCmd->GetNewDoubleValue(newValue));


}
     
else if( command == phantomSizeZCmd )
   { fDetectorConstruction->SetPhantomSizeZ(phantomSizeZCmd->GetNewDoubleValue(newValue));}
     
else if( command == numberOfVoxelsAlongZCmd )
   { fDetectorConstruction->SetNumberOfVoxelsAlongZ(numberOfVoxelsAlongZCmd->GetNewIntValue(newValue));}
     
else if( command == numberOfVoxelsAlongXCmd )
   { fDetectorConstruction->SetNumberOfVoxelsAlongX(numberOfVoxelsAlongXCmd->GetNewIntValue(newValue));}
     
else if( command == numberOfVoxelsAlongYCmd )
   { fDetectorConstruction->SetNumberOfVoxelsAlongY(numberOfVoxelsAlongYCmd->GetNewIntValue(newValue));}

else if( command == CenterVoxel_X_IDCmd )
   { fDetectorConstruction->SetCenterVoxel_X_ID(CenterVoxel_X_IDCmd->GetNewIntValue(newValue));}
     
else if( command == CenterVoxel_Y_IDCmd )
   { fDetectorConstruction->SetCenterVoxel_Y_ID(CenterVoxel_Y_IDCmd->GetNewIntValue(newValue));}
     
else if( command == NomalizedPDDVoxel_Z_IDCmd )
   { fDetectorConstruction->SetNomalizedPDDVoxel_Z_ID(NomalizedPDDVoxel_Z_IDCmd->GetNewIntValue(newValue));}

   else if( command ==  NomalizedPROFILEVoxel_X_IDCmd )
   { fDetectorConstruction->SetNomalizedPROFILEVoxel_X_ID(NomalizedPROFILEVoxel_X_IDCmd->GetNewIntValue(newValue));}

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
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
