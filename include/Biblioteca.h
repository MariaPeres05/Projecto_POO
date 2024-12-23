#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <list>
#include <map>
#include "Pessoa.h"
#include "Livro.h"
#include "Emprestimo.h"
#include <ctime>
#include <sstream>
#include <vector>
#include <string>

class Biblioteca {
private:
    std::list<Pessoa*> leitores;  // Lista de leitores registrados
    std::vector<Livro*> livros;    // Lista de livros disponíveis
    std::list<Emprestimo*> emprestimos;  // Lista de empréstimos ativos

public:
    Biblioteca();
    virtual ~Biblioteca();

    // Métodos principais
    bool SaveLivrosToFile(const std::string& filename);
    bool LoadLivrosFromFile(const std::string& filename);
    bool SaveLeitoresToFile(const std::string& filename);  
    bool LoadLeitoresFromFile(const std::string& filename);
    void RelatorioCategoria(const std::string& cat);
    void ProlongarEmprestimos();
    void SistemaNotificacoesAtraso();
    void ListagemLivros();
    void ListagemLeitores();
    bool AddLeitor(Pessoa* P);

    // Métodos auxiliares
    void AdicionarLivro(Livro* livro);
    void RelatorioMultasPendentes();
    std::map<Livro*, std::list<Pessoa*>> reservas; // Livro e lista de leitores que reservaram
    void RegistarReserva(Livro* livro, Pessoa* leitor);
    void ExibirReservas();
    void ListagemLivrosPorCategoria(const std::string& categoria);
    void AddEmprestimo(Emprestimo* emprestimo);
    void registarEmprestimo();  
};

#endif // BIBLIOTECA_H
