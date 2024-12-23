#include "LivroEducativo.h"
#include <iostream>

LivroEducativo::LivroEducativo(const std::string& titulo, const std::string& autor, const std::string& grau)
    : Livro(titulo, autor, "Educativo"), grauEscolaridade(grau) {}

LivroEducativo::~LivroEducativo() {}

void LivroEducativo::exibirDetalhes() const {
    std::cout << "Livro Educativo - Título: " << titulo
              << ", Autor: " << autor
              << ", Grau Escolaridade: " << grauEscolaridade
              << ", Disponível: " << (disponivel ? "Sim" : "Não") << std::endl;
}
std::string LivroEducativo::getCategoria() const {
    return "Educativo";
}
std::string LivroEducativo::getGrauEscolaridade() const {
    return grauEscolaridade; // Retorna o atributo grau de escolaridade
}