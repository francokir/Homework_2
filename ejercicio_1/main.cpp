#include <iostream>
#include "main.hpp"
Tiempo::Tiempo(){
    horas = 0;
    minutos = 0;
    segundos = 0;
    parte_dia = "a.m.";
}

Tiempo::Tiempo(int h){
    if (h < 1 || h > 12) {
        cout << "Hora fuera del rango" << endl;
        h = 0;
    }
    horas = h;
    minutos = 0;
    segundos = 0;
    parte_dia = "a.m.";
}

Tiempo::Tiempo(int h, int m){
    if (h < 1 || h > 12) {
        cout << "Hora fuera del rango" << endl;
        h = 0;
    }
    if (m < 0 || m > 59) {
        cout << "minutos fuera del rango" << endl;
        m = 0;
    }
    horas = h;
    minutos = m;
    segundos = 0;
    parte_dia = "a.m.";
}

Tiempo::Tiempo(int h, int m, int s){
    if (h < 1 || h > 12) {
        cout << "Hora fuera del rango" << endl;
        h = 0;
    }
    if (m < 0 || m > 59) {
        cout << "minutos fuera del rango" << endl;
        m = 0;
    }
    if (s < 0 || s > 59) {
        cout << "segundos fuera del rango" << endl;
        s = 0;
    }
    horas = h;
    minutos = m;
    segundos = s;
    parte_dia = "a.m.";
}

Tiempo::Tiempo(int h, int m, int s, string pd){
    if (h < 1 || h > 12) {
        cout << "Hora fuera del rango" << endl;
        h = 0;
    }
    if (m < 0 || m > 59) {
        cout << "minutos fuera del rango" << endl;
        m = 0;
    }
    if (s < 0 || s > 59) {
        cout << "segundos fuera del rango" << endl;
        s = 0;
    }   
    if( pd != "a.m." && pd != "p.m."){
        cout << "El formato correspondiente a la parte del dia debe ser a.m. o p.m." << endl;
        pd = "a.m.";
    }
    horas = h;
    minutos = m;
    segundos = s;
    parte_dia = pd;
}

