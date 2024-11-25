#include "Professor.h"

Professor::Professor(const std::string& nome, int id) : Pessoa(nome, id) {}

Professor::~Professor() {}

int Professor::getLimiteEmprestimos() const {
    return 10; // Professores podem levar até 10 livros
}

bool Professor::podeProlongar() const {
    return true; // Professores podem prolongar empréstimos
}

float Professor::calcularMulta(int diasAtrasado, float taxaBase) const {
    return Multa::calcularMulta(diasAtrasado, taxaBase, 0.8f); // 80% de desconto
}

std::string Professor::tipo() const {
    return "Professor";
}
