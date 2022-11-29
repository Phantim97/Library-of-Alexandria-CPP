int str_to_int(char* str)
{
    if (*str == '\0') //Base case
    {
        return 0;
    }

    int last_digit = *str - '0';
    int small_number = str_to_int(str + 1); //Induction Hypothesis
    return small_number * 10 + last_digit; //Induction Step
}
