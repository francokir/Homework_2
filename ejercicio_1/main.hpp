#pragma once
#include <iostream>
using namespace std ;
class Tiempo {
private:
    int horas;
    int minutos;
    int segundos;
    string parte_dia;
public:
    Tiempo ();
    Tiempo (int horas);
    Tiempo (int horas, int minutos);
    Tiempo (int horas,int minutos, int segundos);
    Tiempo (int horas,int minutos, int segundos, string parte_dia);
    void set_tiempo();
    







};
