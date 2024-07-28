#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

class FormattedText
{
    std::string plain_text;
    bool *caps;
public:
    FormattedText(const std::string &plain_text) : plain_text(plain_text) 
    {
        caps = new bool[plain_text.length()];
        memset(caps, 0, plain_text.length());
    }

    ~FormattedText()
    {
        delete caps;
    }

    void capitalize(int start, int end)
    {
        for (int i = start; i <= end; i++)
        {
            caps[i] = true;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const FormattedText &text)
    {
        std::string s;
        for (int i = 0; i < text.plain_text.length(); i++)
        {
            char c = text.plain_text[i];
            s += (text.caps[i] ? std::toupper(c) : c);
        }

        return os << s;
    }
};

class BetterFormattedText
{
public:
    struct TextRange
    {
        int start, end;
        bool capitalize; //potential to add bold, italic, etc.

        [[nodiscard]] bool covers(int position) const
        {
            return position >= start && position <= end;
        }
    };

    TextRange& get_range(int start, int end)
    {
        formatting.emplace_back(TextRange{start, end});
        return *formatting.rbegin();
    }

    BetterFormattedText(std::string plain_text) : plain_text(std::move(plain_text)) {}

    friend std::ostream &operator<<(std::ostream &os, const BetterFormattedText &text)
    {
        std::string s;
        for (int i = 0; i < text.plain_text.length(); i++)
        {
            auto c = text.plain_text[i];
            for (const auto& rng : text.formatting)
            {
                if (rng.covers(i) && rng.capitalize)
                {
                    c = std::toupper(c);
                }
                s += c;
            }
        }

        return os << s;
    }
private:
    std::string plain_text;
    std::vector<TextRange> formatting;
};

int main()
{
    FormattedText ft{"This is a brave new world"};
    ft.capitalize(10, 15);

    std::cout << ft << '\n';

    BetterFormattedText bft{"This is a brave new world"};
    bft.get_range(10,15).capitalize = true;
    
    std::cout << bft << '\n';

    return 0;
}