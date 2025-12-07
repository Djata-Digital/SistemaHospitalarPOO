#ifndef SISTEMA_HOSPITALAR_HPP
#define SISTEMA_HOSPITALAR_HPP

#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

#include "Paciente.hpp"
#include "Medico.hpp"
#include "ConsultaNormal.hpp"
#include "Emergencia.hpp"
#include "Acompanhamento.hpp"

using namespace std;

// Controlador do sistema
class SistemaHospitalar {
private:
    vector<Paciente*> pacientes;
    vector<Medico*> medicos;
    vector<Consulta*> consultas;

public:
    SistemaHospitalar();
    ~SistemaHospitalar();

    // Menus
    void executar();
    void menuPacientes();
    void menuMedicos();
    void menuConsultas();
    void menuProntuario();

    // Pacientes
    void cadastrarPaciente();
    void listarPacientes();
    Paciente* buscarPaciente(int id);
    void editarPaciente();
    void removerPaciente();

    // Médicos
    void cadastrarMedico();
    void listarMedicos();
    Medico* buscarMedico(int id);
    void buscarMedicoEspecializacao();

    // Consultas
    void agendarConsulta();
    void listarConsultas();
    Consulta* buscarConsulta(int id);
    void listarConsultasPorPaciente();
    void listarConsultasPorMedico();
    void alterarConsulta();
    void cancelarConsulta();
    void concluirConsulta();

    // Prontuário
    void adicionarRegistroManual();
    void visualizarProntuario();

    // Estatísticas
    void estatisticas();

    // Persistência (simplificada: pacientes e médicos)
    void salvarTudo();
    void carregarTudo();

    // Utils
    int lerInt(const string& msg);
    string lerStr(const string& msg);
};

#endif
