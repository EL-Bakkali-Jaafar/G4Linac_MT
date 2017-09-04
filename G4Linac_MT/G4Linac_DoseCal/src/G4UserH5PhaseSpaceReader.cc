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
#include "G4UserH5PhaseSpaceReader.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4Threading.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#ifndef H5_NO_NAMESPACE
#ifndef H5_NO_STD
using std::cout;
using std::endl;
#endif  // H5_NO_STD
#endif
#include "H5Cpp.h"
#ifndef H5_NO_NAMESPACE
using namespace H5;
#endif
const std::string DatasetName_histories("BeamData"),
                  MEMBER_HISTORIES("_NUMBER_OF_HISTORIES"),
                  MEMBER_Z_STOP("_Z_STOP"),
                  DatasetName_event("EventData"),
                  MEMBER_ENTERIES("_ENTERIES"),
                  MEMBER_EVENTID("_EVENTID"),
                  DatasetName("PhspData"),
                  MEMBER_PART_PDGE("_PART_PDGE"),
                  MEMBER_PART_WEIGHT("_PART_WEIGHT"),
                  MEMBER_PART_POS_X("_PART_POS_X"),
                  MEMBER_PART_POS_Y("_PART_POS_Y"),
                  MEMBER_PART_POS_Z("_PART_POS_Z"),
                  MEMBER_PART_DIR_X("_PART_DIR_X"),
                  MEMBER_PART_DIR_Y("_PART_DIR_Y"),
                  MEMBER_PART_DIR_Z("_PART_DIR_Z"),
                  MEMBER_PART_KINETIC("_PART_KINETIC");
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::Local_ITERATOR;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::NUMBER_OF_TIME_OF_REUSE_PHASE_SPACE_FILE;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::ID_OF_NEXT_EVENT;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::ITERATOR;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::Event_ID;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::First_ID_Of_Event_In_Thread;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::INDEX_OF_CURRENT_DATA;
G4ThreadLocal  int  G4UserH5PhaseSpaceReader::event_data_length;
G4ThreadLocal  int phsp_event_id;
G4ThreadLocal  bool G4UserH5PhaseSpaceReader::AUTORIZED;


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4UserH5PhaseSpaceReader::G4UserH5PhaseSpaceReader()
: G4VPrimaryGenerator()

{
G4RunManager* runManager = G4RunManager::GetRunManager();
 pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
INDEX_OF_CURRENT_DATA=0;
event_data_length=0;
ID_OF_NEXT_EVENT=0;
phsp_event_id=0;
this->apply=false;
Local_ITERATOR=-1;
NUMBER_OF_TIME_OF_REUSE_PHASE_SPACE_FILE=1;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4UserH5PhaseSpaceReader::~G4UserH5PhaseSpaceReader()
{

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

void G4UserH5PhaseSpaceReader::SET_First_ID_Of_Event_In_Thread(int _First_ID_Of_Event_In_Thread ){
this->First_ID_Of_Event_In_Thread=_First_ID_Of_Event_In_Thread;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void G4UserH5PhaseSpaceReader::GeneratePrimaryVertex(G4Event*anEvent)
{
auto id_thread = std::to_string(G4Threading::G4GetThreadId()); 
//_______________SHOW THE FIRST EVENT ID IN EACH THREAD_______________________________________
if (AUTORIZED==false) {
this-> NUMBER_OF_SIMULATED_HISTORIES=pDetectorConstruction->myBeamData[0].NUMBER_OF_HISORIES;
this-> Z_STOP*=mm;
this-> Z_STOP= pDetectorConstruction->NewZSTOP;

AUTORIZED=false;

G4cout<<" Thread ID "<<   id_thread << "  First event ID "  << anEvent->GetEventID() <<G4endl;
SET_First_ID_Of_Event_In_Thread(anEvent->GetEventID());
}
AUTORIZED=true;
//_____________________________________________________________________________________________


Local_ITERATOR++;

//// recycling phase space

if (Local_ITERATOR== this-> NUMBER_OF_SIMULATED_HISTORIES-1) 
{Local_ITERATOR=0;
//G4cout<<"Phase space recycled "<<NUMBER_OF_TIME_OF_REUSE_PHASE_SPACE_FILE++<<" times"<< " in thread ID : " <<  id_thread  <<G4endl;

}

//Event_ID                =   this->First_ID_Of_Event_In_Thread+Local_ITERATOR;
//
//if (Local_ITERATOR==pDetectorConstruction->RAM_EventData[phsp_event_id].EVENT_ID)
{
Number_of_Entries       =    pDetectorConstruction->RAM_EventData[phsp_event_id].NUMBER_OF_ENTRIES;
//G4cout<<"Number_of_Entries " <<Number_of_Entries <<G4endl;
//G4cout<<"Event_ID " <<Event_ID <<G4endl;
switch (this->EVENT_GENERATION_FLAG)
{
case 0:
GENERATE_NEW_PARTICLE(Local_ITERATOR,anEvent);
phsp_event_id++;
break;
case 1:
GENERATE_NEW_PART_ROT_SPLITTING(Local_ITERATOR,anEvent);
phsp_event_id++;
break;
case 2:
GENERATE_NEW_PART_SPLITTING(Local_ITERATOR,anEvent);
phsp_event_id++;
break;
}

}
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

void G4UserH5PhaseSpaceReader:: GENERATE_NEW_PART_SPLITTING(int ITERATOR,G4Event*& anEvent){

    this->energy           *=MeV;
    this->pos_x            *=mm;
    this->pos_y            *=mm;

    this->dir_x            *=mm;
    this->dir_y            *=mm;
    this->dir_z            *=mm;

    for (INDEX_OF_CURRENT_DATA=0+ITERATOR; INDEX_OF_CURRENT_DATA<Number_of_Entries+ITERATOR;INDEX_OF_CURRENT_DATA++){

         this->particle_pdge   = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_PDGE;
         this->particle_weight = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_WEIGHT;
         this->energy          = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_KINETIC;
         this->pos_x           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_POS_X;
         this->pos_y           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_POS_Y;
         this->pos_z           = this-> Z_STOP;
         this->dir_x           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_X;
         this->dir_y           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_Y;
         this->dir_z           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_Z;

        G4ParticleDefinition*  partDef=GET_PARTICLE_DEFINITION( this->particle_pdge);
        G4float   partMass = partDef->GetPDGMass();
        G4float   partEnergy = this->energy + partMass;
        G4float   partMom = std::sqrt( partEnergy*partEnergy - partMass*partMass );
        SET_Z_PLANE( this-> Z_plane, this->apply );
        particle_time =0;
        for ( int k=0; k< SPLITTING_FACTOR; k++){

      particle_position =  G4ThreeVector(this->pos_x,this->pos_y,this->pos_z);
      particle_momentum =  G4ThreeVector(partMom*this->dir_x,partMom*this->dir_y,partMom*this->dir_z);

     G4PrimaryParticle * particle = new G4PrimaryParticle(GET_PARTICLE_DEFINITION( this->particle_pdge),particle_momentum.x() , particle_momentum.y(), particle_momentum.z());

     G4double  new_weight=this->particle_weight/ (double)SPLITTING_FACTOR;
     particle->SetWeight( new_weight);
     // Create the new primary vertex and set the primary to it
     G4PrimaryVertex * vertex = new G4PrimaryVertex(particle_position, particle_time);
     vertex->SetPrimary(particle);
     // And finally set the vertex to this event
     anEvent->AddPrimaryVertex(vertex);
    }// end of for boucle

    }// end for
    ID_OF_NEXT_EVENT=ID_OF_NEXT_EVENT+Number_of_Entries+1;


}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void G4UserH5PhaseSpaceReader:: GENERATE_NEW_PART_ROT_SPLITTING(int ITERATOR,G4Event*& anEvent){



    this->energy           *=MeV;
    this->pos_x            *=mm;
    this->pos_y            *=mm;

    this->dir_x            *=mm;
    this->dir_y            *=mm;
    this->dir_z            *=mm;
    for (INDEX_OF_CURRENT_DATA=0+ITERATOR; INDEX_OF_CURRENT_DATA<Number_of_Entries+ITERATOR;INDEX_OF_CURRENT_DATA++){
         this->particle_pdge   = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_PDGE;
         this->particle_weight = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_WEIGHT;
         this->energy          = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_KINETIC;
         this->pos_x           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_POS_X;
         this->pos_y           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_POS_Y;
         this->pos_z           = this-> Z_STOP;
         this->dir_x           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_X;
         this->dir_y           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_Y;
         this->dir_z           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_Z;

        G4ParticleDefinition*  partDef=GET_PARTICLE_DEFINITION( this->particle_pdge);
        G4float   partMass = partDef->GetPDGMass();
        G4float   partEnergy = this->energy+ partMass;
        G4float   partMom = std::sqrt( partEnergy*partEnergy - partMass*partMass );
       SET_Z_PLANE( this-> Z_plane, this->apply );

          particle_time =0;

        for ( int k=0; k< SPLITTING_FACTOR; k++){

    particle_position =G4ThreeVector(this->pos_x,this->pos_y,this->pos_z);

     G4float angle;

     angle*=deg;

     angle = k*360.00/(double)SPLITTING_FACTOR;

      particle_momentum = G4ThreeVector(partMom*this->dir_x,partMom*this->dir_y,partMom*this->dir_z);

     particle_position.rotateZ(angle);

     particle_momentum.rotateZ(angle);

     G4PrimaryParticle * particle = new G4PrimaryParticle(GET_PARTICLE_DEFINITION( this->particle_pdge),particle_momentum.x() , particle_momentum.y(), particle_momentum.z());

     G4double  new_weight=this->particle_weight/ (double)SPLITTING_FACTOR;
     particle->SetWeight( new_weight);
     // Create the new primary vertex and set the primary to it
     G4PrimaryVertex * vertex = new G4PrimaryVertex(particle_position, particle_time);
     vertex->SetPrimary(particle);
     // And finally set the vertex to this event
     anEvent->AddPrimaryVertex(vertex);
    }// end of for boucle

    }// end for
    ID_OF_NEXT_EVENT=ID_OF_NEXT_EVENT+Number_of_Entries+1;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void G4UserH5PhaseSpaceReader:: GENERATE_NEW_PARTICLE(int ITERATOR,G4Event*& anEvent){



    this->energy           *=MeV;
    this->pos_x            *=mm;
    this->pos_y            *=mm;
    this->dir_x            *=mm;
    this->dir_y            *=mm;
    this->dir_z            *=mm;

for ( INDEX_OF_CURRENT_DATA=0+ITERATOR; INDEX_OF_CURRENT_DATA<Number_of_Entries+ITERATOR;INDEX_OF_CURRENT_DATA++){

     this->particle_pdge   = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_PDGE;
     this->particle_weight = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_WEIGHT;
     this->energy          = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_KINETIC;
     this->pos_x           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_POS_X;
     this->pos_y           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_POS_Y;
     this->pos_z           = this-> Z_STOP;
     this->dir_x           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_X;
     this->dir_y           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_Y;
     this->dir_z           = pDetectorConstruction->RAM_PhspData[INDEX_OF_CURRENT_DATA]. PART_DIR_Z;
    G4ParticleDefinition*  partDef=GET_PARTICLE_DEFINITION( this->particle_pdge);
    G4float   partMass = partDef->GetPDGMass();
    G4float partEnergy = this->energy+ partMass;
//G4cout<<" enery : " << this->energy<<G4endl;
    G4float  partMom = std::sqrt( partEnergy*partEnergy - partMass*partMass );
      particle_time =0;
    SET_Z_PLANE( this-> Z_plane, this->apply );
     particle_position = G4ThreeVector(this->pos_x,this->pos_y,this->pos_z);
    G4PrimaryParticle * particle = new G4PrimaryParticle(GET_PARTICLE_DEFINITION( this->particle_pdge),partMom*this->dir_x,partMom*this->dir_y,
                                                        partMom*this->dir_z);
    particle->SetWeight(this->particle_weight);
    // Create the new primary vertex and set the primary to it
    G4PrimaryVertex * vertex = new G4PrimaryVertex(particle_position, particle_time);
    vertex->SetPrimary(particle);
    // And finally set the vertex to this event
    anEvent->AddPrimaryVertex(vertex);
}// end for

ID_OF_NEXT_EVENT=ID_OF_NEXT_EVENT+Number_of_Entries+1;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
 G4ParticleDefinition*  G4UserH5PhaseSpaceReader::GET_PARTICLE_DEFINITION(int& PDGE)
{
G4String particleName               =     "";

G4ParticleTable* particleTable      =    G4ParticleTable::GetParticleTable();

G4ParticleDefinition* particle_def  =    particleTable->FindParticle(particleName="gamma");

    switch (PDGE)
     {
     case -11:
                   particle_def     =    particleTable->FindParticle(particleName="e+");;
         break;
     case 11:
                   particle_def     =    particleTable->FindParticle(particleName="e-");
         break;
     case 22:
                   particle_def     =    particleTable->FindParticle(particleName="gamma");
         break;
    case 2112:
                   particle_def     =    particleTable->FindParticle(particleName="neutron");
        break;
    case 2212:
                   particle_def     =    particleTable->FindParticle(particleName="proton");
        break;
     }

return particle_def;
}

 /*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void G4UserH5PhaseSpaceReader::SET_PHASE_SPACE_FILE_NAME( G4String _FileName)

 {
 this->FileName=_FileName;

 }
 /*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
 void G4UserH5PhaseSpaceReader::SET_Z_PLANE( G4double _Z_plane,  bool _apply )
 {
     if ( _apply==true){
         this->pos_z           = _Z_plane/mm;
     }
     else {
     }

 }


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void G4UserH5PhaseSpaceReader::SET_EVENT_GENERATION_FLAG(G4int FLAG){

this->EVENT_GENERATION_FLAG= FLAG;

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void G4UserH5PhaseSpaceReader::SET_PARAMETERS(G4String _PHASE_SPACE_NAME, bool _CHANGE_Z_STOP_VALUE, G4float _Z_STOP, int _EVENT_GENERATION_FLAG, int    _SPLITTING_FACTOR)
{
SET_PHASE_SPACE_FILE_NAME(_PHASE_SPACE_NAME);
this->EVENT_GENERATION_FLAG=_EVENT_GENERATION_FLAG;
if (_CHANGE_Z_STOP_VALUE==true)  SET_Z_PLANE( _Z_STOP,  true ) ;
SET_EVENT_GENERATION_FLAG( _EVENT_GENERATION_FLAG);
this-> SPLITTING_FACTOR=_SPLITTING_FACTOR;
}
