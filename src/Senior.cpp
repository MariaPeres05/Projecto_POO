#include "Senior.h"

Senior::Senior(const std::string& nome, int id) : Pessoa(nome, id) {}

Senior::~Senior() {}

int Senior::getLimiteEmprestimos() const {
    return 2;  // Leitores seniores podem levar até 2 livros
}

bool Senior::podeProlongar() const {
    return true;  // Seniores podem prolongar empréstimos
}

float Senior::calcularMulta(int diasAtrasado, float taxaBase) const {
    return Multa::calcularMulta(diasAtrasado, taxaBase, 0.3f);  // 30% de desconto na multa
}

std::string Senior::tipo() const {
    return "Senior";
}
