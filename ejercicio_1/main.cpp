#include <iostream>
#include "main.hpp"
#include <iomanip>

/*constructor default, no se le pasa nada*/
Tiempo::Tiempo(){
    horas = 0;
    minutos = 0;
    segundos = 0;
    parte_dia = "a.m.";
}

/*constructor pasandole las horas, los otros valores son predeterminados, se chequea que la hora tenga sentido*/
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

/*constructor pasandole horas y minutos, con chequeo, otros valores predeterminados*/
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

/*constructor pasandole horas, minutos y segundos, la parte del dia queda como a.m.*/
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

/*constructor pasandole todos los parametros*/
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

/*metodo que devuelve las hs*/
int Tiempo::getHoras() const {
    return horas;
}

/*metodo que devuelve los minutos*/
int Tiempo::getMinutos() const {
    return minutos;
}

/*metodo que devuelve los segundos*/
int Tiempo::getSegundos() const {
    return segundos;
}

/*metodo que devuelve la parte del dia*/
string Tiempo::getParteDia() const {
    return parte_dia;
}

/*metodo que devuelve el tiempo completo, se usa la libreria recomendada , por lo entendido, el setw da a entender la cantidad de caracteres que ocupara lo que se imprime
, el setfill, si lo que se imprime no ocupa los caracteres necesarios , lo rellena con 0s en este caso, tiene sentido, si quiero poner que son las 3 y 7, completaria 03:07*/
string Tiempo::getTiempoCompleto() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << horas << "h, "
        << setw(2) << setfill('0') << minutos << "m, "
        << setw(2) << setfill('0') << segundos << "s "
        << parte_dia;
    return oss.str();
}

/*metodo para determinar las horas*/
void Tiempo::setHoras(int h) {
    if (h >= 1 && h <= 12) {
        horas = h;
    } else {
        cerr << "Hora fuera del rango." << endl;
    }
}

/*metodo para determinar los minutos*/
void Tiempo::setMinutos(int m) {
    if (m >= 0 && m <= 59) {
        minutos = m;
    } else {
        cerr << "Minutos fuera del rango." << endl;
    }
}

/*metodo para determinar los segundos*/
void Tiempo::setSegundos(int s) {
    if (s >= 0 && s <= 59) {
        segundos = s;
    } else {
        cerr << "Segundos fuera del rango." << endl;
    }
}

/*metodo para determinar la parte del dia*/
void Tiempo::setParteDia(const string& pd) {
    if (pd == "a.m." || pd == "p.m.") {
        parte_dia = pd;
    } else {
        cerr << "Error, poner parte del dia 'a.m.' o 'p.m.'." << endl;
    }
}

/*para imprimir la hora en formato 24hs, primero determino que hora poner dependiendo de la parte del dia, si es pm se le suman 12, y luego imprimo con la misma logica
que utilice para el get tiempo completo, rellenando con el setfill.*/
void Tiempo::tiempo24hs() const {
    int horas24 = horas; 
    
    if (parte_dia == "a.m.") {
        if (horas == 12){
            horas24 = 0;
        }
    }
    else if (parte_dia == "p.m.") {
        if (horas != 12) { 
            horas24 += 12;
        }
    }
    cout << setw(2) << setfill('0') << horas24 << ":"
         << setw(2) << setfill('0') << minutos << ":"
         << setw(2) << setfill('0') << segundos << endl;
}

int main() {
    Tiempo t;

    int opcion;
    while (opcion != 8) {
        cout << "Opciones:" << endl;
        cout << "1. Crear el objeto Tiempo" << endl;
        cout << "2. Modificar la hora" << endl;
        cout << "3. Modificar los minutos" << endl;
        cout << "4. Modificar los segundos" << endl;
        cout << "5. Modificar parte del dia (a.m./p.m.)" << endl;
        cout << "6. Obtener hora completa" << endl;
        cout << "7. Mostrar la hora en formato 24 horas" << endl;
        cout << "8. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int h, m, s;
                string pd;

                cout << "Ingrese la hora: ";
                cin >> h;
                while (h < 1 || h > 12) {
                    cout << "Hora fuera del rango. Ingrese de 1 a 12: ";
                    cin >> h;
                }
                
                cout << "Ingrese los minutos: ";
                cin >> m;
                while (m < 0 || m >= 60) {
                    cout << "Minutos fuera del rango. Ingrese de 0 a 59: ";
                    cin >> m;
                }

                cout << "Ingrese los segundos: ";
                cin >> s;
                while (s < 0 || s >= 60) {
                    cout << "Segundos fuera del rango. Ingrese de 0 a 59: ";
                    cin >> s;
                }

                cout << "Ingrese parte del dia (a.m. o p.m.): ";
                cin >> pd;
                while (pd != "a.m." && pd != "p.m.") {
                    cout << "Ingrese la parte del dia con la forma correspondiente (a.m. o p.m.): ";
                    cin >> pd;
                }

                t = Tiempo(h, m, s, pd);
                break;
            }
            case 2: {
                int h;
                cout << "Ingrese la nueva hora: ";
                cin >> h;
                t.setHoras(h);
                break;
            }
            case 3: {
                int m;
                cout << "Ingrese los nuevos minutos: ";
                cin >> m;
                t.setMinutos(m);
                break;
            }
            case 4: {
                int s;
                cout << "Ingrese los nuevos segundos: ";
                cin >> s;
                t.setSegundos(s);
                break;
            }
            case 5: {
                string pd;
                cout << "Ingrese parte del dia (a.m. o p.m.): ";
                cin >> pd;
                t.setParteDia(pd);
                break;
            }
            case 6: {
                cout << "La hora completa es: " << t.getTiempoCompleto() << endl;
                break;
            }
            case 7: {
                cout << "La hora en formato 24 horas: ";
                t.tiempo24hs();
                break;
            }
            case 8:
                cout << "Termino el programa." << endl;
                break;
        }

    } 

    return 0;
}