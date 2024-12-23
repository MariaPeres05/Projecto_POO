#include "LivroFiccao.h"
#include <iostream>

LivroFiccao::LivroFiccao(const std::string& titulo, const std::string& autor)
    : Livro(titulo, autor, "Ficção") {}

LivroFiccao::~LivroFiccao() {}

void LivroFiccao::exibirDetalhes() const {
    std::cout << "Livro de Ficção - Título: " << titulo
              << ", Autor: " << autor
              << ", Disponível: " << (disponivel ? "Sim" : "Não") << std::endl;
}

std::string LivroFiccao::getCategoria() const {
    return "Ficção"; 
}
std::string LivroFiccao::getTituloFiccao() const {
    return titulo;
}