#include "include/Biblioteca.h"
#include "include/LivroFiccao.h"
#include "include/Estudante.h"
#include "include/LivroCientifico.h"
#include "include/Professor.h"
#include "include/LeitorComum.h"
#include "include/Multa.h"
#include <iostream>
#include <limits>
#include "include/Emprestimo.h"
#include "include/Livro.h"
#include "include/Pessoa.h"



void exibirMenu() {
    std::cout << "\n================ Biblioteca =================" << std::endl;
    std::cout << "1. Listar Livros" << std::endl;
    std::cout << "2. Adicionar Livro" << std::endl;
    std::cout << "3. Listar Leitores" << std::endl;
    std::cout << "4. Adicionar Leitor" << std::endl;
    std::cout << "5. Registar Empréstimo" << std::endl;
    std::cout << "6. Verificar Multas Pendentes" << std::endl;
    std::cout << "7. Prolongar Empréstimos" << std::endl;
    std::cout << "8. Verificar Atrasos(se houverem)" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main() {
    Biblioteca biblioteca;

    int opcao;
    do {
        exibirMenu();
        std::cin >> opcao;
        std::cin.ignore(); // Limpar buffer para evitar problemas com getline

        switch (opcao) {
            case 1: { // Listar Livros
                biblioteca.ListagemLivros();
                break;
            }
            case 2: { // Adicionar Livro
                std::cout << "Escolha o tipo de livro a ser adicionado:\n";
                std::cout << "1. Ficção\n2. Científico\n3.Livro Educativo\n";
                int tipoLivro;
                std::cin >> tipoLivro;
                std::cin.ignore();

                std::string titulo, autor, areaOuCategoria;
                std::cout << "Digite o título: ";
                std::getline(std::cin, titulo);
                std::cout << "Digite o autor: ";
                std::getline(std::cin, autor);

                Livro* novoLivro = nullptr;
                if (tipoLivro == 1) {
                    novoLivro = new LivroFiccao(titulo, autor);
                } else if (tipoLivro == 2) {
                    std::cout << "Digite a área científica: ";
                    std::getline(std::cin, areaOuCategoria);
                    novoLivro = new LivroCientifico(titulo, autor, areaOuCategoria);
                }

                if (novoLivro) {
                    biblioteca.AdicionarLivro(novoLivro);
                } else {
                    std::cout << "Tipo de livro inválido!" << std::endl;
                }
                break;
            }
           case 3: { // Listar Leitores
              biblioteca.ListagemLeitores();
              break;
            }
            case 4: { // Adicionar Leitor
                std::cout << "Escolha o tipo de leitor a ser adicionado:\n";
                std::cout << "1. Estudante\n2. Professor\n3. Leitor Comum\n";
                int tipoLeitor;
                std::cin >> tipoLeitor;
                std::cin.ignore();

                std::string nome;
                int id;
                std::cout << "Digite o nome: ";
                std::getline(std::cin, nome);
                std::cout << "Digite o ID: ";
                std::cin >> id;

                Pessoa* novoLeitor = nullptr;
                if (tipoLeitor == 1) {
                    novoLeitor = new Estudante(nome, id);
                } else if (tipoLeitor == 2) {
                    novoLeitor = new Professor(nome, id);
                } else if (tipoLeitor == 3) {
                    novoLeitor = new LeitorComum(nome, id);
                }

                if (novoLeitor) {
                    biblioteca.AddLeitor(novoLeitor);
                } else {
                    std::cout << "Tipo de leitor inválido!" << std::endl;
                }
                break;
            }
            case 5: { // Registar Empréstimo
                std::cout << "Registrar empréstimos ainda não implementado!" << std::endl;
                break;
            }
            case 6: { // Gerar Relatório de Multas Pendentes
                biblioteca.RelatorioMultasPendentes();
                break;
            }
            case 7: { // Prorrogar Empréstimos
                biblioteca.ProlongarEmprestimos();
                break;
            }
            case 8: { // Sistema de Notificações de Atraso
                biblioteca.SistemaNotificacoesAtraso();
                break;
            }
            case 0:
                std::cout << "Saindo do sistema..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
        }
    } while (opcao != 0);

    return 0;
}