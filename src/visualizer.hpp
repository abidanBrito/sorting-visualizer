#pragma once
#include <vector>
#include <utility>

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
    static constexpr float bar_gap { 0.1f };

    std::vector<float> elements_;
    std::pair<size_t, size_t> compared_;
    size_t marker_idx_ { 0 };
    bool sorted_ { false };
};
