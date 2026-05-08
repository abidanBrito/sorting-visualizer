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
        PollInputEvents();

        if (!algorithm_->is_done())
        {
            algorithm_->step(elements_);
        }

        BeginDrawing();
        ClearBackground(Color { .r = 55, .g = 55, .b = 55, .a = 255 });
        draw();
        EndDrawing();
    }
}

auto SortingVisualizer::draw() const -> void
{
    const auto full_width = static_cast<float>(window_width);
    const auto full_height = static_cast<float>(window_height);

    const float x_step { full_width / static_cast<float>(num_elements) };
    const float bar_width { x_step - bar_gap };

    const auto compared { algorithm_->get_compared() };
    const bool done { algorithm_->is_done() };

    for (size_t i {}; i < num_elements; i++)
    {
        const float height { 0.9f * full_height * elements_[i] };
        const bool is_compared { i == compared.first || i == compared.second };

        const Color top_color = done          ? Color { .r = 180, .g = 220, .b = 180, .a = 255 }
                                : is_compared ? Color { .r = 220, .g = 180, .b = 255, .a = 255 }
                                              : WHITE;

        const Color bottom_color = done          ? Color { .r = 120, .g = 160, .b = 130, .a = 255 }
                                   : is_compared ? Color { .r = 140, .g = 80, .b = 200, .a = 255 }
                                                 : Color { .r = 180, .g = 160, .b = 210, .a = 255 };

        DrawRectangleGradientV(static_cast<int>(x_step * static_cast<float>(i)),
                               static_cast<int>(full_height - height), static_cast<int>(bar_width),
                               static_cast<int>(height), top_color, bottom_color);
    }
}
