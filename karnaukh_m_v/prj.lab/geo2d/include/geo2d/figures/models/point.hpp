#include <iostream>

namespace geo2d::model {
    
    //brief Simple primitive. Figure with one point
    //tparam CoordinatesType Type of point coordinates

    template<consepts::CoordinatesConcept CoordinatesType>
    class Point : public Figure {
    public:
        constexpr Point();
        ~Point();

        Point(const Point&);
        Point& operator=(const Point&);

        explicit constexpr Point(const CoordinatesType& coordinates);

        //brief Coordinates getter
        //return Reference to coordinates

        CoordinatesType& Coord();

        void WriteTo(std::ostream& ostream) const override;
        void ReadFrom(std::istream& istream) override;
    private:
        CoordinatesType coordinates_{};
    };
}