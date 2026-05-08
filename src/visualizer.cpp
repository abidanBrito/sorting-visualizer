#include "visualizer.hpp"

#include <raylib.h>
#include <random>

SortingVisualizer::SortingVisualizer()
{
    InitWindow(window_width, window_height, "Sorting Algorithms Visualizer");
    SetTargetFPS(30);

    std::mt19937 rng {};
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
        PollInputEvents();

        BeginDrawing();

        ClearBackground(Color { .r = 55, .g = 55, .b = 55, .a = 255 });
        draw();
        sort_step();

        EndDrawing();
    }
}

auto SortingVisualizer::draw() const -> void
{
    const auto full_width = static_cast<float>(window_width);
    const auto full_height = static_cast<float>(window_height);
    const float x_step { full_width / static_cast<float>(num_elements) };
    const float bar_width { x_step - bar_gap };

    for (size_t i {}; i < num_elements; i++)
    {
        const float height { 0.9f * full_height * elements_[i] };
        const bool is_compared { i == compared_.first || i == compared_.second };

        const Color top_color = sorted_       ? Color { .r = 180, .g = 220, .b = 180, .a = 255 }
                                : is_compared ? Color { .r = 220, .g = 180, .b = 255, .a = 255 }
                                              : WHITE;

        const Color bottom_color = sorted_       ? Color { .r = 120, .g = 160, .b = 130, .a = 255 }
                                   : is_compared ? Color { .r = 140, .g = 80, .b = 200, .a = 255 }
                                                 : Color { .r = 180, .g = 160, .b = 210, .a = 255 };

        DrawRectangleGradientV(static_cast<int>(x_step * static_cast<float>(i)),
                               static_cast<int>(full_height - height), static_cast<int>(bar_width),
                               static_cast<int>(height), top_color, bottom_color);
    }
}

auto SortingVisualizer::sort_step() -> void
{
    if (marker_idx_ >= num_elements)
    {
        sorted_ = true;
        return;
    }

    size_t min_idx { marker_idx_ };
    for (size_t i { marker_idx_ }; i < num_elements; i++)
    {
        if (elements_[i] <= elements_[min_idx])
        {
            min_idx = i;
        }
    }

    std::swap(elements_[marker_idx_], elements_[min_idx]);
    compared_ = { min_idx, marker_idx_ };

    marker_idx_++;
}
