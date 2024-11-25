#include "LivroCientifico.h"
#include <iostream>

LivroCientifico::LivroCientifico(const std::string& titulo, const std::string& autor, const std::string& area)
    : Livro(titulo, autor, "Científico"), areaCientifica(area) {}

LivroCientifico::~LivroCientifico() {}

void LivroCientifico::exibirDetalhes() const {
    std::cout << "Livro Científico - Título: " << titulo
              << ", Autor: " << autor
              << ", Área: " << areaCientifica
              << ", Disponível: " << (disponivel ? "Sim" : "Não") << std::endl;
}
