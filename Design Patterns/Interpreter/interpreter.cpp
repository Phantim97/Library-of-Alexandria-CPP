#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

struct Token
{
	enum Type
	{
		integer, plus, minus, lparen, rparen
	};

    Type type {};
    std::string text;

    Token(Type type, const std::string& text) : type(type), text(text) {}

    friend std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << " " << token.text << " ";
        return os;
    }
};

std::vector<Token> lex(const std::string &input)
{
    std::vector<Token> result;

    for (int i = 0; i < input.size(); i++)
    {
        switch (input[i])
        {
        case '+':
            result.push_back(Token{Token::plus, "+"});
            break;
        case '-':
            result.push_back(Token{Token::minus, "-"});
            break;
        case '(':
            result.push_back(Token{Token::lparen, "("});
            break;
        case ')':
            result.push_back(Token{Token::rparen, ")"});
            break;
        default:
            std::ostringstream buffer;
            buffer << input[i];
            for (int j = i + 1; j < input.size(); j++)
            {
                if (isdigit(input[j]))
                {
                    buffer << input[j];
                    buffer << input[j];
                    i++;
                }
                else
                {
                    result.push_back(Token{Token::integer, buffer.str()});
                    break;
                }
            }
            break;
        }
    }

    return result;
}

struct Element
{
    virtual int eval() const  = 0;
};

struct Integer : Element
{
    int value = 0;
    Integer(int value) : value(value) {}

    [[nodiscard]] int eval() const override
    {
        return value;
    }
};

struct BinaryOperation : Element
{
    enum Type {addition, subtraction} type{};
    std::shared_ptr<Element> lhs, rhs;

    [[nodiscard]] int eval() const override
    {
		const int left = lhs->eval();
        const int right = rhs->eval();

        if (type == addition)
        {
            return left + right;
        }
        else
        {
            return left - right;
        }
    }
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens)
{
    std::unique_ptr<BinaryOperation> result = std::make_unique<BinaryOperation>();
    bool have_lhs = false;

    for (size_t i = 0; i < tokens.size(); i++)
    {
		const Token& token = tokens[i];

        switch (token.type)
        {
        case Token::integer:
        {
	        const int value = boost::lexical_cast<int>(token.text);
	        std::shared_ptr<Integer> integer = std::make_shared<Integer>(value);

	        if (!have_lhs)
	        {
		        result->lhs = integer;
		        have_lhs = true;
	        }
	        else
	        {
		        result->rhs = integer;
	        }
	        break;
        }
        case Token::plus:
            result->type = BinaryOperation::addition;
            break;
        case Token::minus:
            result->type = BinaryOperation::subtraction;
            break;
        case Token::lparen:
        {
	        int j = i;

	        for (int i = j; j < tokens.size(); j++)
	        {
		        if (tokens[j].type == Token::rparen)
		        {
			        break;
		        }
	        }

	        std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
	        std::shared_ptr<Element> element = parse(subexpression);

	        if (!have_lhs)
	        {
		        result->lhs = element;
		        have_lhs = true;
	        }
	        else
	        {
		        result->rhs = element;
	        }

	        i = j;
	        break;
        }
        default:
            break;
        }
    }
}

int main()
{
    std::string input{"(13-4)-(12+1)"};

    std::vector<Token> tokens = lex(input);

    for (const Token& t : tokens)
    {
        std::cout << t << " \n";
    }

    try
    {
        std::shared_ptr<Element> parsed = parse(tokens);
        std::cout << input << " = " << parsed->eval() << '\n';
    }
    catch(const std::exception e)
    {
        std::cout << e.what() << '\n';
    }
    return 0;
}