#include <string>
#include <iostream>
#include "main.hpp"
using namespace std;

Cuenta::Cuenta(double balance, const string& titularCuenta)
    : balance(balance), titularCuenta(titularCuenta) {}

void Cuenta::depositar(double cantidad) {
    if (cantidad > 0) {
        balance += cantidad;
    }
}

double Cuenta::getBalance() const {
    return balance;
}

CajaDeAhorro::CajaDeAhorro(double balance, const string& titularCuenta)
    : Cuenta(balance, titularCuenta), cantmostrarInfo(0) {}

bool CajaDeAhorro::retirar(double cantidad) {
    if (cantidad > 0 && cantidad <= balance) {
        balance -= cantidad;
        return true;
    }
    return false;
}

void CajaDeAhorro::mostrarInfo() {
    cantmostrarInfo++;
    cout << "Tipo de cuenta: Caja de Ahorro\n";
    cout << "Titular: " << titularCuenta << "\n";
    cout << "Balance: $" << balance << "\n";
    if (cantmostrarInfo > 2) {
        balance -= 20;
    }
}

CuentaCorriente::CuentaCorriente(double balance, const string& titularCuenta)
    : Cuenta(balance, titularCuenta) {}

bool CuentaCorriente::retirar(double cantidad) {
    if (cantidad > 0) {
        balance -= cantidad;
        return true;
    }
    return false;
}

void CuentaCorriente::mostrarInfo() {
    cout << "Tipo de cuenta: Cuenta Corriente\n";
    cout << "Titular: " << titularCuenta << "\n";
    cout << "Balance: $" << balance << "\n";
}

void usarCajaAhorroComoRespaldo(CuentaCorriente& cuentaCorriente, CajaDeAhorro& cajaAhorro, double cantidad) {
    if (!cuentaCorriente.retirar(cantidad)) {
        if (!cajaAhorro.retirar(cantidad)) {
            cout << "La cuenta no posee dinero suficiente.\n";
        }
    }
}

int main() {
    CajaDeAhorro caja(1000, "Franco Kirchheimer");
    CuentaCorriente corriente(500, "Franco Barravecchia");

    caja.mostrarInfo();
    caja.mostrarInfo();
    caja.mostrarInfo();
    caja.mostrarInfo();
    
    corriente.mostrarInfo();
    corriente.retirar(600);
    corriente.mostrarInfo();

    usarCajaAhorroComoRespaldo(corriente, caja, 200);

    return 0;
}


