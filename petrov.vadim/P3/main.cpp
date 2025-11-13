#include <iostream>
#include <fstream>
#include <cstddef>

namespace petrov
{
  void create(std::istream & input, int * mtx, size_t rows, size_t cols);
  bool it_number(const char * w);
  void LFT_BOT_CNT(std::ostream & output, int * mtx, size_t rows, size_t cols);
  void vert_step(int * mtx, size_t col, size_t rows, size_t cols, size_t& plus_step, bool move_down = true);
  void hor_step(int * mtx, size_t row, size_t cols, size_t& plus_step, bool move_right = true);
  void FLL_INC_WAV(std::ostream & output, int * mtx, size_t rows, size_t cols);
  void vert_step_2(int * mtx, size_t col, size_t rows, size_t cols, size_t plus_step);
  void hor_step_2(int * mtx, size_t row, size_t cols, size_t plus_step);
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
  if (!w || *w == '\0')
  {
    return false;
  }
  for (size_t i = 0; w[i] != '\0'; ++i)
  {
    if (w[i] < '0' || w[i] > '9')
    {
      return false;
    }
  }
  return true;
}

void petrov::vert_step(int * mtx, size_t col, size_t rows, size_t cols, size_t& plus_step, bool move_down)
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

void petrov::hor_step(int * mtx, size_t row, size_t cols, size_t& plus_step, bool move_right)
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

void petrov::LFT_BOT_CNT(std::ostream & output, int * mtx, size_t rows, size_t cols)
{
  size_t current_step = 1;
  size_t top = 0, bottom = rows - 1, right = cols - 1, left = 0;

  while (top < bottom + 1 && left < right + 1)
  {
    petrov::hor_step(mtx, bottom, cols, current_step, true);
    bottom--;

    petrov::vert_step(mtx, right, rows, cols, current_step, false);
    right--;

    if (top < bottom + 1)
    {
      petrov::hor_step(mtx, top, cols, current_step, false);
      top++;
    }

    if (left < right + 1)
    {
      petrov::vert_step(mtx, left, rows, cols, current_step, true);
      left++;
    }
  }
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i)
  {
    output << " " << mtx[i];
  }
  output << "\n";
}

void petrov::vert_step_2(int * mtx, size_t col, size_t rows, size_t cols, size_t plus_step)
{
  for (size_t i = 0; i < rows; ++i)
  {
    mtx[i * cols + col] += plus_step;
  }
}

void petrov::hor_step_2(int * mtx, size_t row, size_t cols, size_t plus_step)
{
  for (size_t i = 0; i < cols; ++i)
  {
    mtx[row * cols + i] += plus_step;
  }
}

void petrov::FLL_INC_WAV(std::ostream & output, int * mtx, size_t rows, size_t cols)
{
  size_t current_step = 1;
  size_t top = 0, bottom = rows - 1, right = cols - 1, left = 0;
  while (top < bottom + 1 && left < right + 1)
  {
    petrov::hor_step_2(mtx, bottom, cols, current_step);
    bottom--;

    petrov::vert_step_2(mtx, right, rows, cols, current_step);
    right--;

    if (top < bottom + 1)
    {
      petrov::hor_step_2(mtx, top, cols, current_step);
      top++;
    }

    if (left < right + 1)
    {
      petrov::vert_step_2(mtx, left, rows, cols, current_step);
      left++;
    }

    current_step++;
  }

  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i)
  {
    output << " " << mtx[i];
  }
  output << "\n";
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
  } else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0'))
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "BAD input\n";
    return 2;
  }
}