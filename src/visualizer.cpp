#include "visualizer.hpp"
#include "algorithms/selection_sort.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <raylib.h>
#include <random>

SortingVisualizer::SortingVisualizer()
    : algorithm_ { std::make_unique<SelectionSort>() }
{
    InitWindow(window_width, window_height, "Sorting Algorithms Visualizer");
    SetTargetFPS(30);

    std::mt19937 rng { std::random_device {}() };
    std::uniform_real_distribution<float> range { 0.0f, 1.0f };

    for (size_t i {}; i < num_elements; i++)
    {
        const float value { range(rng) };

        original_elements_.push_back(value);
        elements_.push_back(value);
    }
}

auto SortingVisualizer::run() -> void
{
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
}

auto SortingVisualizer::update() -> void
{
    if (!dropdown_edit_mode_ && !paused_)
    {
        const int sort_steps { speed_multipliers.at(dropdown_active_item_) };
        for (size_t i {}; i < sort_steps && !algorithm_->is_done(); i++)
            algorithm_->step(elements_);
    }
}

auto SortingVisualizer::reset() -> void
{
    elements_ = original_elements_;
    paused_ = false;
    algorithm_->reset();
}

auto SortingVisualizer::draw() -> void
{
    BeginDrawing();
    ClearBackground(Color { .r = 55, .g = 55, .b = 55, .a = 255 });

    draw_bars();
    draw_title();
    draw_ui();

    EndDrawing();
}

auto SortingVisualizer::draw_bars() const -> void
{
    const auto full_width = static_cast<float>(window_width);
    const auto full_height = static_cast<float>(window_height);

    const float available_width { full_width - (2.0f * side_margin) };
    const float x_step { available_width / static_cast<float>(num_elements) };
    const float bar_width { x_step * (1.0f - bar_gap) };

    const auto compared { algorithm_->compared_indices() };
    const auto swapped { algorithm_->swapped_indices() };
    const std::set<size_t> sorted { algorithm_->sorted_indices() };

    for (size_t i {}; i < num_elements; i++)
    {
        const float height { bar_max_window_height * full_height * elements_[i] };
        const bool is_compared { compared.contains(i) };
        const bool is_swapped { swapped.contains(i) };
        const bool is_sorted { sorted.contains(i) };

        const Color top_color = is_sorted     ? Color { .r = 120, .g = 220, .b = 210, .a = 255 }
                                : is_swapped  ? Color { .r = 220, .g = 180, .b = 255, .a = 255 }
                                : is_compared ? Color { .r = 255, .g = 120, .b = 220, .a = 255 }
                                              : Color { .r = 200, .g = 195, .b = 215, .a = 255 };

        const Color bottom_color = is_sorted     ? Color { .r = 60, .g = 160, .b = 150, .a = 255 }
                                   : is_swapped  ? Color { .r = 140, .g = 80, .b = 200, .a = 255 }
                                   : is_compared ? Color { .r = 200, .g = 60, .b = 180, .a = 255 }
                                                 : Color { .r = 180, .g = 160, .b = 210, .a = 255 };

        DrawRectangleGradientV(static_cast<int>(side_margin + (x_step * static_cast<float>(i))),
                               static_cast<int>(full_height - height), static_cast<int>(bar_width),
                               static_cast<int>(height), top_color, bottom_color);
    }
}

auto SortingVisualizer::draw_title() const -> void
{
    const std::string name { algorithm_->name() };
    static constexpr int font_size { 24 };
    const int text_width { MeasureText(name.c_str(), font_size) };

    DrawText(name.c_str(), (window_width - text_width) / 2, (header_height - font_size) / 2,
             font_size, Color { .r = 230, .g = 230, .b = 230, .a = 255 });
}

auto SortingVisualizer::draw_ui() -> void
{
    static constexpr Rectangle play_button_bounds { .x = 30, .y = 30, .width = 75, .height = 25 };
    if (GuiButton(play_button_bounds, paused_ ? "Play" : "Stop") != 0) paused_ = !paused_;

    static constexpr Rectangle reset_button_bounds { .x = 30, .y = 65, .width = 75, .height = 25 };
    if (GuiButton(reset_button_bounds, "Reset") != 0) reset();

    static constexpr Rectangle speed_multiplier_dropdown_bounds {
        .x = 115, .y = 30, .width = 75, .height = 25
    };
    if (GuiDropdownBox(speed_multiplier_dropdown_bounds, "1x;5x;10x;100x", &dropdown_active_item_,
                       dropdown_edit_mode_)
        != 0)
        dropdown_edit_mode_ = !dropdown_edit_mode_;
}
