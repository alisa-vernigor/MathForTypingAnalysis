#include <iostream>

#include <MathModule.h>

#include <vector>

int main() {
    MathModule math;
    std::vector<double> grid(10, 0);
    for (size_t i = 0; i < grid.size(); ++i) {
        grid[i] = i;
    }

    std::vector<double> mean(1, 1);

    std::vector<double> result(grid.size(), 0);

    math.find_density_0_on_grid(mean, grid, &result);

    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << i << ": " << result[i] << std::endl;
    }
}
