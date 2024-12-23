#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Pessoa.h"
#include "Multa.h"
#include <string>
#include <iostream>


class Professor : public Pessoa {
public:
    Professor(const std::string& nome, int id);
    ~Professor();

    int getLimiteEmprestimos() const override; 
    bool podeProlongar() const override;       
    float calcularMulta(int diasAtrasado, float taxaBase) const override; 
    std::string tipo() const override;        
    void notificarAtraso(const std::string& tituloLivro, const std::string& dataDevolucao) const override {
        std::cout << "Caro professor, o livro '" << tituloLivro
                  << "' está atrasado para devolução. Data limite: " << dataDevolucao
                  << ". Lembre-se de que você pode solicitar uma prorrogação se necessário.\n";
    }
};

#endif // PROFESSOR_H
