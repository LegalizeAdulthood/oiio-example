#include <mandel/args.h>
#include <mandel/iterate.h>
#include <mandel/mandel.h>

#include <iostream>

int main(int argc, char *argv[])
{
    return iterate::main(mandel::args(argc, argv), std::cerr, mandel::render);
}
