template <typename... Args>
void printer(Args &&...args)
{
    (std::cout << ... << args) << std::endl;
}

template <typename... Args>
void adds(Args &&...args)
{
    int tot = 0;
    tot = (... += args);
    std::cout << "Total : " << tot << std::endl;

    printer(args...);
}

template <typename... Args>
void adds_reverse(Args &&...args)
{
    int tot = 0;
    tot = (args += ...);
    std::cout << "Total : " << tot << std::endl;

    printer(args...);
}