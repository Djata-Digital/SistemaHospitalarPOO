#ifndef CONSULTA_NORMAL_HPP
#define CONSULTA_NORMAL_HPP

#include "Consulta.hpp"

// Consulta normal
class ConsultaNormal : public Consulta {
public:
    ConsultaNormal(Paciente* p, Medico* m, const string& dh)
        : Consulta(p, m, dh) {}

    double getValor() const override { return 200.0; }
    int getDuracao() const override { return 30; }
    int getPrioridade() const override { return 2; }
    string getTipo() const override { return "Consulta"; }
};

#endif
