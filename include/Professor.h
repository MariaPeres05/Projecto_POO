#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Pessoa.h"
#include "Multa.h"
#include <string>

class Professor : public Pessoa {
public:
    Professor(const std::string& nome, int id);
    ~Professor();

    int getLimiteEmprestimos() const override; 
    bool podeProlongar() const override;       
    float calcularMulta(int diasAtrasado, float taxaBase) const override; 
    std::string tipo() const override;        
};

#endif // PROFESSOR_H
