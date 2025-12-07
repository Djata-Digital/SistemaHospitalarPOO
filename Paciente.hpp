#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "Pessoa.hpp"
#include "ProntuarioMedico.hpp"

// Paciente herda de Pessoa e tem um Prontuário (composição)
class Paciente : public Pessoa {
private:
    int idade;
    ProntuarioMedico prontuario;

public:
    static int proximoId; // definido em Modelos.cpp

    // Construtor para novos pacientes (ID automático)
    Paciente(const string& nome, int idade,
             const string& endereco, const string& contato)
        : Pessoa(proximoId++, nome, endereco, contato),
          idade(idade) {}

    // Construtor para quando carregar de arquivo (ID já conhecido)
    Paciente(int id, const string& nome, int idade,
             const string& endereco, const string& contato)
        : Pessoa(id, nome, endereco, contato),
          idade(idade) {}

    int getIdade() const { return idade; }
    void setIdade(int i) { idade = i; }

    ProntuarioMedico& getProntuario() {
        return prontuario;
    }

    void imprimir() const override {
        Pessoa::imprimir();
        cout << " | Idade: " << idade << endl;
    }
};

#endif
