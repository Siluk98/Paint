[[noreturn]] void callDomainError(int index, int size,std::string file, /*std::string fname,*/ int line)
{
    std::string err = "Index(";
    err += index;
    err += ") out of container range(";
    err += size;
    err += ") in file:";
    err += file;
    //err += " Function:";
    //err += fname;
    err += " Line:";
    err += line;
    throw std::domain_error(err);
}
