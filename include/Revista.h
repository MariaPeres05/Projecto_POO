#ifndef REVISTA_H
#define REVISTA_H

#include "Livro.h"
#include <string>

class Revista : public Livro {
private:
    int numeroEdicao;

public:
    Revista(const std::string& titulo, const std::string& autor, int numeroEdicao);
    ~Revista() override;

    void exibirDetalhes() const override;
    std::string getCategoria() const override;  
    int getNumeroEdicao() const;
};

#endif // REVISTA_H
