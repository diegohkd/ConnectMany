#ifndef PECA_H
#define PECA_H

#include <QColor>

class Peca{
public:
    // inicialização
    Peca(QColor cor);

    // setter e getter
    QColor getCor() const;
    void setCor(const QColor &value);

private:
    QColor cor; //  cor da peça
};

#endif // PECA_H
