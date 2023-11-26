#ifndef NODE_H_
#define NODE_H_

#include <ostream>

/*
  Implement the classes:
  - Node
  - Number
  - Operator
  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'
  - void print(std::ostream& os)
    + print the expression represented in 'this'
  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree
  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */

class Node {
  public:
    virtual ~Node() = default;
    virtual double evaluate() = 0;
    virtual void print_tree(std::ostream& os, int indentation) = 0;
    virtual Node* clone() = 0;

    virtual void print(std::ostream& os) = 0;
};

class Number : public Node {
  public:
    Number(double value);

    double evaluate() override;
    void print_tree(std::ostream& os, int indentation) override;
    Node* clone() override;

    void print(std::ostream& os) override;
  private:
    double value;
};

class Operator : public Node {
  public:
    Operator(Node* lhs, Node* rhs);

    void print_tree(std::ostream& os, int indentation) override;
    virtual char symbol() = 0;

    void print(std::ostream& os) override;
  protected:
    Node* left;
    Node* right;
};

class Addition : public Operator {
  public:
    using Operator::Operator;

    double evaluate() override;
    Node* clone() override;
  private:
    char symbol() override;
};

class Multiplication : public Operator {
  public:
    using Operator::Operator;

    double evaluate() override;
    Node* clone() override;
  private:
    char symbol() override;
};

class Subtraction : public Addition {
  public:
    using Addition::Addition;

    double evaluate() override;
    Node* clone() override;
  private:
    char symbol() override;
};

class Division : public Multiplication {
  public:
    using Multiplication::Multiplication;

    double evaluate() override;
    Node* clone() override;
  private:
    char symbol() override;
};

#endif