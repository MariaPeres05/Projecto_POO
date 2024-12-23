#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include "Pessoa.h"
#include "Emprestimo.h"
#include "Multa.h"
#include <iostream>


class Estudante : public Pessoa {
public:
    Estudante(const std::string& nome, int id);
    virtual ~Estudante();

    int getLimiteEmprestimos() const override;
    bool podeProlongar() const override;
    float calcularMulta(int diasAtrasado, float taxaBase) const override;
    virtual std::string tipo() const override;
    void notificarAtraso(const std::string& tituloLivro, const std::string& dataDevolucao) const override {
        std::cout << "Caro estudante, você está atrasado para devolver o livro '" << tituloLivro
                  << "'. Data de devolução: " << dataDevolucao << ".\n";
    }
};

#endif // ESTUDANTE_H
