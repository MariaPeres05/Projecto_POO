#ifndef LEITORCOMUM_H
#define LEITORCOMUM_H

#include "Pessoa.h"
#include <iostream>


class LeitorComum : public Pessoa {
public:
    LeitorComum(const std::string& nome, int id);
    virtual ~LeitorComum();

    int getLimiteEmprestimos() const override;
    bool podeProlongar() const override;
    float calcularMulta(int diasAtrasado, float taxaBase) const override;
    std::string tipo() const override;
    void notificarAtraso(const std::string& tituloLivro, const std::string& dataDevolucao) const override {
        std::cout << "Atenção, o livro '" << tituloLivro
                  << "' está atrasado para devolução. Data limite: " << dataDevolucao
                  << ". Uma multa será aplicada.\n";
    }
};

#endif // LEITORCOMUM_H