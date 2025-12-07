#ifndef PRONTUARIO_MEDICO_HPP
#define PRONTUARIO_MEDICO_HPP

#include <vector>
#include "Registro.hpp"

class ProntuarioMedico {
private:
    vector<Registro> registros;

public:
    void adicionarRegistro(const Registro& r) {
        registros.push_back(r);
    }

    bool vazio() const { return registros.empty(); }

    void imprimir() const {
        if (registros.empty()) {
            cout << "Nenhum registro encontrado." << endl;
            return;
        }
        for (const auto& r : registros)
            r.imprimir();
    }
};

#endif
