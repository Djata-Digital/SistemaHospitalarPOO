#ifndef ACOMPANHAMENTO_HPP
#define ACOMPANHAMENTO_HPP

#include "Consulta.hpp"

// Acompanhamento (Retorno)
class Acompanhamento : public Consulta {
public:
    Acompanhamento(Paciente* p, Medico* m, const string& dh)
        : Consulta(p, m, dh) {}

    double getValor() const override { return 100.0; }
    int getDuracao() const override { return 20; }
    int getPrioridade() const override { return 3; }
    string getTipo() const override { return "Acompanhamento"; }
};

#endif
