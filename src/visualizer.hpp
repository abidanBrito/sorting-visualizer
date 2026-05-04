#pragma once
#include <vector>

class SortingVisualizer
{
public:
    SortingVisualizer();

    auto run() -> void;

private:
    auto draw() const -> void;
    auto sort_step() -> void;

    static constexpr int window_width { 800 };
    static constexpr int window_height { 600 };
    static constexpr int num_elements { 100 };

    std::vector<float> elements_;
    size_t marker_idx_ { 0 };
};
