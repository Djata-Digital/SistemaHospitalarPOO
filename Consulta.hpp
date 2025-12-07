#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>
#include <iostream>
#include "Paciente.hpp"
#include "Medico.hpp"

using namespace std;

// Classe abstrata Consulta
class Consulta {
protected:
    int id;
    static int proximoId; // definido em Modelos.cpp

    Paciente* paciente;
    Medico* medico;

    string dataHora;
    string status; // AGENDADA, CONCLUÍDA, CANCELADA

public:
    Consulta(Paciente* p, Medico* m, const string& dataHora)
        : id(proximoId++), paciente(p), medico(m),
          dataHora(dataHora), status("AGENDADA") {}

    virtual ~Consulta() {}

    int getId() const { return id; }
    Paciente* getPaciente() const { return paciente; }
    Medico* getMedico() const { return medico; }
    string getStatus() const { return status; }
    void setStatus(const string& s) { status = s; }

    string getDataHora() const { return dataHora; }
    void setDataHora(const string& dh) { dataHora = dh; }

    virtual double getValor() const = 0;
    virtual int getDuracao() const = 0;
    virtual int getPrioridade() const = 0;
    virtual string getTipo() const = 0;

    virtual void imprimir() const {
        cout << "Consulta ID: " << id
             << " | Tipo: " << getTipo()
             << " | Paciente: " << paciente->getNome()
             << " | Médico: " << medico->getNome()
             << " (" << medico->getEspecializacao() << ")"
             << " | Data/Hora: " << dataHora
             << " | Status: " << status
             << " | Valor: R$" << getValor()
             << " | Duração: " << getDuracao() << "min"
             << endl;
    }
};

#endif
