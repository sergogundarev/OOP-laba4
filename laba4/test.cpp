#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "figure.h"

TEST(PointTest, ConstructionAndGetters) {
    Point<int> p1(3, 4);
    EXPECT_EQ(p1.getX(), 3);
    EXPECT_EQ(p1.getY(), 4);
    
    Point<double> p2(2.5, 3.7);
    EXPECT_DOUBLE_EQ(p2.getX(), 2.5);
    EXPECT_DOUBLE_EQ(p2.getY(), 3.7);
}

TEST(PointTest, DistanceCalculation) {
    Point<int> p1(0, 0);
    Point<int> p2(3, 4);
    EXPECT_DOUBLE_EQ(p1.distanceTo(p2), 5.0);
}

TEST(SquareTest, AreaCalculation) {
    Square<double> square(Point<double>(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(square.area(), 25.0);
}

TEST(SquareTest, GeometricCenter) {
    Square<double> square(Point<double>(2, 2), 4.0);
    Point<double> center = square.geometricCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 2.0);
    EXPECT_DOUBLE_EQ(center.getY(), 2.0);
}

TEST(SquareTest, CopyConstructor) {
    Square<double> square1(Point<double>(1, 1), 3.0);
    Square<double> square2(square1);
    EXPECT_DOUBLE_EQ(square1.area(), square2.area());
}

TEST(SquareTest, EqualityOperator) {
    Square<double> square1(Point<double>(0, 0), 5.0);
    Square<double> square2(Point<double>(1, 1), 5.0);
    Square<double> square3(Point<double>(0, 0), 3.0);
    
    EXPECT_TRUE(square1 == square2); 
    EXPECT_FALSE(square1 == square3); 
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<double> rect(Point<double>(0, 0), 6.0, 4.0);
    EXPECT_DOUBLE_EQ(rect.area(), 24.0);
}

TEST(RectangleTest, GeometricCenter) {
    Rectangle<double> rect(Point<double>(1, 1), 4.0, 2.0);
    Point<double> center = rect.geometricCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 1.0);
    EXPECT_DOUBLE_EQ(center.getY(), 1.0);
}

TEST(RectangleTest, Dimensions) {
    Rectangle<double> rect(Point<double>(0, 0), 8.0, 6.0);
    EXPECT_DOUBLE_EQ(rect.getWidth(), 8.0);
    EXPECT_DOUBLE_EQ(rect.getHeight(), 6.0);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<double> trap(Point<double>(0, 0), 8.0, 4.0, 3.0);
    EXPECT_DOUBLE_EQ(trap.area(), (8.0 + 4.0) * 3.0 / 2.0);
}

TEST(TrapezoidTest, GeometricCenter) {
    Trapezoid<double> trap(Point<double>(0, 0), 6.0, 4.0, 2.0);
    Point<double> center = trap.geometricCenter();
    EXPECT_NEAR(center.getX(), 2.5, 0.001);
    EXPECT_NEAR(center.getY(), 1.0, 0.001);
}

TEST(TrapezoidTest, BasesAndHeight) {
    Trapezoid<double> trap(Point<double>(0, 0), 10.0, 6.0, 4.0);
    EXPECT_DOUBLE_EQ(trap.getBottomBase(), 10.0);
    EXPECT_DOUBLE_EQ(trap.getTopBase(), 6.0);
    EXPECT_DOUBLE_EQ(trap.getHeight(), 4.0);
}

TEST(ArrayTest, BasicOperations) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto square = std::make_shared<Square<double>>(Point<double>(0, 0), 2.0);
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(1, 1), 3.0, 4.0);
    
    arr.push_back(square);
    arr.push_back(rect);
    
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_GE(arr.getCapacity(), 2);
}

TEST(ArrayTest, EraseOperation) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto square = std::make_shared<Square<double>>(Point<double>(0, 0), 2.0);
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(1, 1), 3.0, 4.0);
    
    arr.push_back(square);
    arr.push_back(rect);
    
    arr.erase(0);
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_DOUBLE_EQ(arr[0]->area(), 12.0); 
}

TEST(ArrayTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto square = std::make_shared<Square<double>>(Point<double>(0, 0), 2.0); 
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(1, 1), 3.0, 4.0); 
    
    arr.push_back(square);
    arr.push_back(rect);
    
    EXPECT_DOUBLE_EQ(arr.totalArea(), 16.0);
}

TEST(ArrayTest, MoveSemantics) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    auto square = std::make_shared<Square<double>>(Point<double>(0, 0), 2.0);
    arr1.push_back(square);

    Array<std::shared_ptr<Figure<double>>> arr2(std::move(arr1));
    EXPECT_EQ(arr2.getSize(), 1);
    EXPECT_EQ(arr1.getSize(), 0);

    Array<std::shared_ptr<Figure<double>>> arr3;
    arr3 = std::move(arr2);
    EXPECT_EQ(arr3.getSize(), 1);
    EXPECT_EQ(arr2.getSize(), 0);
}

TEST(ConversionTest, ToDouble) {
    Square<double> square(Point<double>(0, 0), 5.0);
    double area = static_cast<double>(square);
    EXPECT_DOUBLE_EQ(area, 25.0);
}

TEST(TemplateTest, DifferentScalarTypes) {
    Square<int> square_int(Point<int>(0, 0), 5);
    EXPECT_DOUBLE_EQ(square_int.area(), 25.0);
    
    Square<float> square_float(Point<float>(0, 0), 5.0f);
    EXPECT_FLOAT_EQ(square_float.area(), 25.0f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}