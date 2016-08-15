#ifndef NODO_H
#define NODO_H

#include "peca.h"
#include "contador.h"

#include <QPointF>

class Nodo{
public:
    // inicialização
    Nodo();

    // destrutor
    ~Nodo();

    void removePeca();

    // getters and setters
    Peca *getPeca();
    void setPeca(Peca *value);
    Nodo *getVizinho_esq() const;
    void setVizinho_esq(Nodo *value);
    Nodo *getVizinho_inferior_esq() const;
    void setVizinho_inferior_esq(Nodo *value);
    Nodo *getVizinho_inferior() const;
    void setVizinho_inferior(Nodo *value);
    Nodo *getVizinho_inferior_dir() const;
    void setVizinho_inferior_dir(Nodo *value);
    Nodo *getVizinho_dir() const;
    void setVizinho_dir(Nodo *value);
    Nodo *getVizinho_superior_dir() const;
    void setVizinho_superior_dir(Nodo *value);
    Nodo *getVizinho_superior() const;
    void setVizinho_superior(Nodo *value);
    Nodo *getVizinho_superior_esq() const;
    void setVizinho_superior_esq(Nodo *value);
    Contador *getAlinhados_horizontal() const;
    void setAlinhados_horizontal(Contador *value);
    Contador *getAlinhados_vertical() const;
    void setAlinhados_vertical(Contador *value);
    Contador *getAlinhados_diagonal() const;
    void setAlinhados_diagonal(Contador *value);
    Contador *getAlinhados_diagonal_invertida() const;
    void setAlinhados_diagonal_invertida(Contador *value);

private:      
    Peca * peca;                            // peça a ser inserida no nodo
    Nodo * vizinho_esq;                     //
    Nodo * vizinho_inferior_esq;            //
    Nodo * vizinho_inferior;                //
    Nodo * vizinho_inferior_dir;            //     < vizinhos dos 8 lados >
    Nodo * vizinho_dir;                     //
    Nodo * vizinho_superior_dir;            //
    Nodo * vizinho_superior;                //
    Nodo * vizinho_superior_esq;            //
    Contador *alinhados_horizontal;         // contagem de peças alinhadas na horizontal
    Contador *alinhados_vertical;           // contagem de peças alinhadas na vertical
    Contador *alinhados_diagonal;           // contagem de peças alinhadas na diagonal
    Contador *alinhados_diagonal_invertida; // contagem de peças alinhadas na diagonal invertida
};

#endif // NODO_H
