#include <iostream>

namespace geo2d::concepts {
    template<class CoordinatesType>
    consept CoordinatesConcept = requires(CoordinatesType coordinates) {
        requires std::default_initializable<CoordinatesType>;
        requires std::copy_constructible<CoordinatesType>;

    //Type of coordinates
    typename CoordinatesType::Coordinate;

    //Dimension of space
    static_cast<unsigned int>(CoordinatesType::dimension);

    //We can get coordinate for each axis
    { coordinates.template get<0>() } -> std::same_as<typename CoordinatesType::Coordinate const&>;
    { coordinates.get(0) } -> std::same_as<typename CoordinatesType::Coordinate const&>;

    //We can set coordinate for each axis
    { coordinates.template set<0>(typename CoordinatesType::Coordinate()) } -> std::same_as<void>;
    { coordinates.set(0, typename CoordinatesType::Coordinate()) } -> std::same_as<void>;

    };

}