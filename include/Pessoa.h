#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
protected:
    std::string nome;
    int id;

public:
    Pessoa(const std::string& nome, int id);
    virtual ~Pessoa();

    virtual int getLimiteEmprestimos() const = 0;
    virtual bool podeProlongar() const = 0;
    virtual float calcularMulta(int diasAtrasado, float taxaBase) const = 0;
    virtual std::string tipo() const = 0;
    int getId() const { return id; }

    std::string getNome() const { return nome; }
};

#endif // PESSOA_H

