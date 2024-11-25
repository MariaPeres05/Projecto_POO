
#ifndef LIVROFICCAO_H
#define LIVROFICCAO_H

#include "Livro.h"

class LivroFiccao : public Livro {
public:
    LivroFiccao(const std::string& titulo, const std::string& autor);
    ~LivroFiccao() override;

    void exibirDetalhes() const override;
    virtual std::string getCategoria () const override;
};

#endif // LIVROFICCAO_H
