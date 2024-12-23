#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <vector>
#include <iostream>


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
    virtual void notificarAtraso(const std::string& tituloLivro, const std::string& dataDevolucao) const = 0;
    int getId() const { return id; }
    bool AddLeitor(Pessoa* P);
    std::string getNome() const { return nome; }
};

#endif // PESSOA_H

