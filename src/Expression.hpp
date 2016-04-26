// Data structures representing the AST for an optimization problem

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>

#include "Utils.hpp"

class ConstAttributes {
 public:
  DenseMatrix data;
};

class VarAttributes {
 public:
  int id;
};

// Expression trees
class Expression {
 public:
  enum Type {
    // Linear functions
    ADD,
    HSTACK,
    INDEX,
    MUL,
    NEG,
    RESHAPE,
    SUM,
    VSTACK,

    // Nonlinear functions
    ABS,
    P_NORM,
    QUAD_OVER_LIN,

    // Constraints
    EQ,
    LEQ,
    SOC,

    // Leaf nodes
    CONST,
    VAR,
  };

  Type type() const { return data_->type; }
  const std::vector<Expression>& args() const { return data_->args; }
  const Expression& arg(int i) const { return data_->args[i]; }

  template<typename T>
  const T& attr() const;

  Expression() {}
  Expression(Type type, std::vector<Expression> args);

 private:
  struct Data {
    Data(Type type, std::vector<Expression> args)
        : type(type), args(std::move(args)) {}
    Type type;
    std::vector<Expression> args;
  };

  std::shared_ptr<const Data> data_;
};

class Size {
 public:
  std::vector<int> dims;
};

class Problem {
 public:
  enum Sense {
    MAXIMIZE,
    MINIMIZE,
  };

  Problem() {}
  Problem(
      Sense sense,
      Expression objective,
      std::vector<Expression> constraints)
      : sense(sense),
        objective(objective),
        constraints(constraints) {}

  Sense sense;
  Expression objective;
  std::vector<Expression> constraints;
};

#endif  // EXPRESSION_H
