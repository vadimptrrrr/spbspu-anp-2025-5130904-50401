/*
malloc/free
UNC-SYM
SEQ-SYM
*/
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

namespace petrov{
  char* get_line();
  char* extend(char* old_str, char a);
  char* check_str(char* str1, char* str2, char* new_str);
  char* unc_sym(char* str1, char* str2);
  int seq_sym(char* str);
}

char* petrov::get_line()
{
    std::string tmp;
    std::cin >> tmp;

    char* str = static_cast<char*>(std::malloc(tmp.size() + 1));
    if (!str)
    {
      std::cerr << "malloc failed\n";
      return nullptr;
    }
    std::memcpy(str, tmp.c_str(), tmp.size() + 1);
    return str;
}


char* petrov::extend(char* old_str, char a)
{
  size_t len = 0;
  if (old_str)
  {
    len = std::strlen(old_str);
  }

  char* new_str = static_cast<char*>(malloc(len + 2));
  if (old_str && len > 0)
  {
    memcpy(new_str, old_str, len);
  }

  new_str[len] = a;
  new_str[len + 1] = '\0';
  free(old_str);
  return new_str;
}

char* petrov::check_str(char* str1, char* str2, char* new_str)
{
  if (!str1 || !str2)
  {
    return new_str;
  }
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);

  for (size_t i = 0; i < len1; i++)
  {
    bool flag = true;
    for (size_t j = 0; j < len2; j++)
    {
      if (str1[i] == str2[j])
      {
        flag = false;
        break;
      }
    }
    if (flag)
    {
      new_str = extend(new_str, str1[i]);
    }
  }
  return new_str;
}

char* petrov::unc_sym(char* str1, char* str2)
{
  char* new_str = static_cast<char*>(malloc(1));
  new_str[0] = '\0';
  if (!new_str)
  {
    std::cerr << "malloc failed\n";
    return nullptr;
  }
  new_str[0] = '\0';

  new_str = check_str(str1, str2, new_str);
  new_str = check_str(str2, str1, new_str);
  return new_str;
}

int petrov::seq_sym(char* str)
{
  size_t len = strlen(str);
  for (size_t i = 0; i < len - 1; ++i)
  {
    if (str[i] == str[i + 1])
    {
      return 1;
    }
  }
  return 0;
}

int main(){
  char* str1 = petrov::get_line();
  char* str2 = petrov::get_line();

  char* task1 = petrov::unc_sym(str1, str2);
  size_t task2 = petrov::seq_sym(str1);

  std::cout << task1 << "\n";
  std::cout << task2 << "\n";

  return 0;
}
