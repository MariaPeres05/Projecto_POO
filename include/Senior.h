#ifndef SENIOR_H
#define SENIOR_H

#include "Pessoa.h"

class Senior : public Pessoa {
public:
    Senior(const std::string& nome, int id);
    ~Senior() override;

    int getLimiteEmprestimos() const override;
    bool podeProlongar() const override;
    float calcularMulta(int diasAtrasado, float taxaBase) const override;
    std::string tipo() const override;
};

#endif // SENIOR_H
