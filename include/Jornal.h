#ifndef JORNAL_H
#define JORNAL_H

#include "Livro.h"

class Jornal : public Livro {
private:
    std::string dataPublicacao;  // Data de publicação do jornal

public:
    Jornal(const std::string& titulo, const std::string& autor, const std::string& dataPublicacao);
    ~Jornal() override;

    void exibirDetalhes() const override;
    std::string getCategoria() const override;
};

#endif // JORNAL_H
