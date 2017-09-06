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
class G4tgrMessenger;
class   DetectorMessenger;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction( int NUMBER_OF_THREADS);
    virtual ~DetectorConstruction();
  //virtual void ConstructSDandField();
    virtual G4VPhysicalVolume* Construct();
    void SetNumberOfVoxelsAlongX(int );
    void SetNumberOfVoxelsAlongY(int );
    void SetNumberOfVoxelsAlongZ(int);
    void SetVoxalizedPhantomSizeY(G4double );
    void SetVoxalizedPhantomSizeX(G4double);
    void SetVoxalizedPhantomSizeZ(G4double);
    void SetReadOutGeometryCenterPosition(G4ThreeVector) ;
    void SetCenterVoxel_X_ID(G4int ) ;
    void SetCenterVoxel_Y_ID(G4int);
    void SetNomalizedPDDVoxel_Z_ID(G4int );
    void SetNomalizedPROFILEVoxel_X_ID(G4int );
    void READ_BEAM_DATA();
    void  READ_PHSP_DATA();
    void READ_EVENT_DATA();
    void SetupGeometry();
    void SetupDetectors();
    void SetGeneratorFlag(int );
    void SetNsplit( int);
    void SetNewZSTOP(G4double _ZSTOP);
    void SetH5PhaseSpaceFileName(G4String );
    int  GetNumberOfVoxelsAlongX();
    int  GetNumberOfVoxelsAlongY();
    int  GetNumberOfVoxelsAlongZ();
    int  GetVoxalizedPhantomSizeY() ;
    int  GetVoxalizedPhantomSizeX() ;
    int  GetVoxalizedPhantomSizeZ() ;
    int  GetCenterVoxel_X_ID();
    int  GetCenterVoxel_Y_ID();
    int  GetNomalizedPDDVoxel_Z_ID();
    int  GetNomalizedPROFILEVoxel_X_ID();
    void SetNameOfGeomFromTextFile(G4String);
    void SetGeomFromTextFlag(bool );
    void SetNumberOfEventsPerThread(int);
    G4ThreeVector  GetReadOutGeometryCenterPosition() ;
    G4ThreeVector ReadOutGeometryCenterPosition;
    G4double VoxalizedPhantomSizeX; 
    G4double VoxalizedPhantomSizeY; 
    G4double VoxalizedPhantomSizeZ;
    G4double  NewZSTOP;
    G4int numberOfVoxelsAlongX;
    G4int numberOfVoxelsAlongY; 
    G4int numberOfVoxelsAlongZ; 
    G4int CenterVoxel_X_ID;
    G4int CenterVoxel_Y_ID;
    int NUMBER_OF_THREADS;
    bool use_geom_from_text;
    G4String geom_file_name;
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
G4tgrMessenger * messenger; 
int Nsplit,GeneratorFlag,NumberOfEventsPerThread;
    typedef struct
    {
       int    PART_PDGE;
       double  PART_WEIGHT
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
         int    EVENT_ID,
                  NUMBER_OF_ENTRIES;


     }EventData;

  typedef struct
  {
     int    NUMBER_OF_HISORIES;
   G4double    Z_STOP;

  }BeamData;
 //
  PhspData *RAM_PhspData;
  EventData *RAM_EventData;
  //
  BeamData  myBeamData[1];
};

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

#endif

