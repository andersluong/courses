#include "Node.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Number
Number::Number(double value)
{
  this->value = value;
}

double Number::evaluate()
{
  return this->value;
}

void Number::print_tree(ostream &os, int indent)
{
  os << setw(indent) << this->value << "\n";
}

Node* Number::clone()
{
  return new Number(this->value);
}

void Number::print(std::ostream& os) {
  os << this->value;
}

// Operator
Operator::Operator(Node *lhs, Node *rhs)
{
  this->left = lhs;
  this->right = rhs;
}

void Operator::print(std::ostream& os) {
  bool isMultiplication = dynamic_cast<Multiplication*>(this) != nullptr; // applies to division as well
  bool addLeftParanthesis = isMultiplication && dynamic_cast<Addition*>(this->left) != nullptr; // applies to subtraction as well
  bool addRightParanthesis = isMultiplication && dynamic_cast<Addition*>(this->right) != nullptr; // applies to subtraction as well

  //cout << "main: " << this->symbol() << ", isMulti: " << (dynamic_cast<Multiplication*>(this) != nullptr) << ", isAddition: " << (dynamic_cast<Addition*>(this->left) != nullptr) << endl;

  if (addLeftParanthesis) {
    os << "(";
  }
  this->left->print(os);
  if (addLeftParanthesis) {
    os << ")";
  }

  os << this->symbol();

  if (addRightParanthesis) {
    os << "(";
  }
  this->right->print(os);
  if (addRightParanthesis) {
    os << ")";
  }

}

void Operator::print_tree(std::ostream &os, int indent)
{
  this->left->print_tree(os, indent + 3);
  os << setw(indent) << " " << "/" << "\n";
  os << setw(indent) << this->symbol() << "\n";
  os << setw(indent) << " " << "\\" << "\n";
  this->right->print_tree(os, indent + 3);
}

// Addition
double Addition::evaluate()
{
  return this->left->evaluate() + this->right->evaluate();
}

Node* Addition::clone()
{
  return new Addition(*this);
}

char Addition::symbol(){
  return '+';
}

// Multiplication
double Multiplication::evaluate()
{
  return this->left->evaluate() * this->right->evaluate();
}

Node* Multiplication::clone()
{
  return new Multiplication(*this);
}

char Multiplication::symbol(){
  return '*';
}

// Subtraction
double Subtraction::evaluate()
{
  return this->left->evaluate() - this->right->evaluate();
}

Node* Subtraction::clone()
{
  return new Subtraction(*this);
}

char Subtraction::symbol(){
  return '-';
}

// Division
double Division::evaluate()
{
  return this->left->evaluate() / this->right->evaluate();
}

Node* Division::clone()
{
  return new Division(*this);
}

char Division::symbol(){
  return '/';
}