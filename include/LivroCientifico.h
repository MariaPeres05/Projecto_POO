#ifndef LIVROCIENTIFICO_H
#define LIVROCIENTIFICO_H

#include "Livro.h"

class LivroCientifico : public Livro {
private:
    std::string areaCientifica;

public:
    LivroCientifico(const std::string& titulo, const std::string& autor, const std::string& area);
    ~LivroCientifico() override;

    void exibirDetalhes() const override;
};

#endif // LIVROCIENTIFICO_H