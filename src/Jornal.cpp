#include "Jornal.h"
#include <iostream>

Jornal::Jornal(const std::string& titulo, const std::string& autor, const std::string& dataPublicacao)
    : Livro(titulo, autor, "Jornal"), dataPublicacao(dataPublicacao) {}

Jornal::~Jornal() {}

void Jornal::exibirDetalhes() const {
    std::cout << "Jornal - Título: " << titulo
              << ", Autor: " << autor
              << ", Data de Publicação: " << dataPublicacao
              << ", Disponível: " << (disponivel ? "Sim" : "Não") << std::endl;
}

std::string Jornal::getCategoria() const {
    return "Jornal";
}
std::string Jornal::getDataPublicacao() const {
    return dataPublicacao; // Retorna o atributo data de publicação
}