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
#include <locale>

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

void menuListarLivrosCategoria(Biblioteca biblioteca) {
    int opcao;
    std::cout << "Escolha a categoria para listar os livros:" << std::endl;
    std::cout << "1. Ficção" << std::endl;
    std::cout << "2. Científico" << std::endl;
    std::cout << "3. Educativo" << std::endl;
    std::cout << "4. Jornal" << std::endl;
    std::cout << "5. Revista" << std::endl;
    std::cout << "6. Voltar ao menu principal" << std::endl;

    std::cout << "Opção: ";
    std::cin >> opcao;

    switch (opcao) {
        case 1:
            biblioteca.ListagemLivrosPorCategoria("Ficcao");
            break;
        case 2:
            biblioteca.ListagemLivrosPorCategoria("Científico");
            break;
        case 3:
            biblioteca.ListagemLivrosPorCategoria("Educativo");
            break;
        case 4:
            biblioteca.ListagemLivrosPorCategoria("Jornal");
            break;
        case 5:
            biblioteca.ListagemLivrosPorCategoria("Revista");
            break;
        case 6:
            std::cout << "Voltando ao menu principal..." << std::endl;
            break;
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
    }
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
    std::cout << "5. Registar Empréstimo" << std::endl;
    std::cout << "6. Sistema de Reservas" << std::endl;
    std::cout << "7. Sistema de Notificações de Atraso" << std::endl;
    std::cout << "8. Gerar Relatório de Multas" << std::endl;
    std::cout << "0. Voltar ao menu inicial" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main() {
    std::setlocale(LC_ALL, "pt_PT.UTF-8");
    Biblioteca biblioteca;
    biblioteca.LoadLivrosFromFile("livros.txt");
    biblioteca.LoadLeitoresFromFile("leitores.txt");
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
                                if (biblioteca.SaveLivrosToFile("livros.txt")) {
                                    std::cout << "Livro salvo no ficheiro com sucesso!\n";
                                } else {
                                    std::cerr << "Erro ao salvar o livro no ficheiro.\n";
                                }
                            } else {
                                std::cerr << "Erro ao criar o livro.\n";
                            }
                            break;
                        }
                        case 2: {
                            // Listar Livros por Categoria
                            menuListarLivrosCategoria(biblioteca);
                            break; 
                        }
                        case 3: {
                            //Adicionar Leitor
                        std::cout << "Escolha o tipo de leitor:\n1. Estudante\n2. Professor\n3. Leitor Comum\n4. Senior\n";
                        int tipoLeitor;
                        std::cin >> tipoLeitor;
                        std::cin.ignore();  // Limpar o buffer
                        std::string nome;
                        std::cout << "Digite o nome do leitor: ";
                        std::getline(std::cin, nome);

                        Pessoa* novoLeitor = nullptr;
                        if (tipoLeitor == 1) {
                        int id;
                        std::cout << "Digite o ID do Estudante: ";
                        std::cin >> id;
                        novoLeitor = new Estudante(nome, id);
                        } else if (tipoLeitor == 2) {
                        int id;
                        std::cout << "Digite o ID do Professor: ";
                        std::cin >> id;
                        novoLeitor = new Professor(nome, id);
                        } else if (tipoLeitor == 3) {
                        int id;
                        std::cout << "Digite o ID do Leitor Comum: ";
                        std::cin >> id;
                        novoLeitor = new LeitorComum(nome, id);
                        } else if (tipoLeitor == 4) {
                        int id;
                        std::cout << "Digite o ID do Senior: ";
                        std::cin >> id;
                        novoLeitor = new Senior(nome, id);
                        }

                        if (novoLeitor) {
                        biblioteca.AddLeitor(novoLeitor);  // Agora passando o ponteiro do leitor
                        std::cout << "Leitor adicionado com sucesso!" << std::endl;
                        } else {
                        std::cout << "Tipo de leitor inválido!" << std::endl;
                        }
                        break;
                        }
                        case 4: {
                            //Listagem Leitores
                             biblioteca.ListagemLeitores();
                             break;
                        }
                        case 5: {
                            //Registar Emprestimo
                             biblioteca.registarEmprestimo();
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
                std::cout << "A encerrar o programa...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
} 
