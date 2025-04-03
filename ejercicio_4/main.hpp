#pragma once

#include <string>
#include <iostream>
using namespace std;

class CajaDeAhorro;

/*la clase cuenta tiene su parte protected asi  las clases derivadas pueden acceder aqui, pero no se puede acceder 
desde afuera, luego en el public estan todos los metodos que tienen que ser llamados desde afuera,
 hay dos metodos virtuales como se pide y tambien un destructor virtual para evitar
por las dudas problemas de memoria.*/

class Cuenta {
protected:
    double balance;
    string titularCuenta;

public:
    Cuenta(double balance, const string& titularCuenta);
    virtual ~Cuenta() = default;

    void depositar(double cantidad);
    virtual bool retirar(double cantidad) = 0;
    virtual void mostrarInfo() = 0;

    double getBalance() const;
};

/*El contador de las veces que se mostro la info es private porque no es necesario que se acceda desde afuera
luego si, los metodos necesarios en public.*/

class CajaDeAhorro : public Cuenta {
private:
    int cantmostrarInfo;

public:
    CajaDeAhorro(double balance, const string& titularCuenta);
    bool retirar(double cantidad) override;
    void mostrarInfo() override;
};

/*en cuenta corriente, public para todos los metodos que necesito para acceder desde afuera, y uso friend como 
solicita la consigna, para permitir un acceso especial a los atributos de cuenta corriente*/

class CuentaCorriente : public Cuenta {
public:
    CuentaCorriente(double balance, const string& titularCuenta);
    bool retirar(double cantidad) override;
    void mostrarInfo() override;

    friend void usarCajaAhorroRespaldo(CuentaCorriente& cuentaCorriente, CajaDeAhorro& cajaAhorro, double cantidad);
};


