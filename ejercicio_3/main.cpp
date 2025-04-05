#include <iostream>
#include "main.hpp"
using namespace std;

/*constructor de los enteros*/
entero::entero(int v) {
    valor = v;
}
/*Como utilizo shared ptr, el dynamic cast sirve para convertir un puntero de la clase base numero, a uno de las 
clases derivadas, en este caso entero. La suma como necesita trabajar con enteros y num seria un numero generico
nos aseguramos de trabajar con enteros. La linea de codigo lo que hace es convertir el puntero &num a un
puntero de tipo const entero*, si num era un complejo o real, ptr se convierte en null ptr, si no, se queda con el 
real. Entiendo que dynamic cast lo que hace es verificar en tiempo de ejecucion que la conversion que intento hacer,
sea valida. La explicacion aplica a la resta y la multiplicacion tambien. */
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
/*simplemente utilizo el to_string, puedo hacerlo ya que es un entero*/
string entero::toString() const {
    return to_string(valor);
}

real::real(float v) {
    num = v;
}

/*Misma explicacion que los enteros, uso dynamic cast, para las 3 operaciones*/
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

/*sigo pudiendo utilizar el to_string, es simplemente un numero real*/
string real::toString() const {
    return to_string(num);
}   


/*constructor de un numero complejo, con su parte real e imaginaria*/
complejo::complejo(float r, float i) {
    real = r;
    imaginario = i;
}

/*Utilizo dynamic cast, como en las anteriores, pero sumo la parte real con la parte real y la imaginaria con la 
imaginaria, hago lo mismo para la resta*/
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

/* formula para multiplicar complejos : (a+bi)⋅(c+di)=(ac−bd)+(ad+bc)i
Vuelvo a utilizar dynamic cast y la operacion se basa en la formula de arriba.*/
shared_ptr<numero> complejo::multiplicacion(const numero& num) const {     
    const complejo* ptr = dynamic_cast<const complejo*>(&num);
    if (ptr) {
        float nuevoReal = real * ptr->real - imaginario * ptr->imaginario;
        float nuevoImaginario = real * ptr->imaginario + imaginario * ptr->real;
        return make_shared<complejo>(nuevoReal, nuevoImaginario);
    }
    return nullptr;
}

/*Uso to_string, pero separando por partes la real y la imaginaria, si es positiva esta ultima, concateno el +
, si es negativa, directament se pone con el - y concateno la i*/
string complejo::toString() const {
    string resultado = to_string(real);
    if (imaginario >= 0) {
        resultado += " + ";
    }
    resultado += to_string(imaginario) + "i";
    return resultado;
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

        if (opcion == 1) { 
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