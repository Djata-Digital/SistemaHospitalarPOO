#include "SistemaHospitalar.hpp"

SistemaHospitalar::SistemaHospitalar() {
    carregarTudo();
}

SistemaHospitalar::~SistemaHospitalar() {
    salvarTudo();
    for (auto p : pacientes) delete p;
    for (auto m : medicos) delete m;
    for (auto c : consultas) delete c;
}

// ---------------------- EXECUÇÃO PRINCIPAL ----------------------

void SistemaHospitalar::executar() {
    int op;
    do {
        cout << "\n===== SISTEMA HOSPITALAR =====\n";
        cout << "1 - Gestao de Pacientes\n";
        cout << "2 - Gestao de Medicos\n";
        cout << "3 - Agendamento de Consultas\n";
        cout << "4 - Prontuarios Medicos\n";
        cout << "5 - Estatisticas\n";
        cout << "0 - Sair\n";
        op = lerInt("Opcao: ");

        switch (op) {
            case 1: menuPacientes(); break;
            case 2: menuMedicos(); break;
            case 3: menuConsultas(); break;
            case 4: menuProntuario(); break;
            case 5: estatisticas(); break;
            case 0: cout << "Saindo...\n"; break;
            default: cout << "Opcao invalida!\n";
        }
    } while (op != 0);
}

// ---------------------- PACIENTES ----------------------

void SistemaHospitalar::menuPacientes() {
    int op;
    do {
        cout << "\n===== PACIENTES =====\n";
        cout << "1 - Cadastrar\n";
        cout << "2 - Listar\n";
        cout << "3 - Editar\n";
        cout << "4 - Remover\n";
        cout << "0 - Voltar\n";
        op = lerInt("Opcao: ");

        switch (op) {
            case 1: cadastrarPaciente(); break;
            case 2: listarPacientes(); break;
            case 3: editarPaciente(); break;
            case 4: removerPaciente(); break;
        }
    } while (op != 0);
}

void SistemaHospitalar::cadastrarPaciente() {
    string nome = lerStr("Nome: ");
    int idade = lerInt("Idade: ");
    string end = lerStr("Endereco: ");
    string cont = lerStr("Contato: ");

    Paciente* p = new Paciente(nome, idade, end, cont);
    pacientes.push_back(p);
    cout << "Paciente cadastrado com ID " << p->getId() << endl;
}

void SistemaHospitalar::listarPacientes() {
    if (pacientes.empty()) {
        cout << "Nenhum paciente cadastrado.\n";
        return;
    }
    for (auto p : pacientes)
        p->imprimir();
}

Paciente* SistemaHospitalar::buscarPaciente(int id) {
    for (auto p : pacientes)
        if (p->getId() == id)
            return p;
    throw runtime_error("Paciente nao encontrado!");
}

void SistemaHospitalar::editarPaciente() {
    int id = lerInt("ID do paciente: ");
    try {
        Paciente* p = buscarPaciente(id);

        cout << "Deixe vazio para manter o valor atual.\n";
        string nome = lerStr("Novo nome (" + p->getNome() + "): ");
        if (!nome.empty()) p->setNome(nome);

        string idadeStr = lerStr("Nova idade (" + to_string(p->getIdade()) + "): ");
        if (!idadeStr.empty()) p->setIdade(stoi(idadeStr));

        string end = lerStr("Novo endereco (" + p->getEndereco() + "): ");
        if (!end.empty()) p->setEndereco(end);

        string cont = lerStr("Novo contato (" + p->getContato() + "): ");
        if (!cont.empty()) p->setContato(cont);

        cout << "Paciente atualizado.\n";
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::removerPaciente() {
    int id = lerInt("ID do paciente: ");
    try {
        Paciente* p = buscarPaciente(id);

        // Verificar consultas agendadas
        for (auto c : consultas) {
            if (c->getPaciente()->getId() == id &&
                c->getStatus() == "AGENDADA") {
                throw runtime_error("Paciente possui consultas agendadas!");
            }
        }

        for (size_t i = 0; i < pacientes.size(); ++i) {
            if (pacientes[i]->getId() == id) {
                delete pacientes[i];
                pacientes.erase(pacientes.begin() + i);
                cout << "Paciente removido.\n";
                return;
            }
        }
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

// ---------------------- MÉDICOS ----------------------

void SistemaHospitalar::menuMedicos() {
    int op;
    do {
        cout << "\n===== MEDICOS =====\n";
        cout << "1 - Cadastrar\n";
        cout << "2 - Listar\n";
        cout << "3 - Buscar por especialização\n";
        cout << "0 - Voltar\n";
        op = lerInt("Opcao: ");

        switch (op) {
            case 1: cadastrarMedico(); break;
            case 2: listarMedicos(); break;
            case 3: buscarMedicoEspecializacao(); break;
        }
    } while (op != 0);
}

void SistemaHospitalar::cadastrarMedico() {
    string nome = lerStr("Nome: ");
    string esp = lerStr("Especializacao: ");
    string crm = lerStr("CRM: ");
    string end = lerStr("Endereco: ");
    string cont = lerStr("Contato: ");

    Medico* m = new Medico(nome, esp, crm, end, cont);
    medicos.push_back(m);
    cout << "Medico cadastrado com ID " << m->getId() << endl;
}

void SistemaHospitalar::listarMedicos() {
    if (medicos.empty()) {
        cout << "Nenhum medico cadastrado.\n";
        return;
    }
    for (auto m : medicos)
        m->imprimir();
}

Medico* SistemaHospitalar::buscarMedico(int id) {
    for (auto m : medicos)
        if (m->getId() == id)
            return m;
    throw runtime_error("Medico nao encontrado!");
}

void SistemaHospitalar::buscarMedicoEspecializacao() {
    string esp = lerStr("Especializacao: ");
    bool achou = false;
    for (auto m : medicos) {
        if (m->getEspecializacao().find(esp) != string::npos) {
            m->imprimir();
            achou = true;
        }
    }
    if (!achou)
        cout << "Nenhum medico encontrado.\n";
}

// ---------------------- CONSULTAS ----------------------

void SistemaHospitalar::menuConsultas() {
    int op;
    do {
        cout << "\n===== CONSULTAS =====\n";
        cout << "1 - Agendar\n";
        cout << "2 - Listar todas\n";
        cout << "3 - Listar por paciente\n";
        cout << "4 - Listar por medico\n";
        cout << "5 - Alterar data/hora\n";
        cout << "6 - Cancelar\n";
        cout << "7 - Concluir e gerar registro\n";
        cout << "0 - Voltar\n";
        op = lerInt("Opcao: ");

        switch (op) {
            case 1: agendarConsulta(); break;
            case 2: listarConsultas(); break;
            case 3: listarConsultasPorPaciente(); break;
            case 4: listarConsultasPorMedico(); break;
            case 5: alterarConsulta(); break;
            case 6: cancelarConsulta(); break;
            case 7: concluirConsulta(); break;
        }
    } while (op != 0);
}

void SistemaHospitalar::agendarConsulta() {
    int idP = lerInt("ID do paciente: ");
    int idM = lerInt("ID do medico: ");

    try {
        Paciente* p = buscarPaciente(idP);
        Medico*  m = buscarMedico(idM);

        cout << "\nTipo de consulta:\n";
        cout << "1 - Normal\n2 - Emergencia\n3 - Acompanhamento\n";
        int tipo = lerInt("Opcao: ");

        string data = lerStr("Data/Hora (ex: 10/10/2025 14:00): ");

        Consulta* c = nullptr;
        if (tipo == 1) c = new ConsultaNormal(p, m, data);
        else if (tipo == 2) c = new Emergencia(p, m, data);
        else c = new Acompanhamento(p, m, data);

        consultas.push_back(c);
        cout << "Consulta agendada com ID " << c->getId() << endl;

    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::listarConsultas() {
    if (consultas.empty()) {
        cout << "Nenhuma consulta cadastrada.\n";
        return;
    }
    for (auto c : consultas)
        c->imprimir();
}

Consulta* SistemaHospitalar::buscarConsulta(int id) {
    for (auto c : consultas)
        if (c->getId() == id)
            return c;
    throw runtime_error("Consulta nao encontrada!");
}

void SistemaHospitalar::listarConsultasPorPaciente() {
    int id = lerInt("ID do paciente: ");
    try {
        Paciente* p = buscarPaciente(id);
        (void)p; // só para dizer que usamos p

        bool achou = false;
        for (auto c : consultas) {
            if (c->getPaciente()->getId() == id) {
                c->imprimir();
                achou = true;
            }
        }
        if (!achou)
            cout << "Nenhuma consulta para esse paciente.\n";

    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::listarConsultasPorMedico() {
    int id = lerInt("ID do medico: ");
    try {
        Medico* m = buscarMedico(id);
        (void)m;
        bool achou = false;
        for (auto c : consultas) {
            if (c->getMedico()->getId() == id) {
                c->imprimir();
                achou = true;
            }
        }
        if (!achou)
            cout << "Nenhuma consulta para esse medico.\n";

    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::alterarConsulta() {
    int id = lerInt("ID da consulta: ");
    try {
        Consulta* c = buscarConsulta(id);
        string novaData = lerStr("Nova data/hora: ");
        c->setDataHora(novaData);
        cout << "Data/hora atualizada.\n";
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::cancelarConsulta() {
    int id = lerInt("ID da consulta: ");
    try {
        Consulta* c = buscarConsulta(id);
        c->setStatus("CANCELADA");
        cout << "Consulta cancelada.\n";
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::concluirConsulta() {
    int id = lerInt("ID da consulta: ");
    try {
        Consulta* c = buscarConsulta(id);
        c->setStatus("CONCLUiDA");

        string descr = lerStr("Descricao do atendimento: ");
        string presc = lerStr("Prescricao (opcional): ");

        Registro r("Hoje",
                   c->getMedico()->getNome(),
                   c->getMedico()->getEspecializacao(),
                   descr,
                   presc);

        c->getPaciente()->getProntuario().adicionarRegistro(r);
        cout << "Consulta concluida e registro adicionado.\n";

    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

// ---------------------- PRONTUÁRIOS ----------------------

void SistemaHospitalar::menuProntuario() {
    int op;
    do {
        cout << "\n===== PRONTUARIOS =====\n";
        cout << "1 - Adicionar registro manual\n";
        cout << "2 - Visualizar por paciente\n";
        cout << "0 - Voltar\n";
        op = lerInt("Opcao: ");

        switch (op) {
            case 1: adicionarRegistroManual(); break;
            case 2: visualizarProntuario(); break;
        }
    } while (op != 0);
}

void SistemaHospitalar::adicionarRegistroManual() {
    int id = lerInt("ID do paciente: ");
    try {
        Paciente* p = buscarPaciente(id);
        string m = lerStr("Nome do medico: ");
        string esp = lerStr("Especializacao: ");
        string d = lerStr("Descricao: ");
        string pr = lerStr("Prescricao (opcional): ");

        Registro r("Hoje", m, esp, d, pr);
        p->getProntuario().adicionarRegistro(r);
        cout << "Registro adicionado.\n";
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void SistemaHospitalar::visualizarProntuario() {
    int id = lerInt("ID do paciente: ");
    try {
        Paciente* p = buscarPaciente(id);
        cout << "\nPRONTUARIO DE " << p->getNome() << ":\n";
        p->getProntuario().imprimir();
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

// ---------------------- ESTATÍSTICAS ----------------------

void SistemaHospitalar::estatisticas() {
    cout << "\n===== ESTATISTICAS =====\n";
    cout << "Total de pacientes: " << pacientes.size() << endl;
    cout << "Total de medicos: " << medicos.size() << endl;
    cout << "Total de consultas: " << consultas.size() << endl;

    map<string, int> cont;
    for (auto c : consultas)
        cont[c->getMedico()->getEspecializacao()]++;

    cout << "Consultas por especializacao:\n";
    if (cont.empty()) {
        cout << "Nenhuma consulta registrada.\n";
    } else {
        for (auto& kv : cont)
            cout << kv.first << ": " << kv.second << endl;
    }
}

// ---------------------- PERSISTENCIA SIMPLIFICADA ----------------------
// Aqui vamos salvar apenas pacientes e medicos em texto simples.
// Consultas e prontuários ficam em memória (para simplificar).

void SistemaHospitalar::salvarTudo() {
    ofstream arq("dados.txt");
    if (!arq.is_open()) return;

    arq << pacientes.size() << "\n";
    for (auto p : pacientes) {
        arq << p->getId() << ";"
            << p->getNome() << ";"
            << p->getIdade() << ";"
            << p->getEndereco() << ";"
            << p->getContato() << "\n";
    }

    arq << medicos.size() << "\n";
    for (auto m : medicos) {
        arq << m->getId() << ";"
            << m->getNome() << ";"
            << m->getEspecializacao() << ";"
            << m->getCRM() << ";"
            << m->getEndereco() << ";"
            << m->getContato() << "\n";
    }

    arq.close();
}

void SistemaHospitalar::carregarTudo() {
    ifstream arq("dados.txt");
    if (!arq.is_open()) return;

    int qtd;
    string linha;

    // Pacientes
    arq >> qtd;
    getline(arq, linha); // comer quebra de linha

    int maxPacId = 0;
    for (int i = 0; i < qtd; ++i) {
        getline(arq, linha);
        stringstream ss(linha);
        string sid, nome, sidade, end, cont;

        getline(ss, sid, ';');
        getline(ss, nome, ';');
        getline(ss, sidade, ';');
        getline(ss, end, ';');
        getline(ss, cont, ';');

        int id = stoi(sid);
        int idade = stoi(sidade);
        Paciente* p = new Paciente(id, nome, idade, end, cont);
        pacientes.push_back(p);
        if (id > maxPacId) maxPacId = id;
    }
    if (maxPacId >= 1)
        Paciente::proximoId = maxPacId + 1;

    // Medicos
    arq >> qtd;
    getline(arq, linha);

    int maxMedId = 0;
    for (int i = 0; i < qtd; ++i) {
        getline(arq, linha);
        stringstream ss(linha);
        string sid, nome, esp, crm, end, cont;

        getline(ss, sid, ';');
        getline(ss, nome, ';');
        getline(ss, esp, ';');
        getline(ss, crm, ';');
        getline(ss, end, ';');
        getline(ss, cont, ';');

        int id = stoi(sid);
        Medico* m = new Medico(id, nome, esp, crm, end, cont);
        medicos.push_back(m);
        if (id > maxMedId) maxMedId = id;
    }
    if (maxMedId >= 1)
        Medico::proximoId = maxMedId + 1;

    arq.close();
}

// ---------------------- UTILITARIOS ----------------------

int SistemaHospitalar::lerInt(const string& msg) {
    cout << msg;
    int x;
    cin >> x;
    cin.ignore();
    return x;
}

string SistemaHospitalar::lerStr(const string& msg) {
    cout << msg;
    string s;
    getline(cin, s);
    return s;
}
