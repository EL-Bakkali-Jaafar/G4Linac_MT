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
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "DetectorROGeometry.hh"
#include "PhantomSD.hh"
#include "G4NistManager.hh"
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorROGeometry::DetectorROGeometry(G4String aString)
  : G4VUserParallelWorld(aString),RODetector(0),RODetectorXDivision(0),
    RODetectorYDivision(0),RODetectorZDivision(0),worldLogical(0),RODetectorLog(0),
    RODetectorXDivisionLog(0),RODetectorYDivisionLog(0),RODetectorZDivisionLog(0),
    sensitiveLogicalVolume(0)
{
  isBuilt = false;
  isInitialized = false;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void DetectorROGeometry::Initialize(G4ThreeVector pos,
						 G4double detectorDimX,
						 G4double detectorDimY,
						 G4double detectorDimZ,
						 G4int numberOfVoxelsX,
						 G4int numberOfVoxelsY,
						 G4int numberOfVoxelsZ)
{  
  detectorToWorldPosition = pos;
  detectorSizeX = detectorDimX;
  detectorSizeY= detectorDimY;
  detectorSizeZ=detectorDimZ;
  numberOfVoxelsAlongX=numberOfVoxelsX;
  numberOfVoxelsAlongY=numberOfVoxelsY;
  numberOfVoxelsAlongZ=numberOfVoxelsZ;

  isInitialized = true;


  
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorROGeometry::UpdateROGeometry()
{
  //Nothing happens if the RO geometry is not built. But parameters are properly set.
  if (!isBuilt)
    {
      //G4Exception("DetectorROGeometry::UpdateROGeometry","had001",
      //		  JustWarning,"Cannot update geometry before it is built");
      return;
    }
 
  //1) Update the dimensions of the G4Boxes
  G4double halfDetectorSizeX = detectorSizeX;
  G4double halfDetectorSizeY = detectorSizeY;
  G4double halfDetectorSizeZ = detectorSizeZ;

  RODetector->SetXHalfLength(halfDetectorSizeX);
  RODetector->SetYHalfLength(halfDetectorSizeY);
  RODetector->SetZHalfLength(halfDetectorSizeZ);

  G4double halfXVoxelSizeX = halfDetectorSizeX/numberOfVoxelsAlongX;
  G4double halfXVoxelSizeY = halfDetectorSizeY;
  G4double halfXVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelXThickness = 2*halfXVoxelSizeX;
  
  RODetectorXDivision->SetXHalfLength(halfXVoxelSizeX);
  RODetectorXDivision->SetYHalfLength(halfXVoxelSizeY);
  RODetectorXDivision->SetZHalfLength(halfXVoxelSizeZ);

  G4double halfYVoxelSizeX = halfXVoxelSizeX;
  G4double halfYVoxelSizeY = halfDetectorSizeY/numberOfVoxelsAlongY;
  G4double halfYVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelYThickness = 2*halfYVoxelSizeY;

  RODetectorYDivision->SetXHalfLength(halfYVoxelSizeX);
  RODetectorYDivision->SetYHalfLength(halfYVoxelSizeY);
  RODetectorYDivision->SetZHalfLength(halfYVoxelSizeZ);

  G4double halfZVoxelSizeX = halfXVoxelSizeX;
  G4double halfZVoxelSizeY = halfYVoxelSizeY;
  G4double halfZVoxelSizeZ = halfDetectorSizeZ/numberOfVoxelsAlongZ;
  G4double voxelZThickness = 2*halfZVoxelSizeZ;

  RODetectorZDivision->SetXHalfLength(halfZVoxelSizeX);
  RODetectorZDivision->SetYHalfLength(halfZVoxelSizeY);
  RODetectorZDivision->SetZHalfLength(halfZVoxelSizeZ);

  //Delete and re-build the relevant physical volumes
  G4PhysicalVolumeStore* store =
    G4PhysicalVolumeStore::GetInstance();

  //Delete...
  G4VPhysicalVolume* myVol = store->GetVolume("RODetectorPhys");
  store->DeRegister(myVol);
  //..and rebuild
  G4VPhysicalVolume *RODetectorPhys = new G4PVPlacement(0,
							detectorToWorldPosition,
							RODetectorLog,
							"RODetectorPhys",
							worldLogical,							
							false,0);

  myVol = store->GetVolume("RODetectorXDivisionPhys");
  store->DeRegister(myVol);
  G4VPhysicalVolume *RODetectorXDivisionPhys = new G4PVReplica("RODetectorXDivisionPhys",
							       RODetectorXDivisionLog,
							       RODetectorPhys,
							       kXAxis,
							       numberOfVoxelsAlongX,
							       voxelXThickness);
  myVol = store->GetVolume("RODetectorYDivisionPhys");
  store->DeRegister(myVol);
  G4VPhysicalVolume *RODetectorYDivisionPhys = new G4PVReplica("RODetectorYDivisionPhys",
							       RODetectorYDivisionLog,
							       RODetectorXDivisionPhys,
							       kYAxis,
							       numberOfVoxelsAlongY,
							       voxelYThickness);
  
  myVol = store->GetVolume("RODetectorZDivisionPhys");
  store->DeRegister(myVol);
  new G4PVReplica("RODetectorZDivisionPhys",
		  RODetectorZDivisionLog,
		  RODetectorYDivisionPhys,
		  kZAxis,
		  numberOfVoxelsAlongZ,
		  voxelZThickness);

  return;

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorROGeometry::~DetectorROGeometry()
{



;}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorROGeometry::Construct()
{

  G4VPhysicalVolume* ghostWorld = GetWorld();
  worldLogical = ghostWorld->GetLogicalVolume();
  G4double halfDetectorSizeX = detectorSizeX;
  G4double halfDetectorSizeY = detectorSizeY;
  G4double halfDetectorSizeZ = detectorSizeZ;
   
  RODetector = new G4Box("RODetector", 
			 halfDetectorSizeX, 
			 halfDetectorSizeY, 
			 halfDetectorSizeZ);
  
  RODetectorLog = new G4LogicalVolume(RODetector,
				      0,
				      "RODetectorLog",
				      0,0,0);
  
  
  
  G4VPhysicalVolume *RODetectorPhys = new G4PVPlacement(0,
							detectorToWorldPosition,RODetectorLog,
							"RODetectorPhys",
							worldLogical,							
							false,0);


  G4NistManager* nist = G4NistManager::Instance();
G4Material * phantom_mat         = nist->FindOrBuildMaterial("G4_WATER");// Tungesten

  
  G4double halfXVoxelSizeX = halfDetectorSizeX/numberOfVoxelsAlongX;
  G4double halfXVoxelSizeY = halfDetectorSizeY;
  G4double halfXVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelXThickness = 2*halfXVoxelSizeX;
  

  RODetectorXDivision = new G4Box("RODetectorXDivision",
				  halfXVoxelSizeX,
				  halfXVoxelSizeY,
				  halfXVoxelSizeZ);
  
  RODetectorXDivisionLog = new G4LogicalVolume(RODetectorXDivision,
					      phantom_mat ,
					       "RODetectorXDivisionLog",
					       0,0,0);

  G4VPhysicalVolume *RODetectorXDivisionPhys = new G4PVReplica("RODetectorXDivisionPhys",
                                                              RODetectorXDivisionLog,
                                                              RODetectorPhys,
                                                              kXAxis,
                                                              numberOfVoxelsAlongX,
                                                              voxelXThickness);


  G4double halfYVoxelSizeX = halfXVoxelSizeX;
  G4double halfYVoxelSizeY = halfDetectorSizeY/numberOfVoxelsAlongY;
  G4double halfYVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelYThickness = 2*halfYVoxelSizeY;

  RODetectorYDivision = new G4Box("RODetectorYDivision",
				  halfYVoxelSizeX, 
				  halfYVoxelSizeY,
				  halfYVoxelSizeZ);

  RODetectorYDivisionLog = new G4LogicalVolume(RODetectorYDivision,
					       phantom_mat ,
					       "RODetectorYDivisionLog",
					       0,0,0);
 
  G4VPhysicalVolume *RODetectorYDivisionPhys = new G4PVReplica("RODetectorYDivisionPhys",
							      RODetectorYDivisionLog,
							      RODetectorXDivisionPhys,
							      kYAxis,
							      numberOfVoxelsAlongY,
							      voxelYThickness);
  

  G4double halfZVoxelSizeX = halfXVoxelSizeX;
  G4double halfZVoxelSizeY = halfYVoxelSizeY;
  G4double halfZVoxelSizeZ = halfDetectorSizeZ/numberOfVoxelsAlongZ;
  G4double voxelZThickness = 2*halfZVoxelSizeZ;
 
  RODetectorZDivision = new G4Box("RODetectorZDivision",
				  halfZVoxelSizeX,
				  halfZVoxelSizeY, 
				  halfZVoxelSizeZ);
 
  RODetectorZDivisionLog = new G4LogicalVolume(RODetectorZDivision,
					       phantom_mat ,
					       "RODetectorZDivisionLog",
					       0,0,0);
 
  new G4PVReplica("RODetectorZDivisionPhys",
		  RODetectorZDivisionLog,
		  RODetectorYDivisionPhys,
		  kZAxis,
		  numberOfVoxelsAlongZ,
		  voxelZThickness);

  this->sensitiveLogicalVolume = RODetectorZDivisionLog;
  isBuilt = true;


}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorROGeometry::ConstructSD()
{
 
G4String sensitiveDetectorName = "PhantomROG";
PhantomSD *mPhantomSD = new PhantomSD(sensitiveDetectorName);
G4SDManager::GetSDMpointer()->AddNewDetector(mPhantomSD);
SetSensitiveDetector( sensitiveLogicalVolume,mPhantomSD);

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
