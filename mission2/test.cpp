#include <gmock/gmock.h>

#include "assemble.h"

TEST(TC, 000) {
  Sedan sedan;
  Suv suv;
  Truck truck;

  assemble::select_engine(sedan, 0);
  assemble::select_engine(suv, 0);
  assemble::select_engine(truck, 0);

  assemble::select_brake(sedan, 0);
  assemble::select_brake(suv, 0);
  assemble::select_brake(truck, 0);

  assemble::select_sterring(sedan, 0);
  assemble::select_sterring(suv, 0);
  assemble::select_sterring(truck, 0);

  assemble::test(sedan);
  assemble::test(suv);
  assemble::test(truck);

  assemble::run(sedan);
  assemble::run(suv);
  assemble::run(truck);
}

TEST(TC, 001) {
  Sedan sedan;

  assemble::select_engine(sedan, EngineSystem::GM);
  assemble::select_brake(sedan, BrakeSystem::CONTINENTAL);
  assemble::select_sterring(sedan, SteeringSystem::MOBIS);
  ASSERT_FALSE(assemble::test(sedan));
  assemble::select_brake(sedan, BrakeSystem::BOSCH_B);
  ASSERT_TRUE(assemble::test(sedan));
  assemble::select_sterring(sedan, SteeringSystem::BOSCH_S);
  ASSERT_FALSE(assemble::test(sedan));
  assemble::select_engine(sedan, EngineSystem::Broken);
  assemble::select_sterring(sedan, SteeringSystem::MOBIS);
  ASSERT_TRUE(assemble::test(sedan));
  assemble::run(sedan);
}

TEST(TC, 002) {
  Suv suv;

  assemble::select_engine(suv, EngineSystem::WIA);
  assemble::select_brake(suv, BrakeSystem::CONTINENTAL);
  assemble::select_sterring(suv, SteeringSystem::MOBIS);
  ASSERT_TRUE(assemble::test(suv));
  assemble::select_engine(suv, EngineSystem::TOYOTA);
  assemble::select_brake(suv, BrakeSystem::MANDO);
  ASSERT_FALSE(assemble::test(suv));
  assemble::select_brake(suv, BrakeSystem::BOSCH_B);
  assemble::select_sterring(suv, SteeringSystem::BOSCH_S);
  ASSERT_FALSE(assemble::test(suv));
  assemble::select_sterring(suv, SteeringSystem::MOBIS);
  assemble::select_engine(suv, EngineSystem::Broken);
  ASSERT_TRUE(assemble::test(suv));
  assemble::run(suv);
}

TEST(TC, 003) {
  Truck truck;

  assemble::select_engine(truck, EngineSystem::WIA);
  assemble::select_brake(truck, BrakeSystem::CONTINENTAL);
  assemble::select_sterring(truck, SteeringSystem::MOBIS);
  ASSERT_FALSE(assemble::test(truck));
  assemble::select_engine(truck, EngineSystem::GM);
  assemble::select_brake(truck, BrakeSystem::MANDO);
  ASSERT_FALSE(assemble::test(truck));
  assemble::select_brake(truck, BrakeSystem::BOSCH_B);
  assemble::select_sterring(truck, SteeringSystem::BOSCH_S);
  ASSERT_FALSE(assemble::test(truck));
  assemble::select_sterring(truck, SteeringSystem::MOBIS);
  ASSERT_TRUE(assemble::test(truck));
  assemble::select_engine(truck, EngineSystem::Broken);
  ASSERT_TRUE(assemble::test(truck));
  assemble::run(truck);
}

TEST(TC, 004) {
  CarHelper helper;
  helper.change(Car::SEDAN);
  assemble::select_engine(helper, EngineSystem::GM);
  assemble::select_brake(helper, BrakeSystem::CONTINENTAL);
  assemble::select_sterring(helper, SteeringSystem::MOBIS);
  ASSERT_FALSE(assemble::test(helper));
  assemble::select_brake(helper, BrakeSystem::BOSCH_B);
  ASSERT_TRUE(assemble::test(helper));
  assemble::select_sterring(helper, SteeringSystem::BOSCH_S);
  ASSERT_FALSE(assemble::test(helper));
  assemble::run(helper);

  helper.change(Car::SUV);
  assemble::select_engine(helper, EngineSystem::WIA);
  assemble::select_brake(helper, BrakeSystem::CONTINENTAL);
  assemble::select_sterring(helper, SteeringSystem::MOBIS);
  ASSERT_TRUE(assemble::test(helper));
  assemble::select_engine(helper, EngineSystem::TOYOTA);
  assemble::select_brake(helper, BrakeSystem::MANDO);
  ASSERT_FALSE(assemble::test(helper));
  assemble::select_brake(helper, BrakeSystem::BOSCH_B);
  assemble::select_sterring(helper, SteeringSystem::BOSCH_S);
  ASSERT_FALSE(assemble::test(helper));
  assemble::run(helper);

  helper.change(Car::TRUCK);
  assemble::select_engine(helper, EngineSystem::WIA);
  assemble::select_brake(helper, BrakeSystem::CONTINENTAL);
  assemble::select_sterring(helper, SteeringSystem::MOBIS);
  ASSERT_FALSE(assemble::test(helper));
  assemble::select_engine(helper, EngineSystem::GM);
  assemble::select_brake(helper, BrakeSystem::MANDO);
  ASSERT_FALSE(assemble::test(helper));
  assemble::select_brake(helper, BrakeSystem::BOSCH_B);
  assemble::select_sterring(helper, SteeringSystem::BOSCH_S);
  ASSERT_FALSE(assemble::test(helper));
  assemble::select_sterring(helper, SteeringSystem::MOBIS);
  ASSERT_TRUE(assemble::test(helper));
  assemble::run(helper);
}