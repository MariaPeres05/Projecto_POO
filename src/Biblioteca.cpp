#include "Biblioteca.h"
#include "LivroFiccao.h"
#include "LivroCientifico.h"
#include "LivroEducativo.h"
#include "Jornal.h"
#include "Revista.h"
#include "Estudante.h"      
#include "Professor.h"      
#include "LeitorComum.h"    
#include "Senior.h"    
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>



Biblioteca::Biblioteca() {}

Biblioteca::~Biblioteca() {
    // Libertar memória
    for (auto leitor : leitores) delete leitor;
    for (auto livro : livros) delete livro;
    for (auto emprestimo : emprestimos) delete emprestimo;
}

bool Biblioteca::SaveLivrosToFile(const std::string& filename)
 {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para escrita.\n";
        return false;
    }

    for (const auto& livro : livros) {
        if (auto* ficcao = dynamic_cast<LivroFiccao*>(livro)) {
            file << ficcao->getCategoria() << ";" << ficcao->getTitulo() << ";" << ficcao->getAutor() << ";\n";
        } else if (auto* cientifico = dynamic_cast<LivroCientifico*>(livro)) {
            file << cientifico->getCategoria() << ";" << cientifico->getTitulo() << ";" 
                 << cientifico->getAutor() << ";" << cientifico->getAreaCientifica() << "\n";
        } else if (auto* educativo = dynamic_cast<LivroEducativo*>(livro)) {
            file << educativo->getCategoria() << ";" << educativo->getTitulo() << ";" 
                 << educativo->getAutor() << ";" << educativo->getGrauEscolaridade() << "\n";
        } else if (auto* jornal = dynamic_cast<Jornal*>(livro)) {
            file << jornal->getCategoria() << ";" << jornal->getTitulo() << ";" 
                 << jornal->getAutor() << ";" << jornal->getDataPublicacao() << "\n";
        } else if (auto* revista = dynamic_cast<Revista*>(livro)) {
            file << revista->getCategoria() << ";" << revista->getTitulo() << ";" 
                 << revista->getAutor() << ";" << revista->getNumeroEdicao() << "\n";
        }
    }
    file.close();
    return true;
}

bool Biblioteca::SaveLeitoresToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para escrita.\n";
        return false;
    }

    for (const auto& leitor : leitores) {
        file << leitor->tipo() << ";" << leitor->getNome() << ";" << leitor->getId() << ";" 
             << leitor->getLimiteEmprestimos() << "\n";
    }

    file.close();
    return true;
}


bool Biblioteca::LoadLivrosFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para leitura.\n";
        return false;
    }

    std::string linha;
    while (std::getline(file, linha)) {
        std::istringstream stream(linha);
        std::string categoria, titulo, autor, extra;

        // Lê os campos separados por ";"
        std::getline(stream, categoria, ';');
        std::getline(stream, titulo, ';');
        std::getline(stream, autor, ';');
        std::getline(stream, extra, ';'); // Campo adicional (como data ou número da edição)

        Livro* novoLivro = nullptr;

        if (categoria == "Ficcao") {
            novoLivro = new LivroFiccao(titulo, autor);
        } else if (categoria == "Científico") {
            novoLivro = new LivroCientifico(titulo, autor, extra);
        } else if (categoria == "Educativo") {
            novoLivro = new LivroEducativo(titulo, autor, extra);
        } else if (categoria == "Jornal") {
            novoLivro = new Jornal(titulo, autor, extra); // Extra contém a data de publicação
        } else if (categoria == "Revista") {
            int numeroEdicao = std::stoi(extra);
            novoLivro = new Revista(titulo, autor, numeroEdicao); // Extra contém o número da edição
        }

        // Valida e adiciona o livro à lista
        if (novoLivro) {
            livros.push_back(novoLivro);
        } else {
            std::cerr << "Erro ao processar a linha: " << linha << "\n";
        }
    }
    file.close();
    return true;
}


bool Biblioteca::LoadLeitoresFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para leitura.\n";
        return false;
    }

    std::string linha;
    while (std::getline(file, linha)) {
        std::istringstream stream(linha);
        std::string tipo, nome;
        int id;

        // Lê os campos separados por ";"
        std::getline(stream, tipo, ';');
        std::getline(stream, nome, ';');
        stream >> id;

        Pessoa* novoLeitor = nullptr;

        if (tipo == "Estudante") {
            novoLeitor = new Estudante(nome, id);
        } else if (tipo == "Professor") {
            novoLeitor = new Professor(nome, id);
        } else if (tipo == "Leitor Comum") {
            novoLeitor = new LeitorComum(nome, id);
        } else if (tipo == "Senior") {
            novoLeitor = new Senior(nome, id);
        }

        // Valida e adiciona o leitor à lista
        if (novoLeitor) {
            leitores.push_back(novoLeitor);
        } else {
            std::cerr << "Erro ao processar a linha: " << linha << "\n";
        }
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
    std::cout << "Listagem de Leitores Registados:" << std::endl;
    if (leitores.empty()) {
        std::cout << "Nenhum leitor registado na biblioteca." << std::endl;
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

    if (!this->SaveLeitoresToFile("leitores.txt")) {
        std::cerr << "Erro ao salvar o leitor no ficheiro.\n";
        return false;
    }

    return true;
}



void Biblioteca::AdicionarLivro(Livro* livro) {
    if (!livro) {
        std::cerr << "Erro ao adicionar o livro: livro inválido!" << std::endl;
        return;
    }

    // Verificar duplicatas
    for (const auto& l : livros) {
        if (l->getTitulo() == livro->getTitulo() && 
            l->getAutor() == livro->getAutor() &&
            l->getCategoria() == livro->getCategoria()) {
            std::cout << "Livro já existe na biblioteca! Não foi adicionado.\n";
            delete livro; // Evita vazamento de memória
            return;
        }
    }

    // Adicionar o livro se não for duplicado
    livros.push_back(livro);
    std::cout << "Livro adicionado - " << livro->getTitulo() << " Categoria: " << livro->getCategoria() << std::endl;

    // Salvar no ficheiro após adicionar
    if (!SaveLivrosToFile("livros.txt")) {
        std::cerr << "Erro ao salvar o livro no ficheiro.\n";
    }
}



void Biblioteca::AddEmprestimo(Emprestimo* emprestimo) {
    emprestimos.push_back(emprestimo);
    std::cout << "Empréstimo adicionado com sucesso.\n";
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
    std::cout << "Livros da categoria: " << categoria << std::endl;

    int index = 1; // Inicializa o índice do livro
    for (const auto& livro : livros) { // Itera sobre todos os livros no vetor 'livros'
        if (livro->getCategoria() == categoria) {
            std::cout << "Livro " << index++ << " - " << livro->getTitulo() << std::endl;
        }
    }

    if (index == 1) { // Nenhum livro listado
        std::cout << "Nenhum livro encontrado na categoria " << categoria << "." << std::endl;
    }
}



void Biblioteca::registarEmprestimo() {
    if (livros.empty() || leitores.empty()) {
        std::cout << "Não há livros ou leitores disponíveis para empréstimos.\n";
        return;
    }

    // Listar livros disponíveis
    std::cout << "Livros disponíveis:\n";
    int i = 1;
    for (auto livro : livros) {
        if (livro->estaDisponivel()) {
            std::cout << i++ << ". " << livro->getTitulo() << " - " << livro->getAutor() << "\n";
        }
    }

    int livroEscolhido;
    std::cout << "Escolha um livro pelo número: ";
    std::cin >> livroEscolhido;

    if (livroEscolhido < 1 || livroEscolhido >= i) {
        std::cout << "Escolha inválida.\n";
        return;
    }

    auto livroSelecionado = livros[livroEscolhido - 1];
    if (!livroSelecionado->estaDisponivel()) {
        std::cout << "O livro já está emprestado.\n";
        return;
    }

    // Listar leitores
    std::cout << "Leitores disponíveis:\n";
    i = 1;
    for (auto leitor : leitores) {
        std::cout << i++ << ". " << leitor->getNome() << " (ID: " << leitor->getId() << ")\n";
    }

    int leitorEscolhido;
    std::cout << "Escolha um leitor pelo número: ";
    std::cin >> leitorEscolhido;

    if (leitorEscolhido < 1 || leitorEscolhido >= i) {
        std::cout << "Escolha inválida.\n";
        return;
    }
    auto leitorSelecionado = leitores.front();
    Emprestimo* novoEmprestimo = new Emprestimo(livroSelecionado, leitorSelecionado);
    emprestimos.push_back(novoEmprestimo);
    livroSelecionado->marcarComoIndisponivel();
    std::cout << "Empréstimo registrado com sucesso!\n";
}