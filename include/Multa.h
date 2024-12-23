#ifndef MULTA_H
#define MULTA_H

class Multa {
public:
   
     // Calcula a multa com base nos dias de atraso, taxa base e desconto
    static float calcularMulta(int diasAtrasado, float taxaBase, float desconto = 0.0f);
};

#endif // MULTA_H
