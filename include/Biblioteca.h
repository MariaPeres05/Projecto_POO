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

// Função utilitária para remover espaços em branco do início e do fim de uma string
std::string trim(const std::string& str);

class Biblioteca {
private:
    std::list<Pessoa*> leitores;  // Lista de leitores registrados
    std::vector<Livro*> livros;    // Lista de livros disponíveis
    std::vector<Emprestimo*> emprestimos;  // Lista de empréstimos
    std::map<Livro*, std::list<Pessoa*>> reservas;  

public:
    Biblioteca();
    virtual ~Biblioteca();

    
    // Métodos principais
    bool SaveLivrosToFile(const std::string& filename);
    bool LoadLivrosFromFile(const std::string& filename);
    bool SaveLeitoresToFile(const std::string& filename);  
    bool LoadLeitoresFromFile(const std::string& filename);
    void RelatorioCategoria(const std::string& cat);
    bool SaveEmprestimosToFile(const std::string& filename);
    bool SaveReservasToFile(const std::string& filename);
    bool LoadEmprestimosFromFile(const std::string& filename);
    bool LoadReservasFromFile(const std::string& filename);
    void ProlongarEmprestimos();
    void SistemaNotificacoesAtraso();
    void ListagemLivros();
    void ListagemLeitores();
    bool AddLeitor(Pessoa* P);

    // Métodos auxiliares
    void AdicionarLivro(Livro* livro);
    void RelatorioMultasPendentes();
    void RelatorioEmprestimosPorTipoLivro();
    void RegistarReserva(Livro* livro, Pessoa* leitor);
    void ExibirReservas();
    void devolverLivro(Pessoa* leitor);
    void ListagemLivrosPorCategoria(const std::string& categoria);
    void AddEmprestimo(Emprestimo* emprestimo);
    void registarEmprestimo();  
    const std::list<Pessoa*>& getLeitores() const;
    const std::vector<Livro*>& getLivros() const { return livros; }
    const std::vector<Emprestimo*>& getEmprestimos() const { return emprestimos; }
    const std::map<Livro*, std::list<Pessoa*>>& getReservas() const;
     

    };

#endif // BIBLIOTECA_H
