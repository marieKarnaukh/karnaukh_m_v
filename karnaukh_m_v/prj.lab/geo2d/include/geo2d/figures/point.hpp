#include <iostream>

namespace geo2d {

    //That's class implement point for 2 dimension
    //First coordinate is x and second is y
    //tparam CoordinateType Type of each coordinate

    template<typename CoordinateType = float>
    class Point : public model::Point<space::Coordinates<CoordinateType, 2>> {
    private:
        using CoordinatesType = space::Coordinates<CoordinateType, 2>;

    public:
        constexpr Point();
        ~Point();

        Point(const Point&);
        Point& operator=(const Point&);

        constexpr Point(CoordinateType x, CoordinateType y);
        constexpr Point(const CoordinatesType& coordinates);

        //X coordinate getter
        //return Const reference to X coord

        constexpr const CoordinateType& x() const;

        //Ycoordinate getter
        //return Const reference to Y coord

        constexpr const CoordinateType& y() const;

        //Set X coordinate by value
        //param v Value to set

        void x(const CoordinateType& v);

        //Set Y coord by value
        //param v Value to set

        void y(const CoordinateType& v);
    };
}