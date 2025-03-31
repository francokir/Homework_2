#pragma once
#include <iostream>
#include <vector>
using namespace std;

class estudiante
{
private:
    string nombre_completo;
    int legajo;
    vector <pair<string,float>> cursos;

public:
    estudiante(string nombre, int legajo);

    string getNombreCompleto() const;
    int getLegajo() const;
    float getPromedioGeneral() const;


    void agregarCurso(const string& nombreCurso, float nota);
};

class curso {
private:
    vector<estudiante*> estudiantes;
    static const int capacidad_maxima = 20; 

public:
    bool inscribirEstudiante(estudiante* est);

    bool desinscribirEstudiante(int legajo);

    bool estaInscripto(int legajo);

    bool estaCompleto();
    
    void imprimirLista();

    curso* copiarCurso();
};