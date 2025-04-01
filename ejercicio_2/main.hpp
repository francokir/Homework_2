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

    bool operator<(const estudiante& otro) const;

    friend ostream& operator<<(ostream& os, const estudiante& est);
};

class curso {
private:
    vector<estudiante*> estudiantes;
    static const int capacidad_maxima = 20; 
    string nombrecurso;
public:

    curso(const string& nombre);

    curso(const curso& otro);

    curso& operator=(const curso& otro);
    
    bool inscribirEstudiante(estudiante* est);
    bool desinscribirEstudiante(int legajo);
    bool estaInscripto(int legajo);
    bool estaCompleto();
    void imprimirLista() const;

    curso* copiarCurso() const;
};