#include "Biblioteca.h"
#include <fstream>


Biblioteca::Biblioteca() {}

Biblioteca::~Biblioteca() {
    // Libertar memória
    for (auto leitor : leitores) delete leitor;
    for (auto livro : livros) delete livro;
    for (auto emprestimo : emprestimos) delete emprestimo;
}

bool Biblioteca::SaveToFile(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return false;
    }
    for (auto livro : livros) {
        file << livro->getCategoria() << "," << livro->getTitulo() << "," << livro->getAutor() << "\n";
    }
    file.close();
    return true;
}

bool Biblioteca::LoadFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return false;
    }
    std::string linha;
    while (std::getline(file, linha)) {
        // Processar linha e recriar objetos
    }
    file.close();
    return true;
}

void Biblioteca::RelatorioCategoria(const std::string& cat) {
    std::cout << "Relatório de livros da categoria: " << cat << std::endl;
    for (auto livro : livros) {
        if (livro->getCategoria() == cat) {
            livro->exibirDetalhes();
        }
    }
}

void Biblioteca::ProlongarEmprestimos() {
    for (auto emprestimo : emprestimos) {
        if (emprestimo->podeProlongar()) {
            emprestimo->prolongar();
        }
    }
}

void Biblioteca::SistemaNotificacoesAtraso() {
    for (auto emprestimo : emprestimos) {
        if (emprestimo->estaAtrasado()) {
            emprestimo->notificarAtraso();
        }
    }
}

void Biblioteca::ListagemLivros() {
    std::cout << "Listagem de Livros na Biblioteca:" << std::endl;
    for (auto livro : livros) {
        livro->exibirDetalhes();
    }
}

void Biblioteca::ListagemLeitores() {
    std::cout << "Listagem de Leitores Registrados:" << std::endl;
    if (leitores.empty()) {
        std::cout << "Nenhum leitor registrado na biblioteca." << std::endl;
        return;
    }

    for (auto leitor : leitores) {
        std::cout << "Nome: " << leitor->getNome() << ", "
                  << "Tipo: " << leitor->tipo() << ", "
                  << "Máximo de Livros: " << leitor->getLimiteEmprestimos()
                  << std::endl;
    }
}

bool Biblioteca::AddLeitor(Pessoa* P) {
    leitores.push_back(P);
    std::cout << "Leitor adicionado com sucesso: " << P->getNome() << std::endl;
    return true;
}

void Biblioteca::AdicionarLivro(Livro* livro) {
    livros.push_back(livro);
    std::cout << "Livro adicionado: " << livro->getTitulo() << std::endl;
}

void Biblioteca::RegistarEmprestimo(Livro* livro, Pessoa* leitor) {
    if (!livro->estaDisponivel()) {
        std::cout << "Livro indisponível para empréstimo." << std::endl;
        return;
    }
    emprestimos.push_back(new Emprestimo(livro, leitor));
    livro->marcarComoIndisponivel();
    std::cout << "Empréstimo registrado com sucesso para: " << leitor->getNome() << std::endl;
}
void Biblioteca::RegistarReserva(Livro* livro, Pessoa* leitor) {
    if (livro->estaDisponivel()) {
        std::cout << "Livro está disponível, não pode ser reservado." << std::endl;
        return;
    }
    reservas[livro].push_back(leitor);
    std::cout << leitor->getNome() << " reservou o livro: " << livro->getTitulo() << std::endl;
}

void Biblioteca::ExibirReservas() {
    for (const auto& reserva : reservas) {
        Livro* livro = reserva.first;
        const std::list<Pessoa*>& leitores = reserva.second;

        std::cout << "Livro: " << livro->getTitulo() << " - Reservado por: ";
        for (auto leitor : leitores) {
            std::cout << leitor->getNome() << " ";
        }
        std::cout << std::endl;
    }
}

void Biblioteca::RelatorioMultasPendentes() {
    for (auto& emprestimo : emprestimos) {
        if (emprestimo->estaAtrasado()) {
            std::time_t dataAtual = std::time(nullptr);  // Obtém o tempo atual
            struct tm* tmDataAtual = localtime(&dataAtual);  // Converte para struct tm
            std::string dataDevolucaoStr = emprestimo->getDataDevolucao();
            struct tm tmDataDevolucao = {0};  // Inicializa tm
            std::stringstream ss(dataDevolucaoStr);
            char delimiter;
            ss >> tmDataDevolucao.tm_mday >> delimiter >> tmDataDevolucao.tm_mon >> delimiter >> tmDataDevolucao.tm_year;
            tmDataDevolucao.tm_mon -= 1;
            tmDataDevolucao.tm_year -= 1900;
            std::time_t tDataDevolucao = std::mktime(&tmDataDevolucao);
            double segundosDeAtraso = std::difftime(dataAtual, tDataDevolucao);
            int diasAtrasados = segundosDeAtraso / (60 * 60 * 24);
            float multa = emprestimo->getLeitor()->calcularMulta(diasAtrasados, 2.0f);
            std::cout << "Leitor: " << emprestimo->getLeitor()->getNome() << std::endl;
            std::cout << "Livro: " << emprestimo->getLivro()->getTitulo() << std::endl;  // Isso pressupõe que você tem o método getLivro()
            std::cout << "Dias Atrasados: " << diasAtrasados << std::endl;
            std::cout << "Multa: " << multa << " reais" << std::endl;
        }
    }
}

void Biblioteca::ListagemLivrosPorCategoria(const std::string& categoria) {
    std::cout << "Livros na Categoria: " << categoria << std::endl;
    for (auto livro : livros) {
        if (livro->getCategoria() == categoria) {
            livro->exibirDetalhes();
        }
    }
}
