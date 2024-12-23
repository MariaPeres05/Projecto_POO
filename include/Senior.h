#ifndef SENIOR_H
#define SENIOR_H

#include "Pessoa.h"
#include "Multa.h"
#include <string>
#include <iostream>


class Senior : public Pessoa {
public:
    Senior(const std::string& nome, int id);
    ~Senior() override;

    int getLimiteEmprestimos() const override;
    bool podeProlongar() const override;
    float calcularMulta(int diasAtrasado, float taxaBase) const override;
    std::string tipo() const override;
     void notificarAtraso(const std::string& tituloLivro, const std::string& dataDevolucao) const override {
        std::cout << "Caro leitor, está atrasado para devolver o livro '" << tituloLivro
                  << "'. Data de devolução: " << dataDevolucao << ".\n";
    }
    
};

#endif // SENIOR_H
