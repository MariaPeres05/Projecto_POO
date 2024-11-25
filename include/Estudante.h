#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include "Pessoa.h"
#include "Emprestimo.h"
#include "Multa.h"

class Estudante : public Pessoa {
public:
    Estudante(const std::string& nome, int id);
    virtual ~Estudante();

    int getLimiteEmprestimos() const override;
    bool podeProlongar() const override;
    float calcularMulta(int diasAtrasado, float taxaBase) const override;
    virtual std::string tipo() const override;
};

#endif // ESTUDANTE_H
