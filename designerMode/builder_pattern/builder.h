#ifndef BUILDER_H
#define BUILDER_H

#include <QString>
#include <QVector>

class Product
{
public:
    QVector<QString> _productItem;
};

class Builder
{
public:
    virtual void setProductA() const = 0;
    virtual void setProductB() const = 0;
    virtual void setProductC() const = 0;
};

class BuildeCreate:public Builder
{
private:
    Product *product;
public:
    BuildeCreate(){this->reset();}
    ~BuildeCreate(){delete product;}
    void reset(){this->product = new Product();}
    Product* getPrduct(){Product *result = this->product;this->reset();return result;}
    void setProductA() const override{this->product->_productItem.append(QString("A步骤"));}
    void setProductB() const override{this->product->_productItem.append(QString("B步骤"));}
    void setProductC() const override{this->product->_productItem.append(QString("C步骤"));}
};

class manager
{
public:
    Builder *builder;

    manager() = default;
    void setCreater(Builder* builder){this->builder = builder;}

    void createMin() const
    {
        this->builder->setProductA();
    }

    void createMax() const
    {
        this->builder->setProductA();
        this->builder->setProductB();
        this->builder->setProductC();
    }

};

#endif // BUILDER_H
