#pragma once
#include <iostream>
#include <memory>
using namespace std;

class numero {
    public:
        virtual shared_ptr<numero> suma (const numero& num) const = 0;
        virtual shared_ptr<numero> resta (const numero& num) const = 0;
        virtual shared_ptr<numero> multiplicacion (const numero& num) const = 0;
        virtual string toString() const = 0;
        virtual ~numero() = default;
};


class entero: public numero {
    private:
    int valor;
    public:
        entero(int v);

        shared_ptr<numero> suma(const numero& num) const override;
        shared_ptr<numero> resta(const numero& num) const override;
        shared_ptr<numero> multiplicacion(const numero& num) const override;
        string toString() const override;
};


class real: public numero {
    private:
        float num;
    public:
        real(float v);

        shared_ptr<numero> suma(const numero& num) const override;
        shared_ptr<numero> resta(const numero& num) const override;
        shared_ptr<numero> multiplicacion(const numero& num) const override;
        string toString() const override;
};


class complejo: public numero {
    private:
        float real;
        float imaginario;
    public:
        complejo(float real, float imaginario);
        
        shared_ptr<numero> suma(const numero& num) const override;
        shared_ptr<numero> resta(const numero& num) const override;
        shared_ptr<numero> multiplicacion(const numero& num) const override;
        string toString() const override;
};