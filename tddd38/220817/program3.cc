#include <iostream>

/* Expected output:

!true = false
!(true && false) = true
(true || false) && false && (false || !false) = false

 */

int main()
{

    // Think carefully about the types here. You might have to modify
    // the testcases slightly to make it work.
    
    /* Expression */ expr1 { Negation { Literal { true } } };

    expr1->print(std::cout);
    std::cout << " = " << expr1->evaluate() << std::endl;
    
    /* Expression */ expr2 {
	Negation {
	    And { Literal { true }, Literal { false } }
	}
    };

    expr2->print(std::cout);
    std::cout << " = " << expr2->evaluate() << std::endl;
    
    /* Expression */ expr3 {
	And {
	    Or { Literal { true }, Literal { false } },
	    Literal { false },
	    Or { Literal { false }, Negation { Literal{false} } }
	}
    };

    expr3->print(std::cout);
    std::cout << " = " << expr3->evaluate() << std::endl;
    
}
