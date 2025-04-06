#include <string>
#include <iostream>
#include "main.hpp"
using namespace std;

/*Constructor de la cuenta, le paso balance y nombre del titular de la cuenta*/
Cuenta::Cuenta(double balance, const string& titularCuenta)
    : balance(balance), titularCuenta(titularCuenta) {}

/*se le deposita una cantidad  de dinero (positiva) y se lo sumo al balance*/
void Cuenta::depositar(double cantidad) {
    if (cantidad > 0) {
        balance += cantidad;
    }
}

double Cuenta::getBalance() const {
    return balance;
}

/*Constructor de la caja de ahorro, se llama directamente al constructor de la clase base cuenta*/
CajaDeAhorro::CajaDeAhorro(double balance, const string& titularCuenta)
    : Cuenta(balance, titularCuenta), cantmostrarInfo(0) {}

/*para retirar dinero de la caja de ahorro se tiene que retirar una cantidad positiva, y a lo sumo todo lo que hay 
(<= balance)*/

bool CajaDeAhorro::retirar(double cantidad) {
    if (cantidad > 0 && cantidad <= balance) {
        balance -= cantidad;
        return true;
    }
    return false;
}

/*para mostrar la info, le sumo 1 al contador de veces q se mostraron, imprimo por pantalla los datos necesarios,
y a la tercera vez que se muestra la info, ya se descuenta 20 del balance.*/
void CajaDeAhorro::mostrarInfo() {
    cantmostrarInfo++;
    cout << "Tipo de cuenta: Caja de Ahorro\n";
    cout << "Titular: " << titularCuenta << "\n";
    cout << "Balance: $" << balance << "\n";
    if (cantmostrarInfo > 2) {
        balance -= 20;
    }
}

/*constructor de la clase cuenta corrienten nuevamente llamando al constructor de la clase base clase*/
CuentaCorriente::CuentaCorriente(double balance, const string& titularCuenta)
    : Cuenta(balance, titularCuenta) {}

/*misma funcion que para la caja de ahorro, me fijo que el balance no quede negativo. Aclaracion: aca tuve dudas
en si permitir que el balance se pueda ir negativo porque es lo que mas sentido tenia en mi opinion, pero en ese caso
la utima funcion de usar caja de ahorro como respaldo, no tendria sentido, ya que siempre se podria retirar dinero
de la cuenta corriente, a menos que haya un limite para cuan negativo se puede ir la cuenta, pero no sabria que numero
poner*/
bool CuentaCorriente::retirar(double cantidad) {
    if (cantidad > 0 && cantidad <= balance) {
        balance -= cantidad;
        return true;
    }
    return false;
}

/*Imprimo por pantalla la info de la cuenta*/
void CuentaCorriente::mostrarInfo() {
    cout << "Tipo de cuenta: Cuenta Corriente\n";
    cout << "Titular: " << titularCuenta << "\n";
    cout << "Balance: $" << balance << "\n";
}

/*Esto es lo ultimo que pedia la consigna, lo que hago es, intentar retirar la cantidad de dinero de la cuenta 
corriente y si falla (no hay cantidad de dinero necesaria) saco de la caja de ahorro si es que hay*/
void usarCajaAhorroComoRespaldo(CuentaCorriente& cuentaCorriente, CajaDeAhorro& cajaAhorro, double cantidad) {
    if (!cuentaCorriente.retirar(cantidad)) {
        if (!cajaAhorro.retirar(cantidad)) {
            cout << "La cuenta no posee dinero suficiente.\n";
        }
    }
}

int main() {
    double monto;
    int opcion = -1;

    double saldoCaja, saldoCorriente;
    string titularCaja, titularCorriente;

    cout << "Ingrese saldo inicial de la Caja de Ahorro: ";
    cin >> saldoCaja;
    cin.ignore();

    cout << "Ingrese titular de la Caja de Ahorro: ";
    getline(cin, titularCaja);

    cout << "Ingrese saldo inicial de la Cuenta Corriente: ";
    cin >> saldoCorriente;
    cin.ignore();

    cout << "Ingrese titular de la Cuenta Corriente: ";
    getline(cin, titularCorriente);

    CajaDeAhorro caja(saldoCaja, titularCaja);
    CuentaCorriente corriente(saldoCorriente, titularCorriente);

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Mostrar info Caja de Ahorro\n";
        cout << "2. Mostrar info Cuenta Corriente\n";
        cout << "3. Retirar de Caja de Ahorro\n";
        cout << "4. Retirar de Cuenta Corriente\n";
        cout << "5. Usar Caja como respaldo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        switch(opcion) {
            case 1:
                caja.mostrarInfo();
                break;

            case 2:
                corriente.mostrarInfo();
                break;

            case 3:
                cout << "Monto a retirar: ";
                cin >> monto;
                if (caja.retirar(monto)) {
                    cout << "Se pudo retirar el dinero de la Caja de Ahorro.\n";
                } else {
                    cout << "No se pudo retirar dinero de la Caja de Ahorro.\n";
                }
                break;

            case 4:
                cout << "Monto a retirar: ";
                cin >> monto;
                if (corriente.retirar(monto)) {
                    cout << "Se pudo retirar el dinero de la Cuenta Corriente.\n";
                } else {
                    cout << "No se pudo retirar dinero de la Cuenta Corriente.\n";
                }
                break;

            case 5: {
                cout << "Monto a retirar: ";
                cin >> monto;

                double balanceInicialCorriente = corriente.getBalance();
                double balanceInicialCaja = caja.getBalance();

                usarCajaAhorroComoRespaldo(corriente, caja, monto);

                double balanceFinalCorriente = corriente.getBalance();
                double balanceFinalCaja = caja.getBalance();

                if (balanceFinalCorriente != balanceInicialCorriente) {
                    cout << "Retiro exitoso desde la Cuenta Corriente.\n";
                } else if (balanceFinalCaja != balanceInicialCaja) {
                    cout << "Retiro exitoso desde la Caja de Ahorro como respaldo.\n";
                } else {
                    cout << "No se pudo realizar el retiro.\n";
                }
                break;
            }

            case 0:
                cout << "Saliendo del programa.\n";
                return 0;

            default:
                cout << "Opcion invalida.\n";
        }
    }
}