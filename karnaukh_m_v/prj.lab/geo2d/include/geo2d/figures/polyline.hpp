#include <iostream>

namespace geo2d {
    //

    template<typename CoordinateType = float>
    using Polyline = model::Polyline<space::Coordinates<CoordinateType, 2>>;
}