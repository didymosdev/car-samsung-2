#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <variant>

struct Car {
  enum type { SEDAN = 1, SUV = 2, TRUCK = 3, End };
  static constexpr const char* prompt[] = {"", "SEDAN", "SUV", "TRUCK"};
};

struct EngineSystem {
  enum type { GM = 1, TOYOTA = 2, WIA = 3, Broken = 4, End };
  static constexpr const char* prompt[] = {"", "GM", "TOYOTA", "WIA",
                                           "고장난 엔진"};
};

struct BrakeSystem {
  enum type { MANDO = 1, CONTINENTAL = 2, BOSCH_B = 3, End };
  static constexpr const char* prompt[] = {"", "MANDO", "CONTINENTAL",
                                           "BOOSCH_B"};
};

struct SteeringSystem {
  enum type { BOSCH_S = 1, MOBIS = 2, End };
  static constexpr const char* prompt[] = {"", "BOSCH", "MOBIS"};
};

struct engine_tag {};
struct brake_tag {};
struct sterring_tag {};

template <typename T>
struct select_t {
  template <typename U>
  void operator()(U& u, int type) {
    return select(T{}, u, type);
  }
};

namespace assemble {
inline static select_t select_engine = select_t<engine_tag>{};
inline static select_t select_brake = select_t<brake_tag>{};
inline static select_t select_sterring = select_t<sterring_tag>{};
}  // namespace assemble

class CarHelper;
struct test_t {
  template <typename T>
  bool operator()(T& t, bool print = false) {
    if constexpr (!std::is_same_v<T, CarHelper>) {
      if (t.brake == BrakeSystem::type::BOSCH_B &&
          t.steering == SteeringSystem::type::BOSCH_S) {
        if (print) {
          printf("자동차 부품 조합 테스트 결과 : FAIL\n");
          printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        }
        return false;
      }
    }
    bool succ = test(t, print);
    if constexpr (!std::is_same_v<T, CarHelper>) {
      if (succ && print) {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
      }
    }
    return succ;
  }
};

namespace assemble {
inline static test_t test = test_t{};
}  // namespace assemble

struct run_t {
  template <typename T>
  void operator()(T& t) {
    if constexpr (!std::is_same_v<T, CarHelper>) {
      if (!assemble::test(t, false)) {
        printf("자동차가 동작되지 않습니다\n");
        return;
      }
      if (t.engine == EngineSystem::type::Broken) {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
      }
      printf("Engine : %s\n", EngineSystem::prompt[static_cast<int>(t.engine)]);
      printf("Brake System : %s",
             BrakeSystem::prompt[static_cast<int>(t.brake)]);
      printf("SteeringSystem : %s\n",
             SteeringSystem::prompt[static_cast<int>(t.steering)]);

      printf("자동차가 동작됩니다.\n");
    }
    return run(t);
  }
};

namespace assemble {
inline static run_t run = run_t{};
}  // namespace assemble

template <typename T>
class Getter {
 public:
  EngineSystem::type get_engine() { return static_cast<T*>(this)->engine; }
  BrakeSystem::type get_brake() { return static_cast<T*>(this)->brake; }
  SteeringSystem::type get_steering() {
    return static_cast<T*>(this)->steering;
  }
};

class Sedan {
 public:
  friend void select(engine_tag, Sedan& sedan, int type) {
    sedan.engine = static_cast<EngineSystem::type>(type);
  }

  friend void select(brake_tag, Sedan& sedan, int type) {
    sedan.brake = static_cast<BrakeSystem::type>(type);
  }

  friend void select(sterring_tag, Sedan& sedan, int type) {
    sedan.steering = static_cast<SteeringSystem::type>(type);
  }

  friend bool test(Sedan& sedan, bool print) {
    if (sedan.brake == BrakeSystem::type::CONTINENTAL) {
      if (print) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
      }
      return false;
    }
    return true;
  }

  friend void run(Sedan& sedan) { printf("Car Type : Sedan\n"); }

  EngineSystem::type engine;
  BrakeSystem::type brake;
  SteeringSystem::type steering;
};

class Suv {
 public:
  friend void select(engine_tag, Suv& suv, int type) {
    suv.engine = static_cast<EngineSystem::type>(type);
  }

  friend void select(brake_tag, Suv& suv, int type) {
    suv.brake = static_cast<BrakeSystem::type>(type);
  }

  friend void select(sterring_tag, Suv& suv, int type) {
    suv.steering = static_cast<SteeringSystem::type>(type);
  }

  friend bool test(Suv& suv, bool print) {
    if (suv.engine == EngineSystem::type::TOYOTA) {
      if (print) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
      }
      return false;
    }
    return true;
  }

  friend void run(Suv& suv) { printf("Car Type : SUV\n"); }

  EngineSystem::type engine;
  BrakeSystem::type brake;
  SteeringSystem::type steering;
};

class Truck {
 public:
  friend void select(engine_tag, Truck& truck, int type) {
    truck.engine = static_cast<EngineSystem::type>(type);
  }

  friend void select(brake_tag, Truck& truck, int type) {
    truck.brake = static_cast<BrakeSystem::type>(type);
  }

  friend void select(sterring_tag, Truck& truck, int type) {
    truck.steering = static_cast<SteeringSystem::type>(type);
  }

  friend bool test(Truck& truck, bool print) {
    if (truck.engine == EngineSystem::type::WIA) {
      if (print) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
      }
      return false;
    } else if (truck.brake == BrakeSystem::type::MANDO) {
      if (print) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
      }
      return false;
    }
    return true;
  }

  friend void run(Truck& truck) { printf("Car Type : Truck\n"); }

  EngineSystem::type engine;
  BrakeSystem::type brake;
  SteeringSystem::type steering;
};

class CarHelper {
 public:
  CarHelper() = default;

  void change(Car::type type) {
    if (type == Car::SEDAN) {
      opaque = Sedan{};
    } else if (type == Car::SUV) {
      opaque = Suv{};
    } else if (type == Car::TRUCK) {
      opaque = Truck{};
    }
  }

  friend void select(engine_tag, CarHelper& car, int type) {
    if (auto* acc = std::get_if<Sedan>(&car.opaque)) {
      assemble::select_engine(*acc, type);
    } else if (auto* acc = std::get_if<Suv>(&car.opaque)) {
      assemble::select_engine(*acc, type);
    } else if (auto* acc = std::get_if<Truck>(&car.opaque)) {
      assemble::select_engine(*acc, type);
    }
  }

  friend void select(brake_tag, CarHelper& car, int type) {
    if (auto* acc = std::get_if<Sedan>(&car.opaque)) {
      assemble::select_brake(*acc, type);
    } else if (auto* acc = std::get_if<Suv>(&car.opaque)) {
      assemble::select_brake(*acc, type);
    } else if (auto* acc = std::get_if<Truck>(&car.opaque)) {
      assemble::select_brake(*acc, type);
    }
  }

  friend void select(sterring_tag, CarHelper& car, int type) {
    if (auto* acc = std::get_if<Sedan>(&car.opaque)) {
      assemble::select_sterring(*acc, type);
    } else if (auto* acc = std::get_if<Suv>(&car.opaque)) {
      assemble::select_sterring(*acc, type);
    } else if (auto* acc = std::get_if<Truck>(&car.opaque)) {
      assemble::select_sterring(*acc, type);
    }
  }

  friend bool test(CarHelper& car, bool print) {
    if (auto* acc = std::get_if<Sedan>(&car.opaque)) {
      return assemble::test(*acc, print);
    } else if (auto* acc = std::get_if<Suv>(&car.opaque)) {
      return assemble::test(*acc, print);
    } else if (auto* acc = std::get_if<Truck>(&car.opaque)) {
      return assemble::test(*acc, print);
    }
    return false;
  }

  friend void run(CarHelper& car) {
    if (auto* acc = std::get_if<Sedan>(&car.opaque)) {
      assemble::run(*acc);
    } else if (auto* acc = std::get_if<Suv>(&car.opaque)) {
      assemble::run(*acc);
    } else if (auto* acc = std::get_if<Truck>(&car.opaque)) {
      assemble::run(*acc);
    }
  }
  std::variant<std::monostate, Sedan, Suv, Truck> opaque;
};