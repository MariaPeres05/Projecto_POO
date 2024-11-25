#include "LeitorComum.h"

LeitorComum::LeitorComum(const std::string& nome, int id) : Pessoa(nome, id) {}

LeitorComum::~LeitorComum() {}

int LeitorComum::getLimiteEmprestimos() const {
    return 3;  // Leitores comuns podem levar até 3 livros
}

bool LeitorComum::podeProlongar() const {
    return false;  // Leitores comuns não podem prolongar empréstimos
}

float LeitorComum::calcularMulta(int diasAtrasado, float taxaBase) const {
    return diasAtrasado * taxaBase;  // Leitores comuns pagam a multa total
}

std::string LeitorComum::tipo() const {
    return "Leitor Comum";
}