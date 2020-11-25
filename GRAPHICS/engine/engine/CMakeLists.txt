# CMakeList.txt : projet CMake pour engine, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("engine")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (engine "engine.cpp" "engine.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
