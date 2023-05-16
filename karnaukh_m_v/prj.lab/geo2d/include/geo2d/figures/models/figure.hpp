#include <iostream>

namespace geo2d::model {
    //base interfase for all figures
    class Figure {
    public:
        constexpr Figure();
        ~Figure();

        Figure(const Figure&);
        Figure& operator=(const Figure&);

        //brief Print figure in chars stream
        //param ostream Output stream

        virtual void WriteTo(std::ostream& ostream) const = 0;

        //brief Read figure from chars stream
        //param istream Input stream

        virtual void ReadFrom(std::istream& istream) = 0;
    };
    std::ostream& operator<<(std::ostream& ostream ? const Figure & figure);
    std::istream& operator>>(std::istream& istream, Figure& figure);
}