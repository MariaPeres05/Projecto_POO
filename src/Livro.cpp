#include "Livro.h"

Livro::Livro(const std::string& titulo, const std::string& autor, const std::string& categoria)
    : titulo(titulo), autor(autor), categoria(categoria), disponivel(true) {}

Livro::~Livro() {}

bool Livro::estaDisponivel() const {
    return disponivel;
}

void Livro::marcarComoIndisponivel() {
    disponivel = false;
}

void Livro::marcarComoDisponivel() {
    disponivel = true;
}

void Livro::emprestar() {
    if (disponivel) {
        disponivel = false;
    }
}

bool Livro::estaEmprestado() const {
    return this->emprestado; // Se a variável emprestado for true, o livro está emprestado
}

void Livro::devolver() {
    disponivel = true;
}

std::string Livro::getCategoria() const {
    return categoria;
}


std::string Livro::getTitulo() const {
    return titulo;
}
