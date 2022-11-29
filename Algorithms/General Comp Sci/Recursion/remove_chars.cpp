void remove_conescutive_duplicates(char* str)
{
    if (*str == '\0') //Base case
    {
        return;
    }

    if (*str == *(str + 1))
    {
        int i = 0;
        while (*(str + i) != '\0')
        {
            *(str + i) = *(str + i + 1);
            ++i;
        }
    }

    remove_conescutive_duplicates(str + 1); //Induction Hypothesis
}
