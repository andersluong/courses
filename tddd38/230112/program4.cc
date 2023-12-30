#include <iostream>
#include <string>
#include <vector>

class Base_Parser {
public:
  virtual ~Base_Parser() = default;
  virtual bool parse(std::string::const_iterator &begin,
                     const std::string::const_iterator end) = 0;
  virtual Base_Parser *clone() = 0;
};

class Match : public Base_Parser {
public:
  Match(std::string m) : match{m} {};
  bool parse(std::string::const_iterator &begin,
             const std::string::const_iterator end) override {
    for (unsigned i = 0; i < match.size(); i++) {
      std::string::const_iterator currentIt = begin + i;
      if (currentIt == end || match[i] != *currentIt) {
        return false;
      }
    }
    begin = begin + match.size();
    return true;
  }

  Base_Parser *clone() override { return new Match{match}; }

private:
  std::string match;
};

class Alternate : public Base_Parser {
public:
  Alternate(std::vector<Base_Parser *> p) : parsers(p){};
  ~Alternate() {
    for (auto parser : parsers) {
      delete parser;
    }
  }
  bool parse(std::string::const_iterator &begin,
             const std::string::const_iterator end) override {
    for (auto parser : parsers) {
      if (parser->parse(begin, end)) {
        return true;
      }
    }
    return false;
  }

  Base_Parser *clone() override {
    std::vector<Base_Parser *> temp;
    for (auto parser : parsers) {
      temp.push_back(parser->clone());
    }
    return new Alternate{temp};
  };

protected:
  std::vector<Base_Parser *> parsers;
};

class Sequence : public Alternate {
public:
  Sequence(std::vector<Base_Parser *> p) : Alternate{p} {};

  bool parse(std::string::const_iterator &begin,
             const std::string::const_iterator end) override {
    std::string::const_iterator old = begin;
    for (auto parser : parsers) {
      if (!parser->parse(begin, end)) {
        begin = old;
        return false;
      }
    }
    return true;
  }

  Base_Parser *clone() override {
    std::vector<Base_Parser *> temp;
    for (auto parser : parsers) {
      temp.push_back(parser->clone());
    }
    return new Sequence{temp};
  };

private:
};

int main() {

  Alternate variable_parser{{new Match{"x"}, new Match{"y"}}};

  Alternate operator_parser{{new Match{"+"}, new Match{"-"}}};

  Sequence basic_parser{{variable_parser.clone(), operator_parser.clone(),
                         variable_parser.clone()}};

  Sequence parenthesis_parser{
      {new Match{"("}, basic_parser.clone(), new Match{")"}}};

  Sequence single_parenthesis_parser{
      {new Match{"("}, variable_parser.clone(), new Match{")"}}};

  Alternate expression_parser{{parenthesis_parser.clone(),
                               single_parenthesis_parser.clone(),
                               basic_parser.clone()}};

  std::string line;
  while (std::getline(std::cin, line)) {
    std::string::const_iterator current{std::cbegin(line)};
    if (expression_parser.parse(current, std::cend(line))) {
      std::cout << "Matched!" << std::endl;
    } else {
      std::cout << "Didn't match!" << std::endl;
    }
  }
}
