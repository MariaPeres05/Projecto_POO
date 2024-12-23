#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <string>
#include "Livro.h"
#include "Pessoa.h"
#include "Multa.h"

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
    float calcularMulta(float taxaBase, float desconto = 0.0f);

    Pessoa* getLeitor() const;
    Livro* getLivro() const;                 
    std::string getDataDevolucao() const;    
    std::string getDataEmprestimo() const { return dataEmprestimo; }
    void setDataDevolucao(const std::string& data) { dataDevolucao = data; }
    void setDataEmprestimo(const std::string& data) { dataEmprestimo = data; }
};

#endif // EMPRESTIMO_H
