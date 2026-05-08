#pragma once

#include <vector>
#include <string_view>
#include <utility>

class SortAlgorithm
{
public:
    SortAlgorithm() = default;
    virtual ~SortAlgorithm() = default;

    SortAlgorithm(const SortAlgorithm&) = delete;
    auto operator =(const SortAlgorithm&) -> SortAlgorithm& = delete;

    SortAlgorithm(SortAlgorithm&&) = delete;
    auto operator =(SortAlgorithm&&) -> SortAlgorithm& = delete;

    virtual auto step(std::vector<float>& elements) -> void = 0;
    virtual auto reset() -> void = 0;

    [[nodiscard]] virtual auto get_compared() const -> std::pair<size_t, size_t> = 0;
    [[nodiscard]] virtual auto get_name() const -> std::string_view = 0;
    [[nodiscard]] virtual auto is_done() const -> bool = 0;
};
