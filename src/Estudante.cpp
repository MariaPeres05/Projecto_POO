#include "Estudante.h"

Estudante::Estudante(const std::string& nome, int id) : Pessoa(nome, id) {}

Estudante::~Estudante() {}

int Estudante::getLimiteEmprestimos() const {
    return 5; // Estudantes podem levar até 5 livros
}

bool Estudante::podeProlongar() const {
    return true; // Estudantes podem prolongar empréstimos
}

float Estudante::calcularMulta(int diasAtrasado, float taxaBase) const {
    return Multa::calcularMulta(diasAtrasado, taxaBase, 0.5f); // 50% de desconto
}
std::string Estudante::tipo() const {
    return "Estudante";
}
