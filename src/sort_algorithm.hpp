#pragma once

#include <set>
#include <vector>
#include <string_view>

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

    [[nodiscard]] virtual auto compared_indices() const -> std::set<size_t> = 0;
    [[nodiscard]] virtual auto swapped_indices() const -> std::set<size_t> = 0;
    [[nodiscard]] virtual auto sorted_indices() const -> std::set<size_t> = 0;
    [[nodiscard]] virtual auto name() const -> std::string_view = 0;

    [[nodiscard]] auto is_done() const -> bool { return done_; }

protected:
    auto mark_done() -> void { done_ = true; }
    auto reset_done() -> void { done_ = false; }

private:
    bool done_ { false };
};
