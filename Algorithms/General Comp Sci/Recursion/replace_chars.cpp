void replace_chars(char* str, char c, char replacement)
{
    if (*str == '\0') //Base case
    {
        return;
    }

    if (*str == c)
    {
        *str = replacement;
    }

    replace_chars(str + 1, c, replacement); //Induction Hypothesis
}
