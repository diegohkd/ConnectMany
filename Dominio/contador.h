#ifndef CONTADOR_H
#define CONTADOR_H


class Contador{
public:
    // inicialização
    Contador(int contagem);

    // getters e setters
    int getContagem() const;
    void setContagem(int value);

private:
    int contagem;   // valor atual do contador
};

#endif // CONTADOR_H
