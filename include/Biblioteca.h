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

class Biblioteca {
private:
    std::list<Pessoa*> leitores;  // Lista de leitores registrados
    std::list<Livro*> livros;     // Lista de livros disponíveis
    std::list<Emprestimo*> emprestimos;  // Lista de empréstimos ativos

public:
    Biblioteca();
    virtual ~Biblioteca();

    // Métodos principais
    bool SaveToFile(std::string nf);
    bool LoadFile(std::string nf);
    void RelatorioCategoria(const std::string& cat);
    void ProlongarEmprestimos();
    void SistemaNotificacoesAtraso();
    void ListagemLivros();
    void ListagemLeitores();
    bool AddLeitor(Pessoa* P);

    // Métodos auxiliares
    void AdicionarLivro(Livro* livro);
    void RegistarEmprestimo(Livro* livro, Pessoa* leitor);
    void RelatorioMultasPendentes();
    std::map<Livro*, std::list<Pessoa*>> reservas; // Livro e lista de leitores que reservaram
    void RegistarReserva(Livro* livro, Pessoa* leitor);
    void ExibirReservas();
    void ListagemLivrosPorCategoria(const std::string& categoria);

};

#endif // BIBLIOTECA_H
