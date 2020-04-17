#include "lexer.hpp"

Lexer::Lexer(std::string path)
{
    std::ifstream file(path, std::ifstream::binary);
    if (!file)
    {
		std::cout << "File cannot be loaded" << std::endl;
		err = true;
    }
    else
    {
        file.seekg(0, file.end);
        length = file.tellg();
        file.seekg(0, file.beg);
        buffer = new char[length];
        file.read(buffer, length);
        if (!file)
        {
            err = true;
        }
        else
        {
            err = create_lexem();
        }
        file.close();
    }
}

Lexer::~Lexer()
{
    delete lexem;
    if (buffer)
    {
        delete buffer;
    }
}

bool Lexer::create_lexem()
{
    int state = START;
    for (int i = 0; i < length; ++i)
    {
        if (state == HASHTAG)
        {
            if (buffer[i] == '\n')
            {
                lexem->push_back(ENDLINE);
                state = ENDLINE;
            }
            else if (buffer[i] == '#')
            {
                lexem->push_back(SPACE);
                state = SPACE;
            }
            else
            {
                lexem->push_back(HASHTAG);
            }
        }
        else
        {
            if (buffer[i] == '#')
            {
                lexem->push_back(HASHTAG);
                state = HASHTAG;
            }
            else if (isdigit(buffer[i]))
            {
                lexem->push_back(NUMBER);
                state = NUMBER;
            }
            else if (buffer[i] == '\n')
            {
                lexem->push_back(ENDLINE);
                state = ENDLINE;
            }
            else if (isspace(buffer[i]))
            {
                lexem->push_back(SPACE);
                state = SPACE;
            }
            else
            {
                return (true);
            }
        }
    }
    return (false);
}
