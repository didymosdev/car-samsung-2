#ifdef _DEBUG

#include "gmock/gmock.h"

int main() {
  testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assemble.h"

#define CLEAR_SCREEN "\033[H\033[2J"

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuestionType {
  CarType_Q,
  Engine_Q,
  brakeSystem_Q,
  SteeringSystem_Q,
  Run_Test,
};

void delay(int ms) {
  volatile int sum = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      for (int t = 0; t < ms; t++) {
        sum++;
      }
    }
  }
}

bool checkInput(int step, const char* buf, int& answer) {
  // ���ڷ� �� ������� Ȯ��
  char* checkNumber;
  answer = strtol(buf, &checkNumber, 10);  // ���ڿ��� 10������ ��ȯ

  // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
  if (*checkNumber != '\0') {
    printf("ERROR :: ���ڸ� �Է� ����\n");
    delay(800);
    return false;
  }

  if (step == CarType_Q && !(answer >= 1 && answer <= 3)) {
    printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
    delay(800);
    return false;
  }

  if (step == Engine_Q && !(answer >= 0 && answer <= 4)) {
    printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
    delay(800);
    return false;
  }

  if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3)) {
    printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
    delay(800);
    return false;
  }

  if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) {
    printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
    delay(800);
    return false;
  }

  if (step == Run_Test && !(answer >= 0 && answer <= 2)) {
    printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
    delay(800);
    return false;
  }
  return true;
}

void processStep(int& step, int answer) {
  if (step == CarType_Q) {
    selectCarType(answer);
    delay(800);
    step = Engine_Q;
  } else if (step == Engine_Q) {
    selectEngine(answer);
    delay(800);
    step = brakeSystem_Q;
  } else if (step == brakeSystem_Q) {
    selectbrakeSystem(answer);
    delay(800);
    step = SteeringSystem_Q;
  } else if (step == SteeringSystem_Q) {
    selectSteeringSystem(answer);
    delay(800);
    step = Run_Test;
  } else if (step == Run_Test && answer == 1) {
    runProducedCar();
    delay(5000);
  } else if (step == Run_Test && answer == 2) {
    printf("Test...\n");
    delay(1500);
    testProducedCar();
    delay(5000);
  }
}

void showMenu(int step, char* buf) {
  if (step == CarType_Q) {
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    for (int i = 1; i < Car::End; i++) {
      printf("%d. %s\n", i, Car::prompt[i]);
    }
  } else if (step == Engine_Q) {
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    for (int i = 1; i < EngineSystem::End; i++) {
      printf("%d. %s\n", i, EngineSystem::prompt[i]);
    }
  } else if (step == brakeSystem_Q) {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    for (int i = 1; i < BrakeSystem::End; i++) {
      printf("%d. %s\n", i, BrakeSystem::prompt[i]);
    }
  } else if (step == SteeringSystem_Q) {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    for (int i = 1; i < SteeringSystem::End; i++) {
      printf("%d. %s\n", i, SteeringSystem::prompt[i]);
    }
  } else if (step == Run_Test) {
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
  }
  printf("===============================\n");

  printf("INPUT > ");
  fgets(buf, sizeof(buf), stdin);

  // ���� ���๮�� ����
  char* context = nullptr;
  strtok_s(buf, "\r", &context);
  strtok_s(buf, "\n", &context);
}

CarHelper helper;

int main() {
  char buf[100];
  int step = CarType_Q;
  int answer = 0;

  while (1) {
    showMenu(step, buf);

    if (!strcmp(buf, "exit")) {
      printf("���̹���\n");
      break;
    }

    if (!checkInput(step, buf, answer)) {
      continue;
    }

    // ó������ ���ư���
    if (answer == 0 && step == Run_Test) {
      step = CarType_Q;
      continue;
    }

    // �������� ���ư���
    if (answer == 0 && step >= 1) {
      step -= 1;
      continue;
    }

    processStep(step, answer);
  }
}

void selectCarType(int answer) {
  helper.change(static_cast<Car::type>(answer));
  printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", Car::prompt[answer]);
}

void selectEngine(int answer) {
  assemble::select_engine(helper, answer);
  printf("%s ������ �����ϼ̽��ϴ�.\n", EngineSystem::prompt[answer]);
}

void selectbrakeSystem(int answer) {
  assemble::select_brake(helper, answer);
  printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", BrakeSystem::prompt[answer]);
}

void selectSteeringSystem(int answer) {
  assemble::select_sterring(helper, answer);
  printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", SteeringSystem::prompt[answer]);
}

int isValidCheck() { return assemble::test(helper); }

void runProducedCar() { assemble::run(helper); }

void testProducedCar() { assemble::test(helper, true); }

#endif