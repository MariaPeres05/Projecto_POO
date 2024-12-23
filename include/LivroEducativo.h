#ifndef LIVROEDUCATIVO_H
#define LIVROEDUCATIVO_H

#include "Livro.h"


class LivroEducativo : public Livro {
private:
    std::string grauEscolaridade;

public:
    LivroEducativo(const std::string& titulo, const std::string& autor, const std::string& grau);
    ~LivroEducativo() override;

    void exibirDetalhes() const override;
    std::string getCategoria() const override;
    std::string getGrauEscolaridade() const;
};

#endif // LIVROEDUCATIVO_H
