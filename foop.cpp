#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void die(const std::string& message) {
#ifndef BE_MORE_FUNCTIONAL
    std::cerr << message << '\n';
#endif
    std::exit(0);
}

struct expression {
    using ptr = const std::shared_ptr<const expression>;
    virtual int eval() const = 0;
    virtual ~expression() {}
};

//In C++, "operator" is a keyword...sigh
template <typename O>
struct operation: expression {
    static expression::ptr make(expression::ptr lhs, expression::ptr rhs) {
        return std::make_shared<operation<O>>(lhs, rhs);
    }

    operation(expression::ptr lhs, expression::ptr rhs): _lhs{lhs}, _rhs{rhs} {}
    int eval() const override { return O{}(_lhs->eval(), _rhs->eval()); }

private:
    expression::ptr _lhs;
    expression::ptr _rhs;
};

using plus = operation<std::plus<int>>;
using minus = operation<std::minus<int>>;
using times = operation<std::multiplies<int>>;
using divided_by = operation<std::divides<int>>;

struct integer: expression {
    static expression::ptr make(const int i) {
        return std::make_shared<integer>(i);
    }

    explicit integer(const int i): _i{i} {}
    int eval() const override { return _i; }

private:
    const int _i;
};

struct stack_node {
    using ptr = const std::shared_ptr<const stack_node>;

    static ptr make(expression::ptr e, ptr next) {
        return std::make_shared<stack_node>(e, next);
    }

    stack_node(expression::ptr e, ptr n): _expression{e}, _next{n} {}

    expression::ptr first() const {
        if (not _expression) die("NULL expression!");
        return _expression;
    }

    expression::ptr second() const {
        if (not _next) die("Stack underflow!");
        if (not _next->_expression) die("NULL expression!");
        return _next->_expression;
    }

    stack_node::ptr next() const {
        if (not _next) die("Stack underflow!");
        return _next;
    }

    stack_node::ptr nextnext() const {
        //When popping two nodes, it's OK to return nullptr
        return next()->_next;
    }

private:
    expression::ptr _expression;
    ptr             _next;
};

expression::ptr parse(
        const std::vector<std::string>& args,
        const int                       arg_index,
        const stack_node::ptr           top)
{
    if (arg_index >= args.size()) {
        return top->first();
    }

    if ('+' == args[arg_index][0]) {
        return parse(args, arg_index + 1,
                stack_node::make(
                    plus::make(top->second(), top->first()),
                    top->nextnext()));
    } else if (('-' == args[arg_index][0]) and (1 == args[arg_index].size())) {
        return parse(args, arg_index + 1,
                stack_node::make(
                    minus::make(top->second(), top->first()),
                    top->nextnext()));
    } else if (('x' == args[arg_index][0]) or ('*' == args[arg_index][0])) {
        return parse(args, arg_index + 1,
                stack_node::make(
                    times::make(top->second(), top->first()),
                    top->nextnext()));
    } else if ('/' == args[arg_index][0]) {
        return parse(args, arg_index + 1,
                stack_node::make(
                    divided_by::make(top->second(), top->first()),
                    top->nextnext()));
    } else {
        return parse(args, arg_index + 1,
                stack_node::make(
                    integer::make(std::stoi(args[arg_index])), top));
    }
}

int main(const int argc, const char** argv) {
    try {
        const std::vector<std::string> args(argv + 1, argv + argc);

        if (0 == args.size()) die("Need arguments!");

        auto ep = parse(args, 0, nullptr);

        auto result = ep->eval();

#ifndef BE_MORE_FUNCTIONAL
        std::cout << result << '\n';
#endif

        return result;
    } catch (const std::exception& e) {
        die(e.what());
    } catch (...) {
        die("Exception!");
    }
}

