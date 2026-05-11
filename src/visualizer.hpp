#pragma once

#include "sort_algorithm.hpp"

#include <memory>
#include <vector>
#include <array>

class SortingVisualizer
{
public:
    SortingVisualizer();

    auto run() -> void;

private:
    auto update() -> void;
    auto reset() -> void;
    auto draw() -> void;
    auto draw_bars() const -> void;
    auto draw_title() const -> void;
    auto draw_ui() -> void;

    static constexpr int window_width { 800 };
    static constexpr int window_height { 600 };
    static constexpr int num_elements { 100 };
    static constexpr float bar_max_window_height { 0.85f };
    static constexpr float bar_gap { 0.15f };
    static constexpr float side_margin { 5.0f };
    static constexpr int header_height { 80 };
    static constexpr std::array<int, 4> speed_multipliers { 1, 5, 10, 100 };

    std::unique_ptr<SortAlgorithm> algorithm_;
    std::vector<float> original_elements_;
    std::vector<float> elements_;

    int dropdown_active_item_ { 0 };
    bool dropdown_edit_mode_ { false };
    bool paused_ { false };
};
