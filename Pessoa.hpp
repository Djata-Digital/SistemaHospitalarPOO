#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include <iostream>

using namespace std;

// Classe base abstrata Pessoa
class Pessoa {
protected:
    int id;
    string nome;
    string endereco;
    string contato;

public:
    Pessoa(int id, string nome, string endereco, string contato)
        : id(id), nome(nome), endereco(endereco), contato(contato) {}

    virtual ~Pessoa() {}

    int getId() const { return id; }
    string getNome() const { return nome; }
    string getEndereco() const { return endereco; }
    string getContato() const { return contato; }

    void setNome(const string& n) { nome = n; }
    void setEndereco(const string& e) { endereco = e; }
    void setContato(const string& c) { contato = c; }

    virtual void imprimir() const {
        cout << "ID: " << id
             << " | Nome: " << nome
             << " | Endereço: " << endereco
             << " | Contato: " << contato;
    }
};

#endif
