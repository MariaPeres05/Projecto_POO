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


void exibirMenuLeitor() {
    std::cout << "\n=========== Menu do Leitor ===========" << std::endl;
    std::cout << "1. Verificar Livros Disponíveis" << std::endl;
    std::cout << "2. Verificar Multas Pendentes" << std::endl;
    std::cout << "3. Verificar Empréstimos e Reservas" << std::endl;
    std::cout << "4. Reservar Livro" << std::endl;
    std::cout << "5. Devolver Livro" << std::endl;
    std::cout << "6. Prolongar Empréstimo" << std::endl; 
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
    std::cout << "6. Relatório de Empréstimos por Tipo de Livro" << std::endl;
    std::cout << "7. Sistema de Reservas" << std::endl;
    std::cout << "8. Gerar Relatório de Multas" << std::endl;
    std::cout << "9. Prolongar Empréstimos" << std::endl; 
    std::cout << "0. Voltar ao menu inicial" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main() {
    std::setlocale(LC_ALL, "pt_PT.UTF-8");
    Biblioteca biblioteca;

    // Carregar dados dos arquivos
    biblioteca.LoadLivrosFromFile("livros.txt");
    biblioteca.LoadLeitoresFromFile("leitores.txt");
    biblioteca.LoadEmprestimosFromFile("emprestimos.txt");
    biblioteca.LoadReservasFromFile("reservas.txt");
    //biblioteca.SaveReservasToFile("reservas.txt");

    int opcao = -1;

    do {
        exibirMenuInicial();
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1: { // Menu do Bibliotecário
                int opcaoBibliotecario = -1;
                do {
                    exibirMenuBibliotecario();
                    std::cin >> opcaoBibliotecario;
                    std::cin.ignore();

                    switch (opcaoBibliotecario) {
                        case 1: { // Adicionar Livro
                            std::cout << "Escolha o tipo de livro:\n1. Ficção\n2. Científico\n3. Educativo\n4. Revista\n5. Jornal\n";
                            int tipoLivro;
                            std::cin >> tipoLivro;
                            std::cin.ignore();

                            std::string titulo, autor, extra;
                            Livro* novoLivro = nullptr;

                            std::cout << "Digite o título: ";
                            std::getline(std::cin, titulo);
                            std::cout << "Digite o autor: ";
                            std::getline(std::cin, autor);

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

                            biblioteca.AdicionarLivro(novoLivro);
                            break;
                        }
                        case 2: { // Listar Livros por Categoria
                            int categoriaEscolhida;
                            std::cout << "Escolha a categoria para listar os livros:\n";
                            std::cout << "1. Ficção\n2. Científico\n3. Educativo\n4. Jornal\n5. Revista\n6. Voltar ao menu principal\n";
                            std::cout << "Opção: ";
                            std::cin >> categoriaEscolhida;

                            std::string categoria;
                            switch (categoriaEscolhida) {
                                case 1:
                                    categoria = "Ficção";
                                    break;
                                case 2:
                                    categoria = "Científico";
                                    break;
                                case 3:
                                    categoria = "Educativo";
                                    break;
                                case 4:
                                    categoria = "Jornal";
                                    break;
                                case 5:
                                    categoria = "Revista";
                                    break;
                                case 6:
                                    break; // Volta ao menu principal
                                default:
                                    std::cout << "Opção inválida. Tente novamente.\n";
                                    break;
                            }

                        if (categoriaEscolhida >= 1 && categoriaEscolhida <= 5) {
                            biblioteca.ListagemLivrosPorCategoria(categoria);
                        }
                        break;
                    }
                        case 3: { // Adicionar Leitor
                            std::cout << "Escolha o tipo de leitor:\n1. Estudante\n2. Professor\n3. Leitor Comum\n4. Senior\n";
                            int tipoLeitor;
                            std::cin >> tipoLeitor;
                            std::cin.ignore();

                            std::string nome;
                            int id;

                            std::cout << "Digite o nome do leitor: ";
                            std::getline(std::cin, nome);
                            std::cout << "Digite o ID do leitor: ";
                            std::cin >> id;

                            Pessoa* novoLeitor = nullptr;
                            if (tipoLeitor == 1) {
                                novoLeitor = new Estudante(nome, id);
                            } else if (tipoLeitor == 2) {
                                novoLeitor = new Professor(nome, id);
                            } else if (tipoLeitor == 3) {
                                novoLeitor = new LeitorComum(nome, id);
                            } else if (tipoLeitor == 4) {
                                novoLeitor = new Senior(nome, id);
                            }

                            if (novoLeitor) {
                                biblioteca.AddLeitor(novoLeitor);
                                std::cout << "Leitor adicionado com sucesso!\n";
                            } else {
                                std::cerr << "Erro ao adicionar leitor.\n";
                            }
                            break;
                        }
                        case 4: 
                            biblioteca.ListagemLeitores();
                            break; 
                        case 5: 
                            //Registar Emprestimo
                            biblioteca.registarEmprestimo();
                            break; 
                        case 6: {  
                            // Relatório de Empréstimos por Tipo de Livro
                            std::cout << "A gerar o relatório de empréstimos por tipo de livro...\n";
                            biblioteca.RelatorioEmprestimosPorTipoLivro();
                            break;
                        }
                        case 7: { // Sistema de Reservas
                            std::cout << "Livros Reservados:\n";
                            bool encontrouReserva = false;
    
                            // Verificar reservas
                            for (const auto& reserva : biblioteca.getReservas()) {
                            std::cout << "Livro: " << reserva.first->getTitulo() << " - Reservado por:\n";
                            int i = 1;
                            for (const auto* leitor : reserva.second) {
                            std::cout << i++ << ". " << leitor->getNome() << "\n";
                            encontrouReserva = true;
                            }

                            }
                            if (!encontrouReserva) {
                            std::cout << "Nenhuma reserva registrada.\n";
                            }
                            break;
                        }
                        case 8: { // Gerar Relatório de Multas
                            std::cout << "Relatório de Multas:\n";
                            double totalMultas = 0.0;
                            float taxaBase = 0.5f;  // Exemplo: 0.5€ por dia de atraso
                            float desconto = 0.1f;  // Exemplo: 10% de desconto para professores

                            // Verificar os empréstimos atrasados e calcular as multas
                            for (auto& emprestimo : biblioteca.getEmprestimos()) {
                            if (emprestimo->estaAtrasado()) {
                            float multa = emprestimo->calcularMulta(taxaBase, desconto);  // Calcula a multa
                            totalMultas += multa;
                            std::cout << "Leitor: " << emprestimo->getLeitor()->getNome() << " - Livro: "
                            << emprestimo->getLivro()->getTitulo() << " - Multa: " << multa << "€\n";
                             }
                            }
                            std::cout << "Total de multas: " << totalMultas << "€\n";
                            break;
                        }
                       
                     case 9: {  // Prolongar Empréstimos
    int i = 1;
    std::vector<Emprestimo*> emprestimosDisponiveis;

    // Listar empréstimos que podem ser prolongados
    std::cout << "Empréstimos disponíveis para prolongar:\n";
    for (auto& emprestimo : biblioteca.getEmprestimos()) {
        // Verifica se o empréstimo está atrasado e se o leitor pode prolongar
        if (emprestimo->estaAtrasado() && emprestimo->podeProlongar()) {
            std::cout << i++ << ". " << emprestimo->getLivro()->getTitulo() << " - "
                      << emprestimo->getLeitor()->getNome() << " (Data de devolução: "
                      << emprestimo->getDataDevolucao() << ")\n";
            emprestimosDisponiveis.push_back(emprestimo);  // Adiciona à lista de empréstimos disponíveis para prolongamento
        }
    }

    if (emprestimosDisponiveis.empty()) {
        std::cout << "Nenhum empréstimo disponível para prolongar.\n";
        break;
    }

    int escolhaEmprestimo;
    std::cout << "Escolha um empréstimo para prolongar (digite o número): ";
    std::cin >> escolhaEmprestimo;

    if (escolhaEmprestimo < 1 || escolhaEmprestimo > emprestimosDisponiveis.size()) {
        std::cout << "Escolha inválida.\n";
        break;
    }

    // Prolongar o empréstimo
    Emprestimo* emprestimoSelecionado = emprestimosDisponiveis[escolhaEmprestimo - 1];
    emprestimoSelecionado->prolongar();
    std::cout << "O empréstimo foi prolongado com sucesso. Nova data de devolução: "
              << emprestimoSelecionado->getDataDevolucao() << "\n";

    // Salvar os empréstimos atualizados no arquivo
    if (!biblioteca.SaveEmprestimosToFile("emprestimos.txt")) {
        std::cerr << "Erro ao salvar os empréstimos no arquivo.\n";
    }

    break;
}

                        case 0:
                            std::cout << "A voltar ao menu inicial...\n";
                            break;
                        default:
                            std::cout << "Opção inválida! Tente novamente.\n";
                    }
                } while (opcaoBibliotecario != 0);
                break;
            }
            case 2: { // Menu do Leitor
                int tipoLeitor = -1;
                do {
                    exibirSubmenuLeitor();
                    std::cin >> tipoLeitor;
                    std::cin.ignore();

                    if (tipoLeitor == 0) {
                        std::cout << "A voltar ao menu inicial...\n";
                        break;
                    }

                    int opcaoLeitor = -1;
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
                            case 3: { // Verificar Empréstimos e Reservas
                                int idLeitor;
                                std::cout << "Digite o ID do leitor: ";
                                std::cin >> idLeitor;

                                // Encontrar o leitor pelo ID
                                Pessoa* leitor = nullptr;
                                for (auto l : biblioteca.getLeitores()) {
                                if (l->getId() == idLeitor) {
                                leitor = l;
                                break;
                                }
                                }

                                if (!leitor) {
                                std::cout << "Leitor não encontrado.\n";
                                break;
                                }

                                // Listar empréstimos do leitor
                                std::cout << "Empréstimos do leitor " << leitor->getNome() << ":\n";
                                bool temEmprestimos = false;
                                for (auto& emprestimo : biblioteca.getEmprestimos()) {
                                if (emprestimo->getLeitor() == leitor) {
                                std::cout << "- " << emprestimo->getLivro()->getTitulo() << "\n";
                                temEmprestimos = true;
                                }
                                }
                                if (!temEmprestimos) {
                                std::cout << "Nenhum empréstimo ativo.\n";
                                }

                                // Listar reservas do leitor
                                std::cout << "\nReservas do leitor " << leitor->getNome() << ":\n";
                                bool temReservas = false;
                                for (const auto& reserva : biblioteca.getReservas()) {
                                    for (auto* pessoaReservada : reserva.second) {
                                        if (pessoaReservada == leitor) {
                                        std::cout << "- " << reserva.first->getTitulo() << "\n";
                                        temReservas = true;
                                break;
                                }
                                }
                                }
                                if (!temReservas) {
                                std::cout << "Nenhuma reserva ativa.\n";
                                }

                                break;
                            }

                            case 4: { // Reservar Livro
                                Pessoa* leitor = nullptr;
                                std::vector<Pessoa*> leitoresFiltrados;

                                // Filtrar os leitores pelo tipo
                                std::cout << "Escolha o leitor:\n";
                                int i = 1;
                                for (auto& l : biblioteca.getLeitores()) {
                                    if ((tipoLeitor == 1 && l->tipo() == "Estudante") ||
                                (tipoLeitor == 2 && l->tipo() == "Professor") ||
                                (tipoLeitor == 3 && l->tipo() == "Leitor Comum") ||
                                (tipoLeitor == 4 && l->tipo() == "Senior")) {
                                leitoresFiltrados.push_back(l);
                                std::cout << i++ << ". " << l->getNome() << "\n";
                                    }
                                }

                                    if (leitoresFiltrados.empty()) {
                                    std::cout << "Nenhum leitor disponível deste tipo.\n";
                                    break;
                                    }

                                int leitorEscolhido;
                                std::cout << "Escolha um leitor: ";
                                std::cin >> leitorEscolhido;

                                if (leitorEscolhido < 1 || leitorEscolhido > leitoresFiltrados.size()) {
                                std::cout << "Escolha inválida.\n";
                                break;
                                } else {
                                leitor = leitoresFiltrados[leitorEscolhido - 1];
                                  }

                                Livro* livroSelecionado = nullptr;
                                std::vector<Livro*> livrosEmprestadosParaReserva;

                                // Listar livros não disponíveis para reserva (livros emprestados)
                                std::cout << "Livros disponíveis para reserva:\n";
                                i = 1;
                                for (auto& livro : biblioteca.getLivros()) {
                                // Verifica se o livro não está disponível (ou seja, emprestado)
                                    if (!livro->estaDisponivel()) {
                                livrosEmprestadosParaReserva.push_back(livro);
                                std::cout << i++ << ". " << livro->getTitulo() << " - " << livro->getAutor() << "\n";
                                    }
                                }

                                    if (livrosEmprestadosParaReserva.empty()) {
                                    std::cout << "Nenhum livro emprestado disponível para reserva.\n";
                                    break;
                                    }

                                int livroEscolhido;
                                std::cout << "Escolha o número do livro: ";
                                std::cin >> livroEscolhido;

                                if (livroEscolhido < 1 || livroEscolhido > livrosEmprestadosParaReserva.size()) {
                                std::cout << "Escolha inválida.\n";
                                break;
                                }

                                livroSelecionado = livrosEmprestadosParaReserva[livroEscolhido - 1];
                                biblioteca.RegistarReserva(livroSelecionado, leitor);
                                std::cout << "Livro reservado com sucesso!\n";

                                break;
                            }

                            case 5: { // Devolver Livro
 
                            int idLeitor;
                            std::cout << "Digite o ID do leitor: ";
                            std::cin >> idLeitor;

                            // Encontrar o leitor pelo ID
                            Pessoa* leitor = nullptr;
                            for (auto l : biblioteca.getLeitores()) {
                            if (l->getId() == idLeitor) {
                            leitor = l;
                            break;
                            }
                            }

                            if (!leitor) {
                            std::cout << "Leitor não encontrado.\n";
                            break;
                            }

                            // Mostrar livros emprestados pelo leitor
                            std::vector<Emprestimo*> emprestimosLeitor;
                            std::cout << "Livros emprestados pelo leitor " << leitor->getNome() << ":\n";
                            int i = 1;
                            for (auto& emprestimo : biblioteca.getEmprestimos()) {
                            if (emprestimo->getLeitor() == leitor) {
                            emprestimosLeitor.push_back(emprestimo);
                            std::cout << i++ << ". " << emprestimo->getLivro()->getTitulo() << "\n";
                            }
                            }

                            if (emprestimosLeitor.empty()) {
                            std::cout << "Nenhum livro emprestado.\n";
                            break;
                            }

                            // Selecionar o livro para devolver
                            int escolha;
                            std::cout << "Escolha o livro a devolver: ";
                            std::cin >> escolha;

                            if (escolha < 1 || escolha > emprestimosLeitor.size()) {
                            std::cout << "Escolha inválida.\n";
                            break;
                            }

                            Emprestimo* emprestimoSelecionado = emprestimosLeitor[escolha - 1];
                            biblioteca.devolverLivro(emprestimoSelecionado->getLeitor());

                            std::cout << "Livro devolvido com sucesso.\n";
                            break;
                            }
                            case 6: { // Prolongar Empréstimo
                                  Pessoa* leitor = nullptr;
                                  int idLeitor;
                                  std::cout << "Digite o ID do leitor: ";
                                  std::cin >> idLeitor;

                                  for (auto l : biblioteca.getLeitores()) {
                                  if (l->getId() == idLeitor) {
                                  leitor = l;
                                  break;
                                  }
                                  }

                                  if (leitor && leitor->podeProlongar()) {
                                  biblioteca.ProlongarEmprestimos(); 
                                  std::cout << "Prorrogação realizada com sucesso!\n";
                                  } else {
                                  std::cout << "Leitor não encontrado ou não pode prorrogar empréstimos.\n";
                                  }
                                  break;
                                }
                            case 0:
                                std::cout << "A voltar ao menu anterior...\n";
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