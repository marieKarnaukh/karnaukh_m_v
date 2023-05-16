#include <iostream>

namespace geo2d::model {
    //

    template<
        concepts::CoordinatesConcept CoordinatesType,
        bool closed_ = true,
        template<typename _ = CoordinatesType>,
        class PointsContainer = std::vector
    >
    class Polyline : public Figure, public PointsContanier<> {
    public: 
        static constexpr bool closed = closed_;
    public:
        constexpr Polyline();
        ~Polyline();

        Polyline(const Polyline&);
        Polyline& operator=(const Polyline&);

        //

        template<std::input_iterator Iterator>
        constexpr Polyline(const Iterator& begin, const Iterator& end);

        //

        constexpr Polyline(std::initializer_list<CoordinatesType> il);
        void WhiteTo(std::ostream& ostream) const override;
        void ReadFrom(std::istream& istream) override;
    };


}