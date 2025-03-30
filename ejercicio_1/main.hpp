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
    
    int getHoras() const;
    int getMinutos() const;
    int getSegundos() const;
    string getParteDia() const;
    string getTiempoCompleto() const;

    void setHoras(int h);
    void setMinutos(int m);
    void setSegundos(int s);
    void setParteDia(const string& pd);
    void tiempo24hs() const;
    

    







};
