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
#include <algorithm>


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



std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
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

        std::getline(stream, categoria, ';');
        std::getline(stream, titulo, ';');
        std::getline(stream, autor, ';');
        std::getline(stream, extra, ';');

        categoria = trim(categoria); // Remove espaços extras
        titulo = trim(titulo);
        autor = trim(autor);
        extra = trim(extra);

        Livro* novoLivro = nullptr;

        if (categoria == "Ficção") {
            novoLivro = new LivroFiccao(titulo, autor);
        } else if (categoria == "Científico") {
            novoLivro = new LivroCientifico(titulo, autor, extra);
        } else if (categoria == "Educativo") {
            novoLivro = new LivroEducativo(titulo, autor, extra);
        } else if (categoria == "Jornal") {
            novoLivro = new Jornal(titulo, autor, extra);
        } else if (categoria == "Revista") {
            int numeroEdicao = std::stoi(extra);
            novoLivro = new Revista(titulo, autor, numeroEdicao);
        }

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
        int id, numeroEmprestimos;
        std::getline(stream, tipo, ';');
        std::getline(stream, nome, ';');
        stream >> id;
        stream.ignore(1, ';'); // Ignore the separator
        stream >> numeroEmprestimos;
        stream.ignore(1, ';'); // Ignore the separator

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

        if (novoLeitor) {
            leitores.push_back(novoLeitor);
        } else {
            std::cerr << "Erro ao processar a linha: " << linha << "\n";
        }
    }

    file.close();
    std::cout << "Leitores carregados com sucesso do arquivo.\n";
    return true;
}


bool Biblioteca::SaveEmprestimosToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para salvar os empréstimos.\n";
        return false;
    }

    for (const auto& emprestimo : emprestimos) {
        Livro* livro = emprestimo->getLivro();
        Pessoa* leitor = emprestimo->getLeitor();

        file << livro->getTitulo() << ";"         // Título do livro
             << livro->getAutor() << ";"          // Autor do livro
             << leitor->getId() << ";"            // ID do leitor
             << leitor->getNome() << ";"          // Nome do leitor
             << emprestimo->getDataDevolucao() << ";" // Data de devolução
             << emprestimo->getDataEmprestimo() << "\n"; // Data de empréstimo
    }

    file.close();
    return true;
}

bool Biblioteca::LoadEmprestimosFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para carregar os empréstimos.\n";
        return false;
    }

    std::string linha;
    while (std::getline(file, linha)) {
        std::istringstream stream(linha);
        std::string titulo, autor, nomeLeitor, dataEmprestimo, dataDevolucao;
        int idLeitor;

        std::getline(stream, titulo, ';');
        std::getline(stream, autor, ';');
        stream >> idLeitor;
        stream.ignore(1, ';'); // Ignora o separador ";"
        std::getline(stream, nomeLeitor, ';');
        std::getline(stream, dataEmprestimo, ';');
        std::getline(stream, dataDevolucao, ';');

        // Encontra o livro correspondente
        Livro* livro = nullptr;
        for (auto& l : livros) {
            if (l->getTitulo() == titulo && l->getAutor() == autor) {
                livro = l;
                break;
            }
        }

        if (!livro) {
            std::cerr << "Livro não encontrado: " << titulo << "\n";
            continue;
        }

        // Encontra o leitor correspondente
        Pessoa* leitor = nullptr;
        for (auto& p : leitores) {
            if (p->getId() == idLeitor) {
                leitor = p;
                break;
            }
        }

        if (!leitor) {
            std::cerr << "Leitor não encontrado: " << nomeLeitor << "\n";
            continue;
        }

        // Cria o empréstimo e atualiza o status do livro
        Emprestimo* novoEmprestimo = new Emprestimo(livro, leitor);
        novoEmprestimo->setDataDevolucao(dataDevolucao);
        novoEmprestimo->setDataEmprestimo(dataEmprestimo);
        emprestimos.push_back(novoEmprestimo);

        // Marcar o livro como indisponível
        livro->marcarComoIndisponivel();
    }

    file.close();
    std::cout << "Emprestimos carregados com sucesso do arquivo.\n";
    return true;
}


bool Biblioteca::SaveReservasToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro para escrita.\n";
        return false;
    }

    for (const auto& reserva : reservas) {
        // Reserva[livro] contém a chave (livro) e o valor (lista de leitores)
        for (auto* leitor : reserva.second) {
            file << reserva.first->getTitulo() << ";" // Título do livro
                 << reserva.first->getAutor() << ";"  // Autor do livro
                 << leitor->getNome() << ";"          // Nome do leitor
                 << leitor->getId() << "\n";          // ID do leitor (pode mudar se for necessário)

        }
    }
    file.close();
    return true;
}


bool Biblioteca::LoadReservasFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de reservas para carregar.\n";
        return false;
    }

    std::string linha;
    while (std::getline(file, linha)) {
        std::istringstream stream(linha);
        std::string tituloLivro, autorLivro, nomeLeitor;
        int idLeitor;

        std::getline(stream, tituloLivro, ';');
        std::getline(stream, autorLivro, ';');
        std::getline(stream, nomeLeitor, ';');
        stream >> idLeitor;
        stream.ignore(1, ';'); // Ignorar o separador

        // Procurar o livro correspondente
        Livro* livro = nullptr;
        for (auto& l : livros) {
            if (l->getTitulo() == tituloLivro && l->getAutor() == autorLivro) {
                livro = l;
                break;
            }
        }

        // Procurar o leitor correspondente
        Pessoa* leitor = nullptr;
        for (auto& p : leitores) {
            if (p->getId() == idLeitor) {
                leitor = p;
                break;
            }
        }

        if (livro && leitor) {
            reservas[livro].push_back(leitor);
        } else {
            std::cerr << "Erro ao carregar reserva: Livro ou Leitor não encontrados.\n";
        }
    }

    file.close();
    std::cout << "Reservas carregadas com sucesso do arquivo.\n";
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
            auto leitor = emprestimo->getLeitor();
            auto livro = emprestimo->getLivro();
            leitor->notificarAtraso(livro->getTitulo(), emprestimo->getDataDevolucao());
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
        std::cerr << "Erro: Livro inválido.\n";
        return;
    }

    // Evitar duplicatas verificando antes
    for (const auto& l : livros) {
        if (l->getTitulo() == livro->getTitulo() && l->getAutor() == livro->getAutor()) {
            std::cerr << "Erro: Livro já existe na biblioteca.\n";
            delete livro; // Evita vazamento de memória
            return;
        }
    }

    // Adicionar livro à lista
    livros.push_back(livro);
    std::cout << "Livro adicionado - " << livro->getTitulo()
              << " Categoria: " << livro->getCategoria() << "\n";

    // Salvar no arquivo
    if (!SaveLivrosToFile("livros.txt")) {
        std::cerr << "Erro ao salvar os livros no arquivo.\n";
    } else {
        std::cout << "Livros salvos no arquivo com sucesso.\n";
    }
}


void Biblioteca::AddEmprestimo(Emprestimo* emprestimo) {
    emprestimos.push_back(emprestimo);
    std::cout << "Empréstimo adicionado com sucesso.\n";
}

void Biblioteca::RegistarReserva(Livro* livro, Pessoa* leitor) {
    // Verifica se o livro está disponível. Se estiver, não precisa de ser reservado.
    if (livro->estaDisponivel()) {
        std::cout << "O livro está disponível e não precisa de ser reservado.\n";
        return;
    }

    // Verifica se o livro já foi reservado pelo mesmo leitor
    auto& listaReservas = reservas[livro];
    if (std::find(listaReservas.begin(), listaReservas.end(), leitor) != listaReservas.end()) {
        std::cout << "O leitor já reservou este livro.\n";
        return;
    }

    // Adiciona o leitor à lista de reservas do livro
    listaReservas.push_back(leitor);

    // Print de depuração para verificar se a reserva foi registrada
    std::cout << "Reserva registrada para o livro: " << livro->getTitulo() 
              << " por " << leitor->getNome() << std::endl;

    // Salvar as reservas no arquivo após registá-las
    if (!SaveReservasToFile("reservas.txt")) {
        std::cerr << "Erro ao salvar a reserva no arquivo.\n";
    }
}



void Biblioteca::devolverLivro(Pessoa* leitor) {
    std::cout << "Livros emprestados pelo leitor " << leitor->getNome() << ":\n";

    std::vector<Emprestimo*> emprestimosLeitor;

    // Find books borrowed by the reader
    for (auto& emprestimo : emprestimos) {
        if (emprestimo->getLeitor() == leitor) {
            emprestimosLeitor.push_back(emprestimo);
            std::cout << "- " << emprestimo->getLivro()->getTitulo() << "\n";
        }
    }

    if (emprestimosLeitor.empty()) {
        std::cout << "Nenhum livro emprestado.\n";
        return;
    }

    // Select a book to return
    std::cout << "Escolha o livro a devolver:\n";
    int escolha;
    std::cin >> escolha;

    if (escolha < 1 || escolha > emprestimosLeitor.size()) {
        std::cout << "Escolha inválida.\n";
        return;
    }

    Emprestimo* emprestimoSelecionado = emprestimosLeitor[escolha - 1];

    auto it = std::find(emprestimos.begin(), emprestimos.end(), emprestimoSelecionado);
    if (it != emprestimos.end()) {
    emprestimos.erase(it); // Remove o empréstimo selecionado
     }


    // Mark the book as available
    emprestimoSelecionado->getLivro()->marcarComoDisponivel();
    delete emprestimoSelecionado;

    std::cout << "Livro devolvido com sucesso.\n";

    SaveEmprestimosToFile("emprestimos.txt");
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

const std::map<Livro*, std::list<Pessoa*>>& Biblioteca::getReservas() const {
    return reservas;
}


void Biblioteca::RelatorioMultasPendentes() {
    bool encontrouMultas = false; // Flag para verificar se há multas

    for (auto& emprestimo : emprestimos) {
        if (emprestimo->estaAtrasado()) {
            encontrouMultas = true;

            std::string tituloLivro = emprestimo->getLivro()->getTitulo();
            std::string dataDevolucao = emprestimo->getDataDevolucao();
            Pessoa* leitor = emprestimo->getLeitor();

            int diasAtrasados = emprestimo->calcularDiasAtrasados(dataDevolucao);
            float multa = leitor->calcularMulta(diasAtrasados, 2.0f);

            std::cout << "Leitor: " << leitor->getNome() << "\n";
            std::cout << "Livro: " << tituloLivro << "\n";
            std::cout << "Data de devolução: " << dataDevolucao << "\n";
            std::cout << "Dias atrasados: " << diasAtrasados << "\n";
            std::cout << "Multa: R$ " << multa << "\n\n";
        }
    }

    if (!encontrouMultas) {
        std::cout << "Nenhuma multa pendente encontrada.\n";
    }
}

void Biblioteca::ListagemLivrosPorCategoria(const std::string& categoria) {
    std::cout << "Livros da categoria: " << categoria << "\n";

    bool encontrou = false;
    for (const auto& livro : livros) {
//        std::cout << "Entrei! Livro Autor: " << livro->getAutor() << "\n";
//        std::cout << "Entrei! Livro Categoria: " << livro->getCategoria() << "\n";
        if (livro->getCategoria() == categoria) {
            std::cout << "- " << livro->getTitulo() << " por " << livro->getAutor() << "\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << "Nenhum livro encontrado na categoria " << categoria << ".\n";
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
    std::vector<Livro*> livrosDisponiveis;
    for (auto livro : livros) {
        if (livro->estaDisponivel()) {
            std::cout << i++ << ". " << livro->getTitulo() << " - " << livro->getAutor() << "\n";
            livrosDisponiveis.push_back(livro);
        }
    }

    if (livrosDisponiveis.empty()) {
        std::cout << "Nenhum livro disponível.\n";
        return;
    }

    int livroEscolhido;
    std::cout << "Escolha um livro pelo número: ";
    std::cin >> livroEscolhido;

    if (livroEscolhido < 1 || livroEscolhido > livrosDisponiveis.size()) {
        std::cout << "Escolha inválida.\n";
        return;
    }

    auto livroSelecionado = livrosDisponiveis[livroEscolhido - 1];

    // Listar leitores
    std::cout << "Leitores disponíveis:\n";
    i = 1;
    std::vector<Pessoa*> listaLeitores;
    for (auto leitor : leitores) {
        std::cout << i++ << ". " << leitor->getNome() << " (ID: " << leitor->getId() << ")\n";
        listaLeitores.push_back(leitor);
    }

    int leitorEscolhido;
    std::cout << "Escolha um leitor pelo número: ";
    std::cin >> leitorEscolhido;

    if (leitorEscolhido < 1 || leitorEscolhido > listaLeitores.size()) {
        std::cout << "Escolha inválida.\n";
        return;
    }

    auto leitorSelecionado = listaLeitores[leitorEscolhido - 1];

    // Registrar o empréstimo
    Emprestimo* novoEmprestimo = new Emprestimo(livroSelecionado, leitorSelecionado);
    emprestimos.push_back(novoEmprestimo);
    livroSelecionado->marcarComoIndisponivel();

    std::cout << "Empréstimo registrado com sucesso!\n";

    // Salvar no arquivo
    if (!SaveEmprestimosToFile("emprestimos.txt")) {
        std::cerr << "Erro ao salvar o empréstimo no arquivo.\n";
    }
}

const std::list<Pessoa*>& Biblioteca::getLeitores() const {
    return leitores;
}

void Biblioteca::RelatorioEmprestimosPorTipoLivro() {
    // Mapeia o tipo de livro com os empréstimos e leitores associados
    std::map<std::string, std::map<std::string, int>> emprestimosPorTipoLivro; // Tipo do livro -> (Leitor -> Quantidade)
    // Iterar sobre todos os empréstimos
    for (const auto& emprestimo : emprestimos) {
        Livro* livro = emprestimo->getLivro();
        Pessoa* leitor = emprestimo->getLeitor();
        // Identificador do leitor (Nome ou ID)
        std::ostringstream leitorIdStream;
        leitorIdStream << leitor->getNome() << " (ID: " << leitor->getId() << ")";
        std::string leitorIdentificador = leitorIdStream.str();
        // Atualizar a contagem de empréstimos
        emprestimosPorTipoLivro[livro->getCategoria()][leitorIdentificador]++;
    }
    // Exibir o relatório
    std::cout << "\n======= Relatório de Empréstimos por Tipo de Livro =======\n";
    for (const auto& tipoLivro : emprestimosPorTipoLivro) {
        const std::string& categoria = tipoLivro.first;
        const std::map<std::string, int>& leitores = tipoLivro.second;

        std::cout << "Categoria: " << categoria << "\n";

        int totalEmprestimos = 0;
        std::string leitorMaisFrequente;
        int maxEmprestimos = 0;
        // Detalhes de leitores por categoria
        for (const auto& leitor : leitores) {
            const std::string& identificadorLeitor = leitor.first;
            int quantidade = leitor.second;
            totalEmprestimos += quantidade;

            std::cout << "  - Leitor: " << identificadorLeitor << " | Empréstimos: " << quantidade << "\n";
            if (quantidade > maxEmprestimos) {
                maxEmprestimos = quantidade;
                leitorMaisFrequente = identificadorLeitor;
            }
        }
        // Resumo para cada tipo de livro
        std::cout << "  Total de empréstimos nesta categoria: " << totalEmprestimos << "\n";
        std::cout << "  Leitor mais frequente: " << leitorMaisFrequente << " com " << maxEmprestimos << " empréstimos\n";
        std::cout << "---------------------------------------------------------\n";
    }
    std::cout << "==========================================================\n";
}
