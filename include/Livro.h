#ifndef LIVRO_H
#define LIVRO_H

#include <string>

class Livro {
protected:
    std::string titulo;
    std::string autor;
    std::string categoria;
    bool disponivel;
    bool emprestado; 

public:
    Livro(const std::string& titulo, const std::string& autor, const std::string& categoria);
    virtual ~Livro();

    virtual void exibirDetalhes() const = 0;
    virtual std::string getCategoria() const;
    
    bool estaEmprestado() const;
    bool estaDisponivel() const;
    void marcarComoIndisponivel();
    void marcarComoDisponivel();
    void emprestar();
    void devolver();
    std::string getTitulo() const;
    std::string getAutor() const { return autor; }

    
};

#endif // LIVRO_H


