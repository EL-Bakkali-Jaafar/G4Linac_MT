

name :=G4Linac_DoseCal
G4TARGET := $(name)
G4EXLIB := true
EXTRALIBS  +=  -L/opt/hdf5/lib -lhdf5_cpp -lhdf5
ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk




