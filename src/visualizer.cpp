#include "visualizer.hpp"
#include "algorithms/selection_sort.hpp"
#include "algorithms/bubble_sort.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <random>

SortingVisualizer::SortingVisualizer()
{
    ui_panes_[0].algorithm = std::make_unique<SelectionSort>();
    ui_panes_[0].speed_multiplier_idx = 0;
    ui_panes_[0].rectangle = Rectangle { .x = 0,
                                         .y = ui_top_bar_height,
                                         .width = window_width / 2.0f,
                                         .height = window_height - ui_top_bar_height };

    ui_panes_[1].algorithm = std::make_unique<BubbleSort>();
    ui_panes_[1].speed_multiplier_idx = 0;
    ui_panes_[1].rectangle = Rectangle { .x = window_width / 2.0f,
                                         .y = ui_top_bar_height,
                                         .width = window_width / 2.0f,
                                         .height = window_height - ui_top_bar_height };

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
    if (!paused_ && !ui_edit_mode_)
    {
        for (auto& pane : ui_panes_)
        {
            const int sort_steps = speed_multipliers.at(pane.speed_multiplier_idx);
            for (size_t i {}; i < sort_steps && !pane.algorithm->is_done(); i++)
                pane.algorithm->step(elements_);
        }
    }

    draw_ui();
}

auto SortingVisualizer::reset() -> void
{
    elements_ = original_elements_;

    for (auto& pane : ui_panes_)
        pane.algorithm->reset();
}

auto SortingVisualizer::draw() -> void
{
    BeginDrawing();
    ClearBackground(Color { .r = 40, .g = 40, .b = 40, .a = 255 });

    for (auto& pane : ui_panes_)
        draw_pane(pane);

    EndDrawing();
}

auto SortingVisualizer::draw_pane(const Pane& pane) const -> void
{
    Rectangle rect = pane.rectangle;
    rect.x += pane_margin;
    rect.y += pane_margin;
    rect.width -= 2 * pane_margin;
    rect.height -= 2 * pane_margin;

    DrawRectangleLinesEx(rect, 2.0f, Color { .r = 200, .g = 200, .b = 200, .a = 255 });

    const std::string name { pane.algorithm->name() };
    const int name_width { MeasureText(name.c_str(), font_size) };

    DrawText(name.c_str(),
             static_cast<int>(rect.x + ((rect.width - static_cast<float>(name_width)) / 2)),
             static_cast<int>(rect.y + pane_padding + pane_title_top_margin), font_size,
             Color { .r = 230, .g = 230, .b = 230, .a = 255 });

    const float available_width { rect.width - (2.0f * pane_padding) };
    const float x_step { available_width / static_cast<float>(num_elements) };
    const float bar_width { x_step * (1.0f - bar_gap) };

    const auto compared { pane.algorithm->compared_indices() };
    const auto swapped { pane.algorithm->swapped_indices() };
    const auto sorted { pane.algorithm->sorted_indices() };

    for (size_t i {}; i < num_elements; i++)
    {
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

        const float drawable_height { rect.height - (2.0f * pane_padding) };
        const float bar_height { bar_max_pane_height * drawable_height * elements_[i] };
        const float bar_x = rect.x + pane_padding + (x_step * static_cast<float>(i));
        const float bar_y = rect.y + rect.height - pane_padding - bar_height;

        DrawRectangleGradientV(static_cast<int>(bar_x), static_cast<int>(bar_y),
                               static_cast<int>(bar_width), static_cast<int>(bar_height), top_color,
                               bottom_color);
    }
}

auto SortingVisualizer::draw_ui() -> void
{
    static constexpr float button_width { 75 };
    static constexpr float button_height { 25 };
    static constexpr float button_spacing { 10 };

    const float total_width = (2 * button_width) + button_spacing;
    const float start_x = (window_width - total_width) / 2.0f;
    const float y = (ui_top_bar_height - button_height) / 2.0f;

    const Rectangle play_button_bounds {
        .x = start_x, .y = y, .width = button_width, .height = button_height
    };

    const Rectangle reset_button_bounds { .x = start_x + button_width + button_spacing,
                                          .y = y,
                                          .width = button_width,
                                          .height = button_height };

    if (GuiButton(play_button_bounds, paused_ ? "Play" : "Pause") != 0) paused_ = !paused_;
    if (GuiButton(reset_button_bounds, "Reset") != 0) reset();

    for (auto& pane : ui_panes_)
    {
        Rectangle rect = pane.rectangle;

        rect.x += pane_margin;
        rect.y += pane_margin;
        rect.width -= 2 * pane_margin;
        rect.height -= 2 * pane_margin;

        Rectangle speed_multiplier_dropdown_bounds { .x = rect.x + (pane_padding * 2.0f),
                                                     .y = rect.y + (pane_padding * 2.0f),
                                                     .width = 75,
                                                     .height = 25 };

        if (GuiDropdownBox(speed_multiplier_dropdown_bounds, "1x;5x;10x;100x",
                           &pane.speed_multiplier_idx, pane.speed_dropdown_edit_mode)
            != 0)
        {
            pane.speed_dropdown_edit_mode = !pane.speed_dropdown_edit_mode;
        }
    }
}
