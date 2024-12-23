#include "Revista.h"
#include <iostream>

Revista::Revista(const std::string& titulo, const std::string& autor, int numeroEdicao)
    : Livro(titulo, autor, "Revista"), numeroEdicao(numeroEdicao) {}

Revista::~Revista() {}

void Revista::exibirDetalhes() const {
    std::cout << "Revista - Título: " << titulo
              << ", Autor: " << autor
              << ", Número da Edição: " << numeroEdicao
              << ", Disponível: " << (disponivel ? "Sim" : "Não") << std::endl;
}

std::string Revista::getCategoria() const {
    return "Revista";  
}
int Revista::getNumeroEdicao() const {
    return numeroEdicao; // Retorna o atributo número da edição
}