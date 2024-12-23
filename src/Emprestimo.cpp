#include "Emprestimo.h"
#include "Uteis.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>


Emprestimo::Emprestimo(Livro* livro, Pessoa* leitor)
    : livro(livro), leitor(leitor) {
    time_t now = time(0);
    dataEmprestimo = ctime(&now);

    tm* t = localtime(&now);
    t->tm_mday += 7;  // 7 dias para devolução
    mktime(t);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);
    dataDevolucao = buffer;
}

Emprestimo::~Emprestimo() {}

std::string Emprestimo::getDataDevolucao() const {
    return dataDevolucao;
}

Pessoa* Emprestimo::getLeitor() const {
    return leitor;
}

Livro* Emprestimo::getLivro() const {
    return livro;
}

int Emprestimo::calcularDiasAtrasados(const std::string& dataDevolucao) {
    time_t agora = time(0); // Data atual
    struct tm tmDevolucao = {}; // Declara e inicializa a estrutura 'tm'
    std::istringstream ss(dataDevolucao);

    // Parsing manual da data no formato "YYYY-MM-DD"
    ss >> std::setw(4) >> tmDevolucao.tm_year; // Ano
    tmDevolucao.tm_year -= 1900;              // Ajusta o ano para struct tm
    ss.ignore(1);                             // Ignora o separador '-'
    ss >> std::setw(2) >> tmDevolucao.tm_mon; // Mês
    tmDevolucao.tm_mon -= 1;                  // Ajusta o mês para struct tm
    ss.ignore(1);                             // Ignora o separador '-'
    ss >> std::setw(2) >> tmDevolucao.tm_mday; // Dia

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
    time_t devolucao = Uteis::parseDateTime(dataDevolucao.c_str(), "%Y-%m-%d");
    return (devolucao != -1) && (difftime(time(0), devolucao) > 0);
}

void Emprestimo::prolongar() {
    time_t devolucao = Uteis::parseDateTime(dataDevolucao.c_str(), "%Y-%m-%d");
    if (devolucao == -1) return;

    tm* tDevolucao = localtime(&devolucao);
    tDevolucao->tm_mday += 7;
    mktime(tDevolucao);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tDevolucao);
    dataDevolucao = buffer;
}

void Emprestimo::notificarAtraso() const {
    std::cout << "O leitor " << leitor->getNome() << " está atrasado para devolver '"
              << livro->getTitulo() << "'. Data limite: " << dataDevolucao << ".\n";
}

bool Emprestimo::podeProlongar() const {
    return leitor->podeProlongar();
}
