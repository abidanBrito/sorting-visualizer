#pragma once

#include "sort_algorithm.hpp"

#include <memory>
#include <vector>

class SortingVisualizer
{
public:
    SortingVisualizer();

    auto run() -> void;

private:
    auto draw() const -> void;

    static constexpr int window_width { 800 };
    static constexpr int window_height { 600 };
    static constexpr int num_elements { 100 };
    static constexpr float bar_gap { 0.15f };

    std::unique_ptr<SortAlgorithm> algorithm_;
    std::vector<float> elements_;
};
