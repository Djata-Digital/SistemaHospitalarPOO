#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>
#include <iostream>

using namespace std;

// Registro de atendimento em um prontuário
class Registro {
private:
    string data;
    string medico;
    string especializacao;
    string descricao;
    string prescricao;

public:
    Registro(const string& data,
             const string& medico,
             const string& esp,
             const string& descr,
             const string& presc = "")
        : data(data), medico(medico), especializacao(esp),
          descricao(descr), prescricao(presc) {}

    void imprimir() const {
        cout << "Data: " << data
             << " | Médico: " << medico
             << " (" << especializacao << ")"
             << " | Descrição: " << descricao;
        if (!prescricao.empty())
            cout << " | Prescrição: " << prescricao;
        cout << endl;
    }
};

#endif
