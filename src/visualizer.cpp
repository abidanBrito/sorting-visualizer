#include "visualizer.hpp"
#include "algorithms/selection_sort.hpp"

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
        elements_.push_back(range(rng));
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
    PollInputEvents();
    if (!algorithm_->is_done()) algorithm_->step(elements_);
}

auto SortingVisualizer::draw() const -> void
{
    BeginDrawing();
    ClearBackground(Color { .r = 55, .g = 55, .b = 55, .a = 255 });
    draw_bars();
    draw_title();
    EndDrawing();
}

auto SortingVisualizer::draw_bars() const -> void
{
    const auto full_width = static_cast<float>(window_width);
    const auto full_height = static_cast<float>(window_height);

    const float x_step { full_width / static_cast<float>(num_elements) };
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

        DrawRectangleGradientV(static_cast<int>(x_step * static_cast<float>(i)),
                               static_cast<int>(full_height - height), static_cast<int>(bar_width),
                               static_cast<int>(height), top_color, bottom_color);
    }
}

auto SortingVisualizer::draw_title() const -> void
{
    const std::string name { algorithm_->name() };
    constexpr int font_size { 24 };
    const int text_width { MeasureText(name.c_str(), font_size) };

    DrawText(name.c_str(), (window_width - text_width) / 2, (header_height - font_size) / 2,
             font_size, Color { .r = 230, .g = 230, .b = 230, .a = 255 });
}
