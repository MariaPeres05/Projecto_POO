#include "include/Biblioteca.h"
#include "include/LivroFiccao.h"
#include "include/Estudante.h"
#include "include/Professor.h"
#include "include/Senior.h"
#include "include/LeitorComum.h"
#include "include/LivroCientifico.h"
#include "include/LivroEducativo.h"
#include "include/Revista.h"
#include "include/Jornal.h"
#include "include/Multa.h"
#include <iostream>
#include <limits>

void exibirMenuInicial() {
    std::cout << "\n=========== Sistema de Gestão de Biblioteca ===========" << std::endl;
    std::cout << "1. Bibliotecário" << std::endl;
    std::cout << "2. Leitor" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

void exibirSubmenuLeitor() {
    std::cout << "\n=========== Escolha o Tipo de Leitor ===========" << std::endl;
    std::cout << "1. Estudante" << std::endl;
    std::cout << "2. Professor" << std::endl;
    std::cout << "3. Leitor Comum" << std::endl;
    std::cout << "4. Senior" << std::endl;
    std::cout << "0. Voltar ao menu inicial" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

void exibirMenuLeitor() {
    std::cout << "\n=========== Menu do Leitor ===========" << std::endl;
    std::cout << "1. Listar Livros Disponíveis" << std::endl;
    std::cout << "2. Verificar Multas Pendentes" << std::endl;
    std::cout << "3. Verificar Empréstimos e Reservas" << std::endl;
    std::cout << "0. Voltar ao menu anterior" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

void exibirMenuBibliotecario() {
    std::cout << "\n=========== Menu do Bibliotecário ===========" << std::endl;
    std::cout << "1. Adicionar Livro" << std::endl;
    std::cout << "2. Listar Livros por Categoria" << std::endl;
    std::cout << "3. Adicionar Leitor" << std::endl;
    std::cout << "4. Listar Leitores" << std::endl;
    std::cout << "5. Registrar Empréstimo" << std::endl;
    std::cout << "6. Sistema de Reservas" << std::endl;
    std::cout << "7. Sistema de Notificações de Atraso" << std::endl;
    std::cout << "8. Gerar Relatório de Multas" << std::endl;
    std::cout << "0. Voltar ao menu inicial" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main() {
    Biblioteca biblioteca;
    int opcao;

    do {
        exibirMenuInicial();
        std::cin >> opcao;
        std::cin.ignore(); // Limpar buffer de entrada

        switch (opcao) {
            case 1: { // Menu do Bibliotecário
                int opcaoBibliotecario;
                do {
                    exibirMenuBibliotecario();
                    std::cin >> opcaoBibliotecario;
                    std::cin.ignore();

                    switch (opcaoBibliotecario) {
                        case 1: {
                            // Adicionar Livro
                            std::cout << "Escolha o tipo de livro:\n1. Ficção\n2. Científico\n3. Educativo\n4. Revista\n5. Jornal\n";
                            int tipoLivro;
                            std::cin >> tipoLivro;
                            std::cin.ignore();
                            std::string titulo, autor, extra;

                            std::cout << "Digite o título: ";
                            std::getline(std::cin, titulo);
                            std::cout << "Digite o autor: ";
                            std::getline(std::cin, autor);

                            Livro* novoLivro = nullptr;
                            if (tipoLivro == 1) {
                                novoLivro = new LivroFiccao(titulo, autor);
                            } else if (tipoLivro == 2) {
                                std::cout << "Digite a área científica: ";
                                std::getline(std::cin, extra);
                                novoLivro = new LivroCientifico(titulo, autor, extra);
                            } else if (tipoLivro == 3) {
                                std::cout << "Digite o grau de escolaridade: ";
                                std::getline(std::cin, extra);
                                novoLivro = new LivroEducativo(titulo, autor, extra);
                            } else if (tipoLivro == 4) {
                                std::cout << "Digite o número da edição: ";
                                std::getline(std::cin, extra);
                                novoLivro = new Revista(titulo, autor, std::stoi(extra));
                            } else if (tipoLivro == 5) {
                                std::cout << "Digite a data de publicação: ";
                                std::getline(std::cin, extra);
                                novoLivro = new Jornal(titulo, autor, extra);
                            }

                            if (novoLivro) {
                                biblioteca.AdicionarLivro(novoLivro);
                                std::cout << "Livro adicionado com sucesso!\n";
                            } else {
                                std::cout << "Erro ao adicionar livro.\n";
                            }
                            break;
                        }
                        case 2: {
                            // Listar Livros por Categoria
                            std::string categoria;
                            std::cout << "Digite a categoria: ";
                            std::cin.ignore();
                            std::getline(std::cin, categoria);
                            biblioteca.ListagemLivrosPorCategoria(categoria);
                            break;
                        }
                        case 0:
                            std::cout << "Voltando ao menu inicial...\n";
                            break;
                        default:
                            std::cout << "Opção inválida! Tente novamente.\n";
                    }
                } while (opcaoBibliotecario != 0);
                break;
            }
            case 2: { // Menu do Leitor
                int tipoLeitor;
                do {
                    exibirSubmenuLeitor();
                    std::cin >> tipoLeitor;
                    std::cin.ignore();

                    if (tipoLeitor == 0) {
                        std::cout << "Voltando ao menu inicial...\n";
                        break;
                    }

                    int opcaoLeitor;
                    do {
                        exibirMenuLeitor();
                        std::cin >> opcaoLeitor;
                        std::cin.ignore();

                        switch (opcaoLeitor) {
                            case 1:
                                biblioteca.ListagemLivros();
                                break;
                            case 2:
                                biblioteca.RelatorioMultasPendentes();
                                break;
                            case 3:
                                biblioteca.ExibirReservas();
                                break;
                            case 0:
                                std::cout << "Voltando ao menu anterior...\n";
                                break;
                            default:
                                std::cout << "Opção inválida! Tente novamente.\n";
                        }
                    } while (opcaoLeitor != 0);
                } while (tipoLeitor != 0);
                break;
            }
            case 0:
                std::cout << "Encerrando o programa...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
}
