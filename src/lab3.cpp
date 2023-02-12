#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

auto print = [](auto x) {
  std::cout << x << '\n';
};

template <typename T, typename F>
void forEach(T items[], size_t len, F fn) {
    for (size_t i{}; i < len; ++i){
        fn(items[i]);
    }
}

char * removeDelim(char * inputOne) {
  char copyInput[256];
  strcpy(copyInput, inputOne);
  char * token = strtok(copyInput, ",");
  return token;
}

template <typename T, typename F>
bool find(T items [], size_t len, F fn) {
  bool found(false);
  for (size_t i{}; i < len; ++i) {
    char * token = removeDelim(items[i]);
    if (stricmp(token, fn) == 0) {
      found = true;
    }
  }
  return found;
}

char * strDup(const char * s) {
  char * s2 = new char[std::strlen(s) + 1]{};
  std::strcpy(s2, s);
  return s2;
}

char * getItem() {
  char line[256] {};
  char * input {};
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.getline(line, 256);
  std::cin.clear();
  std::cout << '\n';
  input = new char[strlen(line) + 5];
  strcpy(input, line);
  return input;
}

char * getQty() {
  char line[256] {};
  char * input {};
  std::cin.getline(line, 256);
  std::cin.clear();
  std::cout << '\n';
  input = new char[strlen(line) + 1];
  strcpy(input, line);
  return input;
}

void append(char **& items, size_t & len, char *newItem) {
  char ** temp = new char *[len + 1];
  for (size_t i{}; i < len; ++i) {
    temp[i] = items[i];
  }
  temp[len] = newItem;
  len++;
  delete [] items;
  items = temp;
}

void remove(char **& items, size_t & len, char * deleteItem) {
  char ** temp = new char *[len -1];
  int index{0};
  bool loop(true);
  if (find(items, len, deleteItem)) {
    int i{0};
    while (loop && (i < len)) {
      if (stricmp(removeDelim(items[i]), deleteItem) == 0) {
        delete [] items[i];
        --len;
        index = i;
        loop = false;
      }
      else {
        temp[i] = items[i];
        ++i;
      }
    }
    while (index < len) {
      temp[index] = items[index +1];
      ++index;
    }
    delete [] items;
    items = temp;
  }
  else {
    std::cout << "The item to remove wasn't in the pantry." << '\n';
  }
}

char * delimItem(char * inputOne, char * inputTwo) {
  const char * strB = {", "};
  char strA [256];
  strcat(strA, inputOne);
  strcat(strA, strB);
  strcat(strA, inputTwo);
  char * delimItems = new char (strlen(strA) + 1);
  delimItems = strDup(strA);
  return delimItems;
}

void modify(char **& items, size_t len, char * modifyItem) {
  int index{0};
  char line [256];
  char * qty {};
  if (find(items, len, modifyItem)) {
    while (stricmp(removeDelim(items[index]), modifyItem) != 0) {
      ++index;
    }
    delete [] items[index];
    std::cout << "Modified item name? \n";
    std::cin.getline(line, 256);
    std::cin.clear();
    std::cout << "How many do you have? \n";
    qty = getQty();
    char * newItem = delimItem(line, qty);
    strcpy(items[index], newItem);
    delete [] newItem;
  }
  else {
    std::cout << "Item is not in the pantry.\n";
  }
}

void fileSave (char ** items, size_t len, char * fileName) {
  std::ofstream fileOut(fileName);
  for (size_t i {}; i < len; ++i) {
    fileOut << items[i] << '\n';
  }
}

void menuDisplay(char **& items, size_t len, char * fileName) {
  int in {};
  char * input{};
  std::cout << "Pantry Menu" << '\n';
  do {
    std::cout << "Menu:\n" <<"1. Add item\n" << "2. Remove item\n" << "3. Find item\n" << "4. Edit item\n" << "5. Display pantry items\n" << "6. Save\n" << "7. Quit\n";
    std::cin >> in;
    std::cin.clear();
    if (in < 1 || in > 7) {
      std::cout << "Please select a valid menu item.";
      std::cin >> in;
    }
    while (in < 1 || in > 7);
    switch (in) {
      case 1: {
        char * qty{};
        std::cout << "What item would you like to add? ";
        input = getItem();
        std::cout << "How many? ";
        qty = getQty();
        char * newIng = delimItem(input, qty);
        append(items, len, newIng);
        std::cout << "Item added to the pantry.\n";
        delete [] input;
        delete [] qty;
        break;
      }
      case 2: {
        std::cout << "What item would you like to remove? ";
        input = getItem();
        remove(items, len, input);
        delete [] input;
        break;
      }
      case 3: {
        std::cout << "What item would you like to find? ";
        input = getItem();
        if (find(items, len, input)) {
          std::cout << "The pantry does contain " << input << ".\n";
        }
        else {
          std::cout << "The pantry does not have that item.\n";
        };
        delete [] input;
        break;
      }
      case 4: {
        std::cout << "What item would you like to modify? ";
        input = getItem();
        modify(items, len, input);
        delete [] input;
        break;
      }
      case 5: {
        std::cout << "Your pantry contains the following items: \n";
        forEach(items, len, print);
        std::cout << '\n';
        break;
      }
       case 6: {
        std::cout << "Your pantry items have been saved.\n";
        fileSave(items, len, fileName);
        break;
      }
      case 7: {
        std::cout << "Exiting the program\n";
        return;
        break;
      }
      default: {
        std::cout << "Invalid entry.\n";
        break;
      }
    }
  }
  while (in != 7);
}

int main(int argc, char ** argv) {
  std::cout << "Lab3\n\n";
  if (argc != 2){
    std::cerr << "Please provide a filename.\n";
    return 1;
  }
  char **items{};
  size_t len{};
  char buffer[256];
  char *fileName{};
  std::fstream myPantry(argv[1]);
  fileName = argv[1];
  while (myPantry.getline(buffer, 256)) {
    char * item = strDup(buffer);
    append(items, len, item);
  }
  menuDisplay(items, len, fileName);
  for (size_t i{}; i < len; ++i) {
    delete [] items[i];
  }
  delete [] items; 
}
