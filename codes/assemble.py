import time
import sys

# 콘솔 클리어
CLEAR_SCREEN = "\033[H\033[2J"

# 질문 단계
CarType_Q, Engine_Q, brakeSystem_Q, SteeringSystem_Q, Run_Test = range(5)

# 차량 타입
SEDAN, SUV, TRUCK = 1, 2, 3
# 엔진
GM, TOYOTA, WIA = 1, 2, 3
# 제동장치
MANDO, CONTINENTAL, BOSCH_B = 1, 2, 3
# 조향장치
BOSCH_S, MOBIS = 1, 2

# 사용자가 고른 선택지 저장
stack = [0] * 5

def delay(ms):
    time.sleep(ms / 1000.0)

def clear():
    sys.stdout.write(CLEAR_SCREEN)
    sys.stdout.flush()

def show_menu(step):
    clear()
    if step == CarType_Q:
        print("        ______________")
        print("       /|            |")
        print("  ____/_|_____________|____")
        print(" |                      O  |")
        print(" '-(@)----------------(@)--'")
        print("===============================")
        print("어떤 차량 타입을 선택할까요?")
        print("1. Sedan\n2. SUV\n3. Truck")
    elif step == Engine_Q:
        print("어떤 엔진을 탑재할까요?")
        print("0. 뒤로가기\n1. GM\n2. TOYOTA\n3. WIA\n4. 고장난 엔진")
    elif step == brakeSystem_Q:
        print("어떤 제동장치를 선택할까요?")
        print("0. 뒤로가기\n1. MANDO\n2. CONTINENTAL\n3. BOSCH")
    elif step == SteeringSystem_Q:
        print("어떤 조향장치를 선택할까요?")
        print("0. 뒤로가기\n1. BOSCH\n2. MOBIS")
    elif step == Run_Test:
        print("멋진 차량이 완성되었습니다.")
        print("0. 처음 화면으로 돌아가기\n1. RUN\n2. Test")
    print("===============================")

def is_valid_range(step, ans):
    if step == CarType_Q and not (1 <= ans <= 3):
        print("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능"); return False
    if step == Engine_Q    and not (0 <= ans <= 4):
        print("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능"); return False
    if step == brakeSystem_Q and not (0 <= ans <= 3):
        print("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능"); return False
    if step == SteeringSystem_Q and not (0 <= ans <= 2):
        print("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능"); return False
    if step == Run_Test    and not (0 <= ans <= 2):
        print("ERROR :: Run 또는 Test 중 하나를 선택 필요"); return False
    return True

def select_car_type(a):
    stack[CarType_Q] = a
    name = {1:"Sedan",2:"SUV",3:"Truck"}[a]
    print(f"차량 타입으로 {name}을 선택하셨습니다.")

def select_engine(a):
    stack[Engine_Q] = a
    name = {1:"GM",2:"TOYOTA",3:"WIA",4:"고장난 엔진"}[a]
    print(f"{name} 엔진을 선택하셨습니다.")

def select_brake(a):
    stack[brakeSystem_Q] = a
    name = {1:"MANDO",2:"CONTINENTAL",3:"BOSCH"}[a]
    print(f"{name} 제동장치를 선택하셨습니다.")

def select_steering(a):
    stack[SteeringSystem_Q] = a
    name = {1:"BOSCH",2:"MOBIS"}[a]
    print(f"{name} 조향장치를 선택하셨습니다.")

def is_valid_check():
    if stack[CarType_Q]==SEDAN and stack[brakeSystem_Q]==CONTINENTAL: return False
    if stack[CarType_Q]==SUV   and stack[Engine_Q]==TOYOTA:       return False
    if stack[CarType_Q]==TRUCK and stack[Engine_Q]==WIA:          return False
    if stack[CarType_Q]==TRUCK and stack[brakeSystem_Q]==MANDO:   return False
    if stack[brakeSystem_Q]==BOSCH_B and stack[SteeringSystem_Q]!=BOSCH_S: return False
    return True

def run_produced_car():
    if not is_valid_check():
        print("자동차가 동작되지 않습니다"); return
    if stack[Engine_Q] == 4:
        print("엔진이 고장나있습니다."); print("자동차가 움직이지 않습니다."); return

    carNames = {1:"Sedan",2:"SUV",3:"Truck"}
    engNames = {1:"GM",2:"TOYOTA",3:"WIA"}
    brakeNames = {1:"Mando",2:"Continental",3:"Bosch"}
    steerNames= {1:"Bosch",2:"Mobis"}

    print(f"Car Type : {carNames[stack[CarType_Q]]}")
    print(f"Engine   : {engNames[stack[Engine_Q]]}")
    print(f"Brake    : {brakeNames[stack[brakeSystem_Q]]}")
    print(f"Steering : {steerNames[stack[SteeringSystem_Q]]}")
    print("자동차가 동작됩니다.")

def test_produced_car():
    if stack[CarType_Q]==SEDAN and stack[brakeSystem_Q]==CONTINENTAL:
        print("FAIL\nSedan에는 Continental제동장치 사용 불가")
    elif stack[CarType_Q]==SUV and stack[Engine_Q]==TOYOTA:
        print("FAIL\nSUV에는 TOYOTA엔진 사용 불가")
    elif stack[CarType_Q]==TRUCK and stack[Engine_Q]==WIA:
        print("FAIL\nTruck에는 WIA엔진 사용 불가")
    elif stack[CarType_Q]==TRUCK and stack[brakeSystem_Q]==MANDO:
        print("FAIL\nTruck에는 Mando제동장치 사용 불가")
    elif stack[brakeSystem_Q]==BOSCH_B and stack[SteeringSystem_Q]!=BOSCH_S:
        print("FAIL\nBosch제동장치에는 Bosch조향장치 이외 사용 불가")
    else:
        print("PASS")

def main():
    step = CarType_Q
    while True:
        show_menu(step)
        buf = input("INPUT > ").strip()

        if buf.lower() == "exit":
            print("바이바이")
            break

        try:
            ans = int(buf)
        except:
            print("ERROR :: 숫자만 입력 가능")
            delay(800)
            continue

        if not is_valid_range(step, ans):
            delay(800)
            continue

        if ans == 0:
            if step == Run_Test:
                step = CarType_Q
            elif step > CarType_Q:
                step -= 1
            continue

        # 다음 단계 또는 실행/테스트
        if step == CarType_Q:
            select_car_type(ans); delay(800); step = Engine_Q
        elif step == Engine_Q:
            select_engine(ans); delay(800); step = brakeSystem_Q
        elif step == brakeSystem_Q:
            select_brake(ans); delay(800); step = SteeringSystem_Q
        elif step == SteeringSystem_Q:
            select_steering(ans); delay(800); step = Run_Test
        elif step == Run_Test:
            if ans == 1:
                run_produced_car(); delay(2000)
            elif ans == 2:
                print("Test..."); delay(1500); test_produced_car(); delay(2000)

if __name__ == "__main__":
    main()