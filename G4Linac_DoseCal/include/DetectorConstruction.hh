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
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class PhantomROGeometry;
class PhantomSD;
class G4Material;
class G4Box;
class   DetectorMessenger;
/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction( int NUMBER_OF_THREADS);
    virtual ~DetectorConstruction();
  //virtual void ConstructSDandField();
    virtual G4VPhysicalVolume* Construct();
    void SetNumberOfVoxelsAlongX(int _numberOfVoxelsAlongX);
    void SetNumberOfVoxelsAlongY(int _numberOfVoxelsAlongY);
    void SetNumberOfVoxelsAlongZ(int _numberOfVoxelsAlongZ);
    void SetPhantomSizeY(G4double _phantomSizeY);
    void SetPhantomSizeX(G4double _phantomSizeX);
    void SetPhantomSizeZ(G4double _phantomSizeZ);
    void SetReadOutGeometryCenterPosition(G4ThreeVector _ReadOutGeometryCenterPosition) ;
    void SetCenterVoxel_X_ID(G4int _CenterVoxel_X_ID) ;
    void SetCenterVoxel_Y_ID(G4int _CenterVoxel_Y_ID);
    void SetNomalizedPDDVoxel_Z_ID(G4int _NomalizedPDDVoxel_Z_ID);
    void SetNomalizedPROFILEVoxel_X_ID(G4int _NomalizedPROFILEVoxel_X_ID);
    void READ_BEAM_DATA();
    void  READ_PHSP_DATA();
    void READ_EVENT_DATA();
    void SetupGeometry();
    void SetupDetectors();
    void SetNewZSTOP(G4double _ZSTOP);
    void SetH5PhaseSpaceFileName(G4String _Filename);
    int  GetNumberOfVoxelsAlongX();
    int  GetNumberOfVoxelsAlongY();
    int  GetNumberOfVoxelsAlongZ();
    int  GetPhantomSizeY() ;
    int  GetPhantomSizeX() ;
    int  GetPhantomSizeZ() ;
    int  GetCenterVoxel_X_ID();
    int  GetCenterVoxel_Y_ID();
    int  GetNomalizedPDDVoxel_Z_ID();
    int  GetNomalizedPROFILEVoxel_X_ID();
    G4ThreeVector  GetReadOutGeometryCenterPosition() ;
    G4ThreeVector ReadOutGeometryCenterPosition;
    G4double phantomSizeX; //Phantom XSize
    G4double phantomSizeY; //Phantom YSize
    G4double phantomSizeZ; //Phantom ZSize
    G4double  NewZSTOP;
    G4int numberOfVoxelsAlongX; //Number of voxels along x axis
    G4int numberOfVoxelsAlongY; //Number of voxels along y axis
    G4int numberOfVoxelsAlongZ; //Number of voxels along z axis
    G4int CenterVoxel_X_ID;
    G4int CenterVoxel_Y_ID;
    int NUMBER_OF_THREADS;
    G4int NomalizedPDDVoxel_Z_ID;
    G4int NomalizedPROFILEVoxel_X_ID;
    G4String sensitiveDetectorName; 
    G4VPhysicalVolume *physWorld;
    G4Box* solidWorld  ;
    PhantomSD* mPhantomSD;//pointer to sensitive detector
    PhantomROGeometry* phantomROGeometry;//pointer to ROGeometry
    std::string H5PhaseSpaceFileName;
    G4Box* solidDetector ;
    G4LogicalVolume* logicdDetector ;
    G4LogicalVolume* logicWorld;
    G4Material* phantom_mat;
    G4bool             fConstructed;
    G4VPhysicalVolume* pDetector ;
    static G4ThreadLocal G4bool fConstructedSDandField;
  DetectorMessenger * pDetectorMessenger;

    typedef struct
    {
       int    PART_PDGE;
       float  PART_WEIGHT
                ,PART_POS_X
                ,PART_POS_Y
                ,PART_POS_Z
                ,PART_DIR_X
                ,PART_DIR_Y
                ,PART_DIR_Z
                ,PART_KINETIC;


    }PhspData;

     typedef struct
     {
         G4int    EVENT_ID,
                  NUMBER_OF_ENTRIES;


     }EventData;

  typedef struct
  {
     G4int    NUMBER_OF_HISORIES;
   G4float     Z_STOP;

  }BeamData;
 //
  PhspData *RAM_PhspData;
  EventData *RAM_EventData;
  //
  BeamData  myBeamData[1];
};

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

#endif

