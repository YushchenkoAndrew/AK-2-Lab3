#include<iostream>
#include <algorithm>
#include <vector>
#include <string.h>

// States for Parser State Machine
#define INIT_COMMAND 0
#define GET_COMMAND 1
#define NEXT_COMMAND 2
#define GET_VALUE 3
#define GET_LIST 4

// Completed commands
std::vector<char> commands;

void parser(int state, int i, int index, int len, char **argv);

bool isNumber(char *str) {
      char* p;
      strtol(str, &p, 10);
      return *p == 0;
}

void getLongCommand(int state, int i, int index, int len, char **argv) {
  if (strcmp(argv[index], "--help") == 0) {
    if (std::find(commands.begin(), commands.end(), 'h') == commands.end()) {
      std::cout << "arg: help" << std::endl;
      commands.push_back('h');
    }

    parser(INIT_COMMAND, 0, index + 1, len, argv);
  } else {

    if (strcmp(argv[index], "--version") == 0) {
      if (std::find(commands.begin(), commands.end(), 'v') == commands.end()) {
        std::cout << "arg: version" << std::endl;
        commands.push_back('v');
      }

      parser(INIT_COMMAND, 0, index + 1, len, argv);
    } else {
      if (strcmp(argv[index], "--num") == 0) {
        parser(GET_VALUE, 0, index + 1, len, argv);
    } else {

        if (strcmp(argv[index], "--list") == 0) {
          parser(GET_LIST, 0, index + 1, len, argv);
        } else
          std::cout << "arg: invalid option" << std::endl;
      }
    }
  }
}

void shortCommand(int state, int i, int index, int len, char **argv) {
  switch (argv[index][i])
  {
  case 'h':
    if (std::find(commands.begin(), commands.end(), 'h') == commands.end()) {
      std::cout << "arg: help" << std::endl;
      commands.push_back('h');
    }

    parser(NEXT_COMMAND, i + 1, index, len, argv);
    break;

  case 'v':
    if (std::find(commands.begin(), commands.end(), 'v') == commands.end()) {
      std::cout << "arg: version" << std::endl;
      commands.push_back('v');
    }

    parser(NEXT_COMMAND, i + 1, index, len, argv);
    break;

  case 'n':
    if (argv[index][i + 1] == '\0')
      parser(GET_VALUE, 0, index + 1, len, argv);
    else std::cout << "arg: invalid option" << std::endl;
    break;

  case 'l':
    if (argv[index][i + 1] == '\0')
      parser(GET_LIST, 0, index + 1, len, argv);
    else std::cout << "arg: invalid option" << std::endl;
    break;

  default:
    std::cout << "arg: invalid option" << std::endl;
    break;
  }
}


void parser(int state, int i, int index, int len, char **argv) {
  // Check if input params is ended
  if (index == len) {
    if (state != INIT_COMMAND)
      std::cout << "arg: invalid option" << std::endl;
    return;
  }

  switch(state) {
    case INIT_COMMAND:
      if (argv[index][i] == '-')
        parser(GET_COMMAND, i + 1, index, len, argv);
      else std::cout << "arg: Cannot Access '" << argv[index][i] << "'" << std::endl;
      break;

    case GET_COMMAND:
      if (argv[index][i] == '-') getLongCommand(state, i + 1, index, len, argv);
      else shortCommand(state, i, index, len, argv);
      break;

    case NEXT_COMMAND:
      if (argv[index][i] == '\0')
        parser(INIT_COMMAND, 0, index + 1, len, argv);
      else shortCommand(state, i, index, len, argv);
      break;

    case GET_VALUE:
      // Convert String to int with error checker

      if (isNumber(argv[index])) {
        if (std::find(commands.begin(), commands.end(), 'n') == commands.end()) {
          std::cout << "arg: value = " << std::stoi(argv[index]) << std::endl;
          commands.push_back('n');
        }
      } else {
        std::cout << "arg: invalid option" << std::endl;
        break;
      }

      parser(INIT_COMMAND, 0, index + 1, len, argv);
      break;

    case GET_LIST:
      if (std::find(commands.begin(), commands.end(), 'l') != commands.end()) {
        parser(INIT_COMMAND, 0, index + 1, len, argv);
        break;
      }

      std::cout << "arg: list:";

      char * pch;
      pch = strtok(argv[index], ",");
      while (pch != NULL)
      {
        if (isNumber(pch))
          std::cout << " " << std::stoi(pch);
        else {
          std::cout << std::endl <<"arg: invalid option" << std::endl;
          return;
        }

        pch = strtok(NULL, ",");
      }
      std::cout << std::endl;
      commands.push_back('l');

      parser(INIT_COMMAND, 0, index + 1, len, argv);
      break;
  }
}


int main(int argc, char *argv[]) {
  std::cout << "Run Command" << std::endl;

  parser(INIT_COMMAND, 0, 1, argc, argv);

  return 0;
}
