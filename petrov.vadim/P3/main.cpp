#include <iostream>
#include <fstream>
#include <cstddef>

namespace petrov
{
  void create(std::istream & input, int * mtx, size_t rows, size_t cols);
} 

void create(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for(size_t i = 0; i < (rows*cols); ++i)
  {
    input >> mtx[i];
  }
}

int main(int argc, char ** argv)
{
  
  
}
