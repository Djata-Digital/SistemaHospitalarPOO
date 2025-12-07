#ifndef MEDICO_HPP
#define MEDICO_HPP

#include "Pessoa.hpp"

// Médico herda de Pessoa
class Medico : public Pessoa {
private:
    string especializacao;
    string crm;

public:
    static int proximoId; // definido em Modelos.cpp

    Medico(const string& nome, const string& espec,
           const string& crm, const string& endereco,
           const string& contato)
        : Pessoa(proximoId++, nome, endereco, contato),
          especializacao(espec), crm(crm) {}

    // Construtor com ID (se quiser carregar de arquivo)
    Medico(int id, const string& nome, const string& espec,
           const string& crm, const string& endereco,
           const string& contato)
        : Pessoa(id, nome, endereco, contato),
          especializacao(espec), crm(crm) {}

    string getEspecializacao() const { return especializacao; }
    string getCRM() const { return crm; }

    void imprimir() const override {
        Pessoa::imprimir();
        cout << " | CRM: " << crm
             << " | Especialização: " << especializacao << endl;
    }
};

#endif
