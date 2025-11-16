#include <iostream>
#include <fstream>
#include <cstddef>

namespace petrov
{
  void create(std::istream & input, int * mtx, size_t rows, size_t cols);
  int * copy(int* mtx, size_t rows, size_t cols);
  bool it_number(const char * w);
  void LFT_BOT_CNT(std::ostream & output, int * mtx, size_t rows, size_t cols);
  void vert_step(int * mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_down, size_t cols);
  void hor_step(int * mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_right, size_t cols);
  void FLL_INC_WAV(std::ostream & output, int * mtx, size_t rows, size_t cols);
  void vert_step_2(int * mtx, size_t col, size_t row_start, size_t row_end, size_t cols, size_t plus_step);
  void hor_step_2(int * mtx, size_t row, size_t col_start, size_t col_end, size_t cols, size_t plus_step);
}

int * petrov::copy(int* mtx, size_t rows, size_t cols)
{
  int* copy = new int[rows * cols]();
  for (size_t i = 0; i < (rows * cols); ++i) {
    copy[i] = mtx[i];
  }
  return copy;
}

void petrov::create(std::istream & input, int * mtx, size_t rows, size_t cols)
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

void petrov::vert_step(int * mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_down, size_t cols)
{
  if (move_down)
  {
    for (long long i = static_cast<long long> (top); i <= static_cast<long long> (bottom); ++i)
    {
      mtx[i * cols + left] += plus_step;
      ++plus_step;
    }
  }
  else
  {
    for (long long i = static_cast<long long> (bottom); i >= static_cast<long long> (top); --i)
    {
      mtx[i * cols + right] += static_cast<int> (plus_step);
      ++plus_step;
    }
  }
}

void petrov::hor_step(int * mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_right, size_t cols)
{
  if (move_right)
  {
    for (long long i = static_cast<long long> (left); i <= static_cast<long long> (right); ++i)
    {
      mtx[bottom * cols + i] += static_cast<int> (plus_step);
      ++plus_step;
    }
  }
  else
  {
    for (long long i = static_cast<long long> (right); i >= static_cast<long long> (left); --i)
    {
      mtx[top * cols + i] += static_cast<int> (plus_step);
      ++plus_step;
    }
  }
}

void petrov::LFT_BOT_CNT(std::ostream & output, int * mtx, size_t rows, size_t cols)
{
  size_t current_step = 1;
  size_t top = 0, bottom = rows - 1, right = cols - 1, left = 0;

  while (top <= bottom && left <= right)
  {
    hor_step(mtx, top, bottom, right, left, current_step, true, cols);
    if (bottom == 0) break;
    --bottom;

    vert_step(mtx, top, bottom, right, left, current_step, false, cols);
    if (right == 0) break;
    --right;

    if (top <= bottom)
    {
      hor_step(mtx, top, bottom, right, left, current_step, false, cols);
      ++top;
    }

    if (left <= right)
    {
      vert_step(mtx, top, bottom, right, left, current_step, true, cols);
      ++left;
    }
  }
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i)
  {
    output << " " << mtx[i];
  }
  output << "\n";
}

void petrov::vert_step_2(int * mtx, size_t col, size_t row_start, size_t row_end, size_t cols, size_t plus_step)
{
  for (size_t r = row_start; r <= row_end; ++r)
  {
    mtx[r * cols + col] += static_cast<int> (plus_step);
  }
}

void petrov::hor_step_2(int * mtx, size_t row, size_t col_start, size_t col_end, size_t cols, size_t plus_step)
{
  for (size_t i = col_start; i <= col_end; ++i)
  {
    mtx[row * cols + i] += static_cast<int> (plus_step);
  }
}

void petrov::FLL_INC_WAV(std::ostream & output, int * mtx, size_t rows, size_t cols)
{
  size_t current_step = 1;
  size_t top = 0, bottom = rows - 1, right = cols - 1, left = 0;
  while (top <= bottom && left <= right)
  {
    hor_step_2(mtx, bottom, left, right, cols, current_step);
    if (bottom == 0) break;
    --bottom;

    if (top <= bottom && left <= right)
    {
      vert_step_2(mtx, right, top, bottom, cols, current_step);
      if (right == 0) break;
      --right;
    }

    if (top <= bottom && left <= right)
    {
      hor_step_2(mtx, top, left, right, cols, current_step);
      ++top;
    }

    if (top <= bottom && left <= right)
    {
      vert_step_2(mtx, left, top, bottom, cols, current_step);
      ++left;
    }

    ++current_step;
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

  if (rows == 0 || cols == 0)
  {
    output << rows << " " << cols;
    return 0;
  }

  if (argv[1][0] == '1')
  {
    int * matrix1 = nullptr;
    bool allocated = false;
    const size_t MAX_SIZE = 10000;
    if (rows * cols <= MAX_SIZE)
    {
      static int static_buf[MAX_SIZE];
      for (size_t i = 0; i < (rows * cols); ++i)
      {
        static_buf[i] = 0;
      }
      matrix1 = static_buf;
    }
    else
    {
      matrix1 = new int[rows * cols];
      allocated = true;
    }

    petrov::create(input, matrix1, rows, cols);
    if (!input)
    {
      std::cerr << "BAD input\n";
      if (allocated) delete[] matrix1;
      return 2;
    }

    int * matrix2 = petrov::copy(matrix1, rows, cols);
    petrov::LFT_BOT_CNT(output, matrix1, rows, cols);
    petrov::FLL_INC_WAV(output, matrix2, rows, cols);
    delete[] matrix2;
    if (allocated) delete[] matrix1;
    return 0;
  }

  int * matrix = new int[rows * cols];
  petrov::create(input, matrix, rows, cols);
  int * matrix2 = petrov::copy(matrix, rows, cols);

  if (!input)
  {
    std::cerr << "BAD input\n";
    delete[] matrix;
    delete[] matrix2;
    return 2;
  }

  try
  {
    petrov::LFT_BOT_CNT(output, matrix, rows, cols);
    petrov::FLL_INC_WAV(output, matrix2, rows, cols);
  }
  catch(const std::exception& e)
  {
    delete[] matrix;
    delete[] matrix2;
    throw;
  }

  delete[] matrix;
  delete[] matrix2;

  return 0;
}
