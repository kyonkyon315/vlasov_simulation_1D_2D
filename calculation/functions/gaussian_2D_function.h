#ifndef GAUSSIAN_2D_FUNCTION_H
#define GAUSSIAN_2D_FUNCTION_H
#include <cmath>
#include <stdexcept>
namespace Gaussian_2D_function{
// π 定数
constexpr double PI = 3.14159265358979323846;

/**
 * 2D Gaussian function (no covariance term).
 * 
 * @param x       評価点 x
 * @param y       評価点 y
 * @param mu_x    平均値 (x方向)
 * @param mu_y    平均値 (y方向)
 * @param sigma_x 標準偏差 (x方向)
 * @param sigma_y 標準偏差 (y方向)
 * @param normalized 正規化する場合 true
 * @return G(x,y)
 */
inline double function(double x, double y,
                         double mu_x = 0.0, double mu_y = 0.0,
                         double sigma_x = 1.0, double sigma_y = 1.0,
                         bool normalized = true) {
    if (sigma_x <= 0.0 || sigma_y <= 0.0) {
        throw std::invalid_argument("sigma_x, sigma_y must be positive");
    }

    const double dx = (x - mu_x) / sigma_x;
    const double dy = (y - mu_y) / sigma_y;
    const double exponent = -0.5 * (dx * dx + dy * dy);
    const double g = std::exp(exponent);

    if (normalized) {
        return g / (2.0 * PI * sigma_x * sigma_y);
    } else {
        return g;
    }
}
};
#endif