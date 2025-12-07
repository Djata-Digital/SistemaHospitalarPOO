#ifndef EMERGENCIA_HPP
#define EMERGENCIA_HPP

#include "Consulta.hpp"

// Emergência
class Emergencia : public Consulta {
public:
    Emergencia(Paciente* p, Medico* m, const string& dh)
        : Consulta(p, m, dh) {}

    double getValor() const override { return 400.0; }
    int getDuracao() const override { return 60; }
    int getPrioridade() const override { return 1; }
    string getTipo() const override { return "Emergência"; }
};

#endif
