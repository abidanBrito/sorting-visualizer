#pragma once

#include "sort_algorithm.hpp"

#include <raygui.h>
#include <raylib.h>

#include <memory>
#include <vector>
#include <array>

struct Pane
{
    std::unique_ptr<SortAlgorithm> algorithm;
    Rectangle rectangle;
    bool speed_dropdown_edit_mode { false };
    int speed_multiplier_idx { 0 };
};

class SortingVisualizer
{
public:
    SortingVisualizer();

    auto run() -> void;

private:
    auto update() -> void;
    auto reset() -> void;
    auto draw() -> void;
    auto draw_ui() -> void;
    auto draw_pane(const Pane& pane) const -> void;

    static constexpr int window_width { 1280 };
    static constexpr int window_height { 720 };
    static constexpr int num_elements { 40 };
    static constexpr int ui_top_bar_height { 50 };
    static constexpr int pane_title_top_margin { 25 };
    static constexpr int pane_padding { 5 };
    static constexpr int pane_margin { 10 };
    static constexpr float bar_max_pane_height { 0.85f };
    static constexpr float bar_gap { 0.1f };
    static constexpr int font_size { 20 };
    static constexpr std::array<int, 4> speed_multipliers { 1, 5, 10, 100 };

    std::vector<float> original_elements_;
    std::vector<float> elements_;

    std::array<Pane, 2> ui_panes_;
    bool ui_edit_mode_ { false };
    bool paused_ { false };
};
