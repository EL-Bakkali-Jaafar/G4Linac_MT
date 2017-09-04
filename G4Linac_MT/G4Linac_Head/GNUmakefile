# GNUmakefile for using HDF5 phase-space I/O.  Jaafar EL Bakkali, 13/02/2015
name :=G4Linac_Head
G4TARGET := $(name)
G4EXLIB := true
EXTRALIBS  +=  -L/opt/hdf5/lib -lhdf5_cpp 

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk




