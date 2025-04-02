#include <iostream>
#include <vector>
#include <algorithm>
#include "main.hpp"
using namespace std;

estudiante::estudiante(string nombre, int legajo) {
    nombre_completo = nombre;
    this->legajo = legajo;
}

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

void estudiante::agregarCurso(const string& nombrecurso, float nota) {
    cursos.push_back({nombrecurso, nota}); 
}

bool estudiante::operator<(const estudiante& otro) const {
    return nombre_completo < otro.nombre_completo;
}

ostream& operator<<(ostream& os, const estudiante& est) {
    os << "Nombre: " << est.nombre_completo << ", Legajo: " << est.legajo;
    return os;
}

curso::curso(const string& nombre) {
    nombrecurso = nombre;
}

bool curso::inscribirEstudiante(shared_ptr<estudiante> est){
    if (estudiantes.size() < capacidad_maxima){
        estudiantes.push_back(est);
        return true;
        }
    else {
        return false;
    }
}

bool curso::estaInscripto(int legajo){
    for (const auto &est : estudiantes) {
        if (est->getLegajo() == legajo) {
            return true;
        }
    }
    return false;
}

bool curso::estaCompleto(){
    return (curso::capacidad_maxima == estudiantes.size());
}

bool curso::desinscribirEstudiante(int legajo){
    for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
        if ((*it)->getLegajo() == legajo) {
            estudiantes.erase(it);
            return true;
        }
    }
    return false;
}


void curso::imprimirLista() const {
    vector<shared_ptr<estudiante>> estudiantesOrdenados = estudiantes;
    sort(estudiantesOrdenados.begin(), estudiantesOrdenados.end(), [](shared_ptr<estudiante> a, shared_ptr<estudiante> b) {
                  return *a < *b;
        });
    cout << "Estudiantes en orden alfabetico:\n";
    for (const auto& est : estudiantesOrdenados) {
        cout << *est << endl;
    }
}

/*Para la copia implemente un shallow copy, copio el vector de punteros estudiantes pero no duplico los objetos
apuntados. Esto significa que ambos cursos apuntan a los mismos estudiantes. Crei conveniente esta eleccion
ya que es eficiente en memoria y permite que los cambios en un estudiante se vean en todos los cursos que lo incluyen*/

curso::curso(const curso& otro)
    : nombrecurso(otro.nombrecurso), estudiantes(otro.estudiantes) {
}

/* Decidi implementar un shallow copy, como mi clase curso almacena shared ptr hacia objetos estudiantes, al copiar
el curso, se copian los punteros pero no se duplican los estudiantes, esto hace que se puedan compartir estudiantes 
entre varios curos y esto es eficiente en memoria. Al usar shared ptr, no me preocupo por la memoria, no la tengo que gestionar
y por ejemplo cuando el ultimo curso que apunta a un estudiante se destruye, el estudiante tambien se destruye.
*/

curso* curso::copiarCurso() const {
    return new curso(*this);
}

/* c. ¿Qué tipo de relación existe entre los objetos curso y estudiante?
    La relación entre curso y estudiante es de Agregación en mi implementacion.
    Mi clase curso lo que almacena son objetos estudiante, con punteros *. Es un vector , el curso tiene acceso
    a los estudiantes pero no es propietario. Existe uno independientemente del otro, la destruccion de un curso
    no implica la destruccion de los objetos estudiante almacenados, pueden ser compartidos por otros cursos.
    Ademas, como dije recien algunos cursos comparten la mayor parte de los estudiantes, los punteros hacen posible
    esto ya que un mismo estudiante puede ser referenciado por multiples cursos, sin duplicar datos.
*/

int main() {
    curso miCurso("Paradigmas de Programación");

    while (true) {
        cout << "\n--- Menu Principal ---\n";
        cout << "1. Inscribir un estudiante\n";
        cout << "2. Desinscribir un estudiante\n";
        cout << "3. Verificar si un estudiante está inscripto\n";
        cout << "4. Imprimir lista de estudiantes (orden alfabético)\n";
        cout << "5. Copiar curso\n";
        cout << "6. Salir\n";
        cout << "Ingrese una opción: ";

        int opcion;
        cin >> opcion;

        if (opcion == 6) break;

        switch (opcion) {
            case 1: {
                string nombre;
                int legajo;
                cout << "Ingresar nombre completo del estudiante: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingresar legajo del estudiante: ";
                cin >> legajo;

                auto nuevoEstudiante = make_shared<estudiante>(nombre, legajo);

                if (miCurso.inscribirEstudiante(nuevoEstudiante)) {
                    cout << "Estudiante inscripto.\n";
                } else {
                    cout << "El curso ya esta lleno.\n";
                }
                break;
            }

            case 2: {
                int legajo;
                cout << "Ingresar el legajo del estudiante que quiere desinscribir: ";
                cin >> legajo;

                if (miCurso.desinscribirEstudiante(legajo)) {
                    cout << "El estudiante fue desinscripto.\n";
                } else {
                    cout << "No existe un estudiante con ese legajo.\n";
                }
                break;
            }

            case 3: {
                int legajo;
                cout << "Ingresar el legajo del estudiante: ";
                cin >> legajo;

                if (miCurso.estaInscripto(legajo)) {
                    cout << "El estudiante está inscripto.\n";
                } else {
                    cout << "El estudiante no está inscripto.\n";
                }
                break;
            }

            case 4: {
                miCurso.imprimirLista();
                break;
            }

            case 5: {
                auto copia = miCurso.copiarCurso();
                cout << "Curso copiado.\n";
                delete copia; /*libero la memoria que se asigna en la copia*/
                break;
            }
        }
    }

    cout << "Saliste del menu.\n";
    return 0;
}
