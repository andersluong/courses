#include "Expression.h"

#include <stdexcept>
#include <ostream>

/* Implement Expression here */

Expression::Expression(Node* root){
    this->root = root;
}; 

Expression::Expression(Expression const& other) {
    this->root = other.root;
};

Expression::Expression(Expression&& other) {
    this->root = other.root;
    other.root = nullptr;    
};

Expression::~Expression() {
    if (this->root == nullptr) {
        return;
    }
    delete this->root;
};

Expression& Expression::operator=(Expression const& rhs){
     Expression temp{rhs};
     *this = temp;
     return *this;
};

Expression& Expression::operator=(Expression&& rhs){
    std::swap(*this, rhs);
    return *this;
};

double Expression::evaluate() const {
    this->root->evaluate();
};

void Expression::print_tree(std::ostream& os, int indentation) const {
    this->root->print_tree(os, indentation);
};

/* For part B */
void Expression::print(std::ostream& os) const
{
    this->root->print(os);
}

/* For part C */
void Expression::expand()
{
    throw std::invalid_argument{"--expand is unimplemented"};
}
