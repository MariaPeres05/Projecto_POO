#include "Emprestimo.h"
#include "Uteis.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

Emprestimo::Emprestimo(Livro* livro, Pessoa* leitor)
    : livro(livro), leitor(leitor) {
    // Obter data atual como data de empréstimo
    time_t now = time(0);
    dataEmprestimo = ctime(&now);

    // Definir data de devolução (exemplo: 7 dias à frente)
    tm* t = localtime(&now);
    t->tm_mday += 7;
    mktime(t); // Ajusta a estrutura tm caso exceda o mês
    dataDevolucao = asctime(t);
}

Emprestimo::~Emprestimo() {}

int calcularDiasAtrasados(const std::string& dataDevolucao) {
    time_t agora = time(0); // Data atual
    struct tm tmAgora = *localtime(&agora); // Preenche tmAgora com a data e hora atuais
    struct tm tmDevolucao = {};
    std::istringstream ss(dataDevolucao);
    ss >> std::get_time(&tmDevolucao, "%Y-%m-%d"); // Formato personalizado
    if (ss.fail()) {
        std::cerr << "Erro ao analisar a data de devolução: " << dataDevolucao << std::endl;
        return -1;
    }
    time_t tDevolucao = mktime(&tmDevolucao);
    if (tDevolucao == -1) {
        std::cerr << "Erro ao converter a data de devolução." << std::endl;
        return -1;
    }
    // Calcula a diferença em segundos e converte para dias
    double diffSegundos = difftime(agora, tDevolucao);
    return static_cast<int>(diffSegundos / (60 * 60 * 24)); // Retorna a diferença em dias
}

bool Emprestimo::estaAtrasado() const {
    time_t now = time(0);

    time_t devolucao = Uteis::parseDateTime(dataDevolucao.c_str(), "%a %b %d %H:%M:%S %Y");
    if (devolucao == -1) {
        std::cerr << "Erro ao processar a data de devolução." << std::endl;
        return false;
    }

    return difftime(now, devolucao) > 0;
}

void Emprestimo::prolongar() {
    // Converte dataDevolucao de string para time_t usando a função parseDateTime
    time_t devolucaoTime = Uteis::parseDateTime(dataDevolucao.c_str(), "%a %b %d %H:%M:%S %Y");
    if (devolucaoTime == -1) {
        std::cerr << "Erro ao processar a data de devolução." << std::endl;
        return;
    }
    tm* tDevolucao = localtime(&devolucaoTime); // Converte para tm
    tDevolucao->tm_mday += 7; // Adiciona 7 dias à data de devolução
    mktime(tDevolucao);
    // Converte de volta para string com a data formatada
    char novaDataDevolucao[100];
    strftime(novaDataDevolucao, sizeof(novaDataDevolucao), "%a %b %d %H:%M:%S %Y", tDevolucao);
    dataDevolucao = novaDataDevolucao; // Atualiza a string de dataDevolucao
    std::cout << "Empréstimo prolongado até: " << dataDevolucao << std::endl;
}


void Emprestimo::notificarAtraso() const {
    std::cout << "O leitor " << leitor->getNome() << " está atrasado para devolver o livro '"
              << livro->getTitulo() << "'. Data limite: " << dataDevolucao << std::endl;
}

bool Emprestimo::podeProlongar() const {
    return leitor->podeProlongar();
}

std::string Emprestimo::getDataDevolucao() const {
    return dataDevolucao;
}

Livro* Emprestimo::getLivro() const {
    return livro;
}