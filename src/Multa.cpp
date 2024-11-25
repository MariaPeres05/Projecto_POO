#include "Multa.h"
#include <iostream>



float Multa::calcularMulta(int diasAtrasado, float taxaBase, float desconto) {
    if (diasAtrasado <= 0) return 0.0f;
    float multa = diasAtrasado * taxaBase;
    return multa * (1.0f - desconto);
}

