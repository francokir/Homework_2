#include <iostream>
#include <vector>
#include "main.hpp"
using namespace std;

string estudiante::getNombreCompleto()const {
    return nombre_completo;
}

int estudiante::getLegajo() const {
    return legajo;
}

float estudiante::getPromedioGeneral() const {
    float suma = 0.0;
        for (const auto& par : cursos) {
            suma += par.second;
        }
        return suma / cursos.size();
}

void estudiante::agregarCurso(const string& nombreCurso, float nota) {
    cursos.push_back({nombreCurso, nota}); 
}