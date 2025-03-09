#PARTIE A MODIFIER : Liste des fichiers .cpp (et uniquement les .cpp) à compiler

SOURCES=code_test.cpp FLRW_model.cpp FLRW_statistics.cpp interpolation2D.cpp matrice_covariance.cpp outils.cpp
#FIN DE LA PARTIE A MODIFIER

# Nom du compilateur
CXX=g++

CXXFLAGS=-O2 -march=native -std=c++17 -fopenmp # Optimisation et standard C++

LDFLAGS=-Wall -Wextra
# Arguments pour l'etape de compilation : tous les avertissements (et même plus) sauf "ignored-attributes" (présence d'un bug dans GCC version 6 et plus)
CPPFLAGS=-Wall -Wextra -I/usr/include/eigen3
# Librairies : none
LDLIBS=-lgsl -lgslcblas -lm -fopenmp #ajout de gsl et OpenMP

# Liste des fichier objet (*.o), générée automagiquement
OBJETS=$(subst .cpp,.o,$(SOURCES))

all: build

build: $(OBJETS)
	$(CXX) $(LDFLAGS) -o run $(OBJETS) $(LDLIBS) 

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	rm $(OBJETS)
	rm -f *~ .depend

-include .depend # le "-" ignore l'erreur si le fichier n'existe pas.