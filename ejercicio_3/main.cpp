#include <iostream>
#include <sstream>
#include "main.hpp"
using namespace std;

entero::entero(int v) {
    valor = v;
}

shared_ptr<numero> entero::suma(const numero& num) const {
    const entero* ptr = dynamic_cast<const entero*>(&num);
    if (ptr) {
        return make_shared<entero>(valor + ptr->valor);
    }
    return nullptr;
}

shared_ptr<numero> entero::resta(const numero& num) const {
    const entero* ptr = dynamic_cast<const entero*>(&num);
    if (ptr) {
        return make_shared<entero>(valor - ptr->valor);
    }
    return nullptr;
}

shared_ptr<numero> entero::multiplicacion(const numero& num) const {
    const entero* ptr = dynamic_cast<const entero*>(&num);
    if (ptr) {
        return make_shared<entero>(valor * ptr->valor);
    }
    return nullptr;
}

string entero::toString() const {
    return to_string(valor);
}

real::real(float v) {
    num = v;
}

shared_ptr<numero> real::suma(const numero& num) const {
    const real* ptr = dynamic_cast<const real*>(&num);
    if (ptr) {
        return make_shared<real>(this->num + ptr->num);
    }
    return nullptr;
}

shared_ptr<numero> real::resta(const numero& num) const {
    const real* ptr = dynamic_cast<const real*>(&num);
    if (ptr) {
        return make_shared<real>(this->num - ptr->num);
    }
    return nullptr;
}

shared_ptr<numero> real::multiplicacion(const numero& num) const {
    const real* ptr = dynamic_cast<const real*>(&num);
    if (ptr) {
        return make_shared<real>(this->num * ptr->num);
    }
    return nullptr;
}

string real::toString() const {
    return to_string(num);
}   


complejo::complejo(float r, float i) {
    real = r;
    imaginario = i;
}

shared_ptr<numero> complejo::suma(const numero& num) const {
    const complejo* ptr = dynamic_cast<const complejo*>(&num);
    if (ptr) {
        return make_shared<complejo>(real + ptr->real, imaginario + ptr->imaginario);
    }
    return nullptr;
}

shared_ptr<numero> complejo::resta(const numero& num) const {
    const complejo* ptr = dynamic_cast<const complejo*>(&num);
    if (ptr) {
        return make_shared<complejo>(real - ptr->real, imaginario - ptr->imaginario);
    }
    return nullptr;
}

/* formula para multiplicar complejos : (a+bi)⋅(c+di)=(ac−bd)+(ad+bc)i*/
shared_ptr<numero> complejo::multiplicacion(const numero& num) const {     
    const complejo* ptr = dynamic_cast<const complejo*>(&num);
    if (ptr) {
        float nuevoReal = real * ptr->real - imaginario * ptr->imaginario;
        float nuevoImaginario = real * ptr->imaginario + imaginario * ptr->real;
        return make_shared<complejo>(nuevoReal, nuevoImaginario);
    }
    return nullptr;
}

string complejo::toString() const {
    ostringstream os;
    os << real;

    if (imaginario >= 0) {
        os << "+"; 
    }
   
    os << imaginario << "i"; 
    return os.str();
}

int main() {
    int opcion;

    while (true){
        cout << "Seleccione el tipo de numero:" << endl;
        cout << "1. Entero" << endl;
        cout << "2. Real" << endl;
        cout << "3. Complejo" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 4) break;

        if (opcion == 1) { // Entero
            int v1, v2;
            cout << "Ingrese un numero entero: ";
            cin >> v1;
            cout << "Ingrese otro numero entero: ";
            cin >> v2;

            auto n1 = make_shared<entero>(v1);
            auto n2 = make_shared<entero>(v2);

            auto sumaEnteros = n1->suma(*n2);
            auto restaEnteros = n1->resta(*n2);
            auto multiplicacionEnteros = n1->multiplicacion(*n2);

            cout << "La suma de sus dos enteros da: " << sumaEnteros->toString() << endl;
            cout << "La resta de sus dos enteros da: " << restaEnteros->toString() << endl;
            cout << "La multiplicacion de sus dos enteros da: " << multiplicacionEnteros->toString() << endl;

        } else if (opcion == 2) {
            float r1, r2;
            cout << "Ingrese un numero real: ";
            cin >> r1;
            cout << "Ingrese otro numero real: ";
            cin >> r2;

            auto real1 = make_shared<real>(r1);
            auto real2 = make_shared<real>(r2);

            auto sumaReales = real1->suma(*real2);
            auto restaReales = real1->resta(*real2);
            auto multiplicacionReales = real1->multiplicacion(*real2);

            cout << "La suma de sus dos numeros reales da: " << sumaReales->toString() << endl;
            cout << "La resta de sus dos numeros reales da: " << restaReales->toString() << endl;
            cout << "La multiplicacion de sus dos numeros reales da: " << multiplicacionReales->toString() << endl;

        } else if (opcion == 3) {
            float real1, imag1, real2, imag2;
            cout << "Ingrese la parte real del primer numero complejo: ";
            cin >> real1;
            cout << "Ingrese la parte imaginaria del primer numero complejo: ";
            cin >> imag1;
            cout << "Ingrese la parte real del segundo numero complejo: ";
            cin >> real2;
            cout << "Ingrese la parte imaginaria del segundo numero complejo: ";
            cin >> imag2;

            auto c1 = make_shared<complejo>(real1, imag1);
            auto c2 = make_shared<complejo>(real2, imag2);

            auto sumaComplejos = c1->suma(*c2);
            auto restaComplejos = c1->resta(*c2);
            auto multiplicacionComplejos = c1->multiplicacion(*c2);

            cout << "La suma de sus dos numeros imaginarios da: " << sumaComplejos->toString() << endl;
            cout << "La resta de sus dos numeros imaginarios da: " << restaComplejos->toString() << endl;
            cout << "La multiplicacion de sus dos numeros imaginarios da: " << multiplicacionComplejos->toString() << endl;

        } 

    }

    return 0;
}