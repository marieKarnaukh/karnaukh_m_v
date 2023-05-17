#include <iostream>

namespace geo2d {
    namespace orto {
        class Quad {
        public:
            Quad() : x_(0), y_(0), lenght_(0), width_(0) {}
            Quad(double x, double y, double len = 0, double wid = 0)
                : x_(x), y_(y), lenght_(len), width_(wid)
            {
                if (len < 0 || wid < 0)
                    throw std::invalid_argument("expected positive lenght or width");
            }
            Quad(const Quad& copy)
                : x_(copy.x_), y_(copy.y_), lenght_(copy.lenght_), width_(copy.width_)
            {}
            void Get() {
                std::cout << x_ << " " << y_ << " " << lenght_ << " " << width_ << "\n";
            }
            double GetX() const{ return x_; }
            double GetY() const { return y_; }
            double GetL() const { return lenght_; }
            double GetW() const { return width_; }

            virtual void Scale(double param) = 0;
            virtual Quad* Intersect(const Quad& first, const Quad& second) const = 0;

        protected:
            double x_{ 0 };
            double y_{ 0 };
            double lenght_{ 0 };
            double width_{ 0 };
        };

        class Rect : public Quad {
        public:
            Rect() : Quad() {}
            Rect(double x, double y, double len = 0, double wid = 0) : Quad(x, y, len, wid) {}
            void Scale(double param) override {
                lenght_ *= param;
                width_ *= param;
            }
            Quad* Intersect(const Quad& first, const Quad& second) const override {
                double new_x = 0;
                double new_y = 0;
                double new_len = 0;
                double new_wid = 0;
                new_len = (first.GetL() + second.GetL()) / 2 - std::abs(first.GetX() - second.GetX());
                new_wid = (first.GetW() + second.GetW()) / 2 - std::abs(first.GetY() - second.GetY());
                if (new_len < 0) {
                    throw std::invalid_argument("");
                }
                if (first.GetX() < second.GetX()) {
                    new_x = first.GetX() + (first.GetL() + new_len) / 2;
                }
                else {
                    new_x = second.GetX() + (second.GetL() + new_len) / 2;
                }
                if (first.GetY() > second.GetY()) {
                    new_y = first.GetY() + (first.GetW() + new_wid) / 2;
                }
                else {
                    new_y = second.GetY() + (second.GetW() + new_wid) / 2;
                }
                   

            }
        };
    }
}



int main() {
    geo2d::orto::Rect a;
    geo2d::orto::Rect b(1, 2, 6, 4);
    geo2d::orto::Rect c(5, 7);
    b.Scale(3);
    b.Get();
    b.Scale(0.5);
    b.Get();


}
