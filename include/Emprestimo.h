#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H
//#include <ctime>
#include <string>
#include "Livro.h"
#include "Pessoa.h"

class Emprestimo {
private:
    Livro* livro;
    Pessoa* leitor;
    std::string dataEmprestimo;
    std::string dataDevolucao;

public:
    Emprestimo(Livro* livro, Pessoa* leitor);
    ~Emprestimo();
    
    int calcularDiasAtrasados(const std::string& dataDevolucao);
    bool estaAtrasado() const;
    void prolongar();
    void notificarAtraso() const;
    bool podeProlongar() const;
    Pessoa* getLeitor() const {
        return leitor;
    }
    std::string getDataDevolucao() const;
    Livro* getLivro() const; 
};

#endif // EMPRESTIMO_H
