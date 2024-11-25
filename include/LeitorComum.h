#ifndef LEITORCOMUM_H
#define LEITORCOMUM_H

#include "Pessoa.h"

class LeitorComum : public Pessoa {
public:
    LeitorComum(const std::string& nome, int id);
    virtual ~LeitorComum();

    int getLimiteEmprestimos() const override;
    bool podeProlongar() const override;
    float calcularMulta(int diasAtrasado, float taxaBase) const override;
    std::string tipo() const override;
};

#endif // LEITORCOMUM_H