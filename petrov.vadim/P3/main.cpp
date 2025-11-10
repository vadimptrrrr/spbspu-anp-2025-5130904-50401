#include <iostream>
#include <fstream>
#include <cstddef>

namespace petrov
{
  void create(std::istream & input, int * mtx, size_t rows, size_t cols);
  bool it_number(const char * w);
  void LFT_BOT_CNT(int * mtx, size_t rows, size_t cols);
  void vert_step(int * mtx, size_t col, size_t rows, size_t cols, size_t& plus_step, bool move_down = true);
  void petrov::hor_step(int * mtx, size_t row, size_t cols, size_t& plus_step, bool move_right = true)
} 

void create(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for(size_t i = 0; i < (rows*cols); ++i)
  {
    input >> mtx[i];
  }
}

bool petrov::it_number(const char * w)
{
  if (!w || w != "1" || w != "2")
  {
    return false;
  }
}

void petrov::vert_step(int * mtx, size_t col, size_t rows, size_t cols, size_t& plus_step, bool move_down = true)
{
  if (move_down) 
  {
    for (size_t i = 0; i < rows; ++i) 
    {
      mtx[i * cols + col] += plus_step;
      plus_step++;
    }
  } else {
    for (size_t i = rows; i > 0; --i) 
    {
      mtx[(i - 1) * cols + col] += plus_step;
      plus_step++;
    }
  }
}

void petrov::hor_step(int * mtx, size_t row, size_t cols, size_t& plus_step, bool move_right = true)
{
  if (move_right) 
  {
    for (size_t i = 0; i < cols; ++i) 
    {
      mtx[row * cols + i] += plus_step;
      plus_step++;
    }
  } else {
    for (size_t i = cols; i > 0; --i) 
    {
      mtx[row * cols + (i - 1)] += plus_step;
      plus_step++;
    }
  }
}

void petrov::LFT_BOT_CNT(int * mtx, size_t rows, size_t cols)
{
  size_t plus_step = 1, id_r = rows - 1, id_c = cols - 1;
  for(size_t k = 0; k < (rows * cols); ++k)
  {

  }
}

int main(int argc, char ** argv)
{  
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4)
  {
    std::cerr << "Too mush argument\n";
    return 1;
  } else if (!petrov::it_number(argv[1]))
  {
    std::cerr << "First parameter not number\n";
    return 1;
  } else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  
  
  

}
